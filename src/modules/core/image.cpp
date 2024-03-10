#include "image.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image/stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image/stb_image_write.h"

#include <cstring>
#include <iostream>

Image::Image()
{
    ptr_ = nullptr;
    re_ptr_ = new RePtr();
    owner_ = false;
    unit_type_ = 0;
    origin_rect_ = Rect();
    my_rect_ = Rect();
    rows = 0;
    cols = 0;
}

Image::Image(const Size &size, uattr type)
{
    ptr_ = (uchar*)malloc(size.width * size.height * UNITATTR_SIZE(type));
    re_ptr_ = new RePtr();

    assert(ptr_ != nullptr);

    my_rect_ = origin_rect_ = Rect(0, 0, size.width, size.height);
    unit_type_ = type;
    rows = size.height;
    cols = size.width;
}

Image::Image(const Size &size, uattr type, uchar* data)
{
    assert(data != nullptr);
    ptr_ = data;
    re_ptr_ = new RePtr();
    my_rect_ = origin_rect_ = Rect(0, 0, size.width, size.height);
    unit_type_ = type;
    rows = size.height;
    cols = size.width;
}

Image::Image(const Image &other)
{
    ptr_ = other.ptr_;
    re_ptr_ = other.re_ptr_;
    ++re_ptr_->count;
    owner_ = true;
    auto& t = const_cast<Image&>(other);
    t.owner_ = false;
    unit_type_ = other.unit_type_;
    origin_rect_ = other.origin_rect_;
    my_rect_ = other.my_rect_;
    rows = other.rows;
    cols = other.cols;
}

Image::Image(const Image &&other)
{
    ptr_ = other.ptr_;
    re_ptr_ = other.re_ptr_;
    ++re_ptr_->count;
    owner_ = true;
    auto t = const_cast<Image&>(other);
    t.owner_ = false;
    unit_type_ = other.unit_type_;
    origin_rect_ = other.origin_rect_;
    my_rect_ = other.my_rect_;
    rows = other.rows;
    cols = other.cols;
}

Image &Image::operator=(const Image &other)
{
    ++other.re_ptr_->count;
    if (--re_ptr_->count == 0)
    {
        Release();
    }
    re_ptr_ = other.re_ptr_;
    ptr_ = other.ptr_;
    origin_rect_ = other.origin_rect_;
    my_rect_ = other.my_rect_;
    unit_type_ = other.unit_type_;
    owner_ = true;
    auto t = const_cast<Image&>(other);
    t.owner_ = false;
    rows = other.rows;
    cols = other.cols;

    return *this;
}

Image Image::operator()(const Rect &roi)
{
    Image ret = *this;
    ret.owner_ = false;
    this->owner_ = true;
    ret.my_rect_ = roi;

    return ret;
}

void Image::Create(const Size &size, uattr type)
{
    Release();

    ptr_ = (uchar*)malloc(size.width * size.height * UNITATTR_SIZE(type));

    assert(ptr_ != NULL);

    my_rect_ = origin_rect_ = Rect(0, 0, size.width, size.height);
    unit_type_ = type;
    rows = size.height;
    cols = size.width;
}

void Image::Release()
{
    if(re_ptr_->count == 0)
    {
        delete re_ptr_;
        re_ptr_ = nullptr;
        ptr_ = nullptr;
        owner_ = true;
        unit_type_ = 0;
        origin_rect_ = Rect();
        my_rect_ = Rect();
        rows = 0;
        cols = 0;
        if (ptr_)
            free(ptr_);
    }
}

std::uint8_t Image::Channels() const
{
    return UNITATTR_SIZE(unit_type_);
}

bool Image::IsEmpty() const
{
    return  ptr_ == nullptr || rows <= 0 || cols <= 0;
}

Size Image::GetSize() const
{
    return Size(my_rect_.width, my_rect_.height);
}

uattr Image::GetType() const
{
    return unit_type_;
}


void Image::CopyTo(Image &other) const
{
    other.Create(my_rect_.size(), unit_type_);

    if (my_rect_.x == 0 && my_rect_.y == 0)
    {
        memcpy(other.ptr_, ptr_, my_rect_.height * my_rect_.width * UNITATTR_SIZE(unit_type_));
        return;
    }

    for (int row = 0; row < other.my_rect_.height; ++row)
        memcpy(other.ptr_ + (UNITATTR_SIZE(unit_type_) * other.my_rect_.width * row), ptr_ + (((origin_rect_.width * (row + my_rect_.y)) + my_rect_.x) * UNITATTR_SIZE(unit_type_)), (UNITATTR_SIZE(unit_type_) * other.my_rect_.width));
}

Image Image::Clone() const
{
    Image copy_img;
    CopyTo(copy_img);
    return  copy_img;
}

 Image::~Image()
{
    if (--re_ptr_->count == 0)
    {
        Release();
    }
}

template<typename E>
E &Image::At(int x, int y)
{
    return *((E*)(&(ptr_[UNITATTR_SIZE(unit_type_)*((origin_rect_.width * (y + my_rect_.y)) + (x + my_rect_.x))])));
}

template<typename E>
E &Image::At(const Point &point)
{
    return At<E>(point.x, point.y);
}

template<typename E>
E *Image::Ptr(int x, int y)
{
    return &At<E>(x, y);
}

template<typename E>
E *Image::Ptr(const Point &point)
{
    return Ptr<E>(point.x, point.y);
}

static IMAGE_TYPE ChannelToType(const int channels)
{
    if(channels == 1)
    {
        return  IMAGE_TYPE::IMAGE_8UC1;
    }else if(channels == 2)
    {
        return IMAGE_TYPE::IMAGE_8UC2;
    }else if(channels == 3)
    {
        return IMAGE_TYPE::IMAGE_8UC3;
    }else if(channels == 4)
    {
        return IMAGE_TYPE::IMAGE_32FC4;
    }else{
        return IMAGE_TYPE::IMAGE_32FC4;
    }
}

Image LoadImage(const char* img_path)
{
    Image matrix;
    assert(img_path != nullptr);
    if(img_path != nullptr)
    {
        int w, h, n;
        w = h = n = 0;
        std::uint8_t *data = stbi_load(img_path, &w, &h, &n, 0);
        if(nullptr != data)
        {
            auto tmp = Image(Size(w, h), ChannelToType(n), data);
            matrix = tmp;
        }
    }
    return matrix;
}

int WriteImage(Image img, const char* img_path)
{
    if(img.IsEmpty() || img_path == nullptr)
    {
        return  -1;
    }
    std::uint8_t* data = img.Ptr<std::uint8_t>(0, 0);
    auto src_size = img.GetSize();
    int  h = src_size.height;
    int  w = src_size.width;
    auto n = img.Channels();

    std::string file_name = std::string(img_path);
    size_t dot_position = file_name.find_last_of(".");
    if (dot_position != std::string::npos)
    {
        std::string file_extension = file_name.substr(dot_position + 1);
        if(file_extension == "jpg" || file_extension == "jpeg" )
        {
            //图片质量范围【0-100】，默认95，与opencv一致
            return stbi_write_jpg(img_path, w, h, n, data, 95);
        }else if(file_extension == "png")
        {
            return stbi_write_png(img_path,w, h, n, data, w * n );
        }else if(file_extension == "bmp")
        {
            return stbi_write_bmp(img_path, w, h, n, data);
        }else
        {
            std::cerr<< "The image format unsupported!!!" << std::endl;
        }
    }
    return -1;
}

Image Image::CopyWithBorder(const size_t border_size,
                            const BORDER_TYPE& border_type,
                            const std::array<uint8_t, 3>& const_border)
{
    if(border_size == 0 || border_type == BORDER_TYPE::NONE)
    {
        return Clone();
    }else
    {
        size_t cols = this->cols;
        size_t rows = this->rows;

        size_t new_cols = cols + border_size * 2;
        size_t new_rows = rows + border_size * 2;
        size_t channel = Channels();
        size_t data_size = (new_cols) * (new_rows) * channel;
        uint8_t* data = new uint8_t[data_size]();

        //拷贝原图像数据
        for(size_t i = 0; i < rows; i++)
        {
            size_t new_i = i + border_size;
            size_t new_start = (new_i * new_cols + border_size) * channel;
            std::memcpy(data + new_start, Ptr<std::uint8_t>(0, i), cols * channel);
        }

        Image img_with_border(Size(new_cols, new_cols), unit_type_, data);

        switch(border_type)
        {
            //默认 镜像， 123 | 321
            case BORDER_TYPE::MIRROR:
            {
                //填充左右两边
                for(int i = border_size; i < new_rows - border_size; i++) // rows in new image
                {
                    //左边
                    for(int left = border_size - 1, right = border_size; left >= 0; left--, right++) //cols in new image
                    {
                        for(int c = 0; c < channel; c++)
                        {
                            img_with_border.Ptr<std::uint8_t>(left, i)[c] = img_with_border.Ptr<std::uint8_t>(right, i)[c];
                        }
                    }
                    //右边
                    for(int left = new_cols - border_size - 1, right = new_cols - border_size; right < new_cols; left--,right++) //cols
                    {
                        for(int c = 0; c < channel; c++)
                        {
                            img_with_border.Ptr<std::uint8_t>(right, i)[c] = img_with_border.Ptr<std::uint8_t>(left, i)[c];
                        }
                    }
                }

                //填充上下两边
                for(int top = border_size - 1, bot = border_size; top >= 0; top--, bot++)
                {
                    std::memcpy(img_with_border.Ptr<std::uint8_t>(0, top), img_with_border.Ptr<std::uint8_t>(0, bot), new_cols * channel);
                }
                for(int bot = new_rows - border_size, top = new_rows - border_size - 1; bot < new_rows; bot++, top--)
                {
                    std::memcpy(img_with_border.Ptr<std::uint8_t>(0, bot), img_with_border.Ptr<std::uint8_t>(0, top), new_cols * channel);
                }
                break;
            }
            case BORDER_TYPE::CONSTANT:
            {
                //填充左右两边
                for(int i = border_size; i < new_rows - border_size; i++) // rows
                {
                    for(int left = 0; left < border_size; left++) //cols
                    {
                        for(int c = 0; c < channel; c++)
                        {
                            img_with_border.Ptr<std::uint8_t>(left, i)[c] = const_border[c];
                        }
                    }
                    for(int right = new_cols - border_size - 1; right < new_cols; right++) //cols
                    {
                        for(int c = 0; c < channel; c++)
                        {
                            img_with_border.Ptr<std::uint8_t>(right, i)[c] = const_border[c];
                        }
                    }
                }
                //填充上下两边
                for(int i = 0; i < new_cols; i++) //rows
                {
                    for(int c = 0; c < channel; c++)
                    {
                        img_with_border.Ptr<std::uint8_t>(i, 0)[c] = const_border[c];
                    }
                }
                for(int top = 1; top < border_size; top++)
                {
                    std::memcpy(img_with_border.Ptr<std::uint8_t>( 0, top), img_with_border.Ptr<std::uint8_t>(0, 0), new_cols * channel);
                }
                for(int bottom = new_rows - border_size; bottom < new_rows; bottom++)
                {
                    std::memcpy(img_with_border.Ptr<std::uint8_t>(0, bottom), img_with_border.Ptr<std::uint8_t>(0, 0), new_cols * channel);
                }
                break;
            }
            case BORDER_TYPE::REPLICATE:
            {
                //填充左右两边
                for(int i = border_size; i < new_rows - border_size; i++) // rows
                {
                    //左边
                    for(int left = border_size - 1, right = border_size; left >= 0; left--) //cols
                    {
                        for(int c = 0; c < channel; c++)
                        {
                            img_with_border.Ptr<std::uint8_t>(left, i)[c] = img_with_border.Ptr<std::uint8_t>(right, i)[c];
                        }
                    }
                    //右边
                    for(int left = new_cols - border_size - 1, right = new_cols - border_size; right < new_cols; right++) //cols
                    {
                        for(int c = 0; c < channel; c++)
                        {
                            img_with_border.Ptr<std::uint8_t>(right, i)[c] = img_with_border.Ptr<std::uint8_t>(left, i)[c];
                        }
                    }
                }
                //填充上下两边
                for(int top = 0; top < border_size; top++)
                {
                    std::memcpy(img_with_border.Ptr<std::uint8_t>(0, top), img_with_border.Ptr<std::uint8_t>(0, border_size), new_cols * channel);
                }
                for(int bottom = new_rows - border_size; bottom < new_rows; bottom++)
                {
                    std::memcpy(img_with_border.Ptr<std::uint8_t>(0, bottom), img_with_border.Ptr<std::uint8_t>(0,new_rows - border_size - 1), new_cols * channel);
                }
                break;
            }
        }

        return img_with_border;
    }
}

Image Image::Convert(const CONVERT_TYPE &type) const
{
    return  ConvertType(*this, type);
}

Image Rgb2Gray(Image src)
{
    assert(src.Channels() == 3);
    auto size = src.GetSize();
    int h = size.height;
    int w = size.width;

    Image dst(size, IMAGE_TYPE::IMAGE_8UC1);

    for(int i = 0; i < h; i++)
    {
        for(int j = 0; j < w; j++)
        {
            auto rgb = src.At<Vec3b>(j, i);
            dst.At<std::uint8_t>(j, i) = std::round(rgb[0] * 0.299 + rgb[1] * 0.578 + rgb[2] * 0.114);
        }
    }
    return dst;
}

Image Rgb2Bgr(Image src)
{
    assert(src.Channels() == 3);
    auto size = src.GetSize();
    int h = size.height;
    int w = size.width;

    Image dst(size, IMAGE_TYPE::IMAGE_8UC3);
    for(int i = 0; i < h; i++)
    {
        for(int j = 0; j < w; j++)
        {
            auto src_rgb = src.At<Vec3b>(j, i);
            auto dst_rgb = src.At<Vec3b>(j, i);
            dst_rgb[0] = src_rgb[2];
            dst_rgb[1] = src_rgb[1];
            dst_rgb[2] = src_rgb[0];
        }
    }
    return dst;
}

Image Rgb2Rgba(Image src)
{
    assert(src.Channels() == 3);
    auto size = src.GetSize();
    int h = size.height;
    int w = size.width;

    Image dst(size, IMAGE_TYPE::IMAGE_8UC4);
    for(int i = 0; i < h; i++)
    {
        for(int j = 0; j < w; j++)
        {
            auto src_rgb = src.Ptr<std::uint8_t>(j, i);
            auto dst_rgb = dst.Ptr<std::uint8_t>(j, i);
            dst_rgb[0] = src_rgb[0];
            dst_rgb[1] = src_rgb[1];
            dst_rgb[2] = src_rgb[2];
            dst_rgb[3] = 255;
        }
    }
    return dst;
}

Image Rgb2Hsv(Image src)
{
    assert(src.Channels() == 3);
    auto size = src.GetSize();
    int h = size.height;
    int w = size.width;

    Image dst(size, src.GetType());

    for(int i = 0; i < h; i++)
    {
        for(int j = 0; j < w; j++)
        {
            auto src_rgb = src.Ptr<std::uint8_t>(j, i);
            auto dst_rgb = dst.Ptr<std::uint8_t>(j, i);
            auto r = src_rgb[0];
            auto g = src_rgb[1];
            auto b = src_rgb[2];
            auto v = std::max({r, g, b}); //v
            auto min_rgb = std::min({r, g, b});
            auto s = v == 0 ? 0 : (v - min_rgb) / float(v);//s
            int h = 0;
            if(v == r)
            {
                h = 60 * (g - b) / (v - min_rgb);
            }else if(v == g)
            {
                h = 120 + 60 * (b - r) / (v - min_rgb);
            }else
            {
                //v == b
                h = 240 + 60 * (r - g) / (v - min_rgb);
            }
            h = h >= 0 ? h : h + 360;

            dst_rgb[0] = h / 2;
            dst_rgb[1] = s * 255;
            dst_rgb[2] = v;
        }
    }
    return dst;
}


Image ConvertType(Image src, const CONVERT_TYPE& type)
{
    if(src.IsEmpty()){return  src;}

    switch (type)
    {
        case CONVERT_TYPE::RGB2BGR:
        {
            return Rgb2Bgr(src);
        }
        case CONVERT_TYPE::RGB2GRAY:
        {
            return Rgb2Gray(src);
        }
        case CONVERT_TYPE::RGB2RGBA:
        {
            return Rgb2Rgba(src);
        }
        case CONVERT_TYPE::RGB2HSV:
        {
            return Rgb2Hsv(src);
        }
        default:
    }
    return src;
}
