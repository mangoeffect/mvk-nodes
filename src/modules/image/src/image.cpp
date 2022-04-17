/**
 * @file image.cpp
 * @author mango (2321544362@qq.com)
 * @brief 
 * @version 0.1
 * @date 2021-08-09
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "image/image.hpp"
#include "image/image_impl.hpp"
#include <cstring>


namespace mvk
{
    Image::Image()
     : image_impl_(new ImageImpl())
    {

    }

    Image::Image(uint8_t* data, const size_t& width, const size_t& height, const IMAGE_FORMAT& format)
    : image_impl_(new ImageImpl(data, width, height, format))
    {

    }

    Image::Image(const size_t& width, const size_t& height, const uint8_t init_value)
    {
        uint8_t* data = new uint8_t[width * height]();
        std::memset(data, init_value, width * height);
        image_impl_ = std::make_shared<ImageImpl>(data, width, height, IMAGE_FORMAT::MONO_8_BIT);
    }

    Image::Image(const size_t& width, const size_t& height, const std::array<uint8_t, 3>& init_value)
    {
        uint8_t* data = new uint8_t[width * height * 3]();
        image_impl_ = std::make_shared<ImageImpl>(data, width, height, IMAGE_FORMAT::RGB_24_BIT);
        for(size_t i = 0; i < height; i++) //row
        {
            for(size_t j = 0; j < width; j++)//col
            {
                GetPixel(i, j)[0] = init_value[0];
                GetPixel(i, j)[1] = init_value[1];
                GetPixel(i, j)[2] = init_value[2];
            }
        }
    }

    Image::Image(const Matrix<uint8_t>& matrix, const size_t channel)
    {
        assert(channel == 1 || channel == 3);
        size_t rows = matrix.Rows();
        size_t cols = matrix.Cols();
        uint8_t* data = new uint8_t[rows * cols];
        for(size_t i = 0; i < rows; i++)
        {
            std::memcpy(data + i * cols, &matrix(i,0), cols);
        }
        if(1 == channel)
        {
            image_impl_ = std::make_shared<ImageImpl>(data, cols, rows, IMAGE_FORMAT::MONO_8_BIT);
        }else
        {
            assert(cols % 3 == 0);
            image_impl_ = std::make_shared<ImageImpl>(data, cols / 3, rows, IMAGE_FORMAT::RGB_24_BIT);
        }
    }

    Image Image::Copy() const
    {
        size_t data_size = GetHeight() * GetWidth() * GetChannel();
        uint8_t* data = new uint8_t[data_size];
        std::memcpy(data, GetData(),data_size);

        auto format = GetChannel() == 1 ? IMAGE_FORMAT::MONO_8_BIT : IMAGE_FORMAT::RGB_24_BIT;
        return Image(data, GetWidth(), GetHeight(), format);
    }

    Image Image::CopyWithBorder(const size_t border_size, 
                                const BORDER_TYPE& border_type,
                                const std::array<uint8_t, 3>& const_border) const
    {
        if(border_size == 0)
        {
            return Copy();
        }else
        {
            size_t cols = GetHeight();
            size_t rows = GetWidth();

            size_t new_cols = cols + border_size * 2;
            size_t new_rows = rows + border_size * 2;
            size_t channel = GetChannel();
            size_t data_size = (new_cols) * (new_rows) * channel;
            uint8_t* data = new uint8_t[data_size]();

            //拷贝原图像数据
            for(size_t i = 0; i < rows; i++)
            {
                size_t new_i = i + border_size;
                size_t new_start = (new_i * new_cols + border_size) * channel;
                std::memcpy(data + new_start, GetPixel(i, 0), cols * channel);
            }
            auto format = channel == 1 ? IMAGE_FORMAT::MONO_8_BIT : IMAGE_FORMAT::RGB_24_BIT;
            Image img_with_border(data, new_cols, new_rows, format);

            switch(border_type)
            {
                //默认 镜像， 123 | 321
                case BORDER_TYPE::DEFAULT: 
                {
                     //填充左右两边
                    for(int i = border_size; i < new_rows - border_size; i++) // rows in new image
                    {
                        //左边
                        for(int left = border_size - 1, right = border_size; left >= 0; left--, right++) //cols in new image
                        {
                            for(int c = 0; c < channel; c++)
                            {
                                img_with_border.GetPixel(i, left)[c] = img_with_border.GetPixel(i,right)[c];
                            }
                        }
                        //右边
                        for(int left = new_cols - border_size - 1, right = new_cols - border_size; right < new_cols; left--,right++) //cols
                        {
                            for(int c = 0; c < channel; c++)
                            {
                                img_with_border.GetPixel(i,right)[c] = img_with_border.GetPixel(i, left)[c];
                            }
                        }
                    }
 
                    //填充上下两边
                    for(int top = border_size - 1, bot = border_size; top >= 0; top--, bot++)
                    {
                        std::memcpy(img_with_border.GetPixel(top, 0), img_with_border.GetPixel(bot, 0), new_cols * channel);
                    }
                    for(int bot = new_rows - border_size, top = new_rows - border_size - 1; bot < new_rows; bot++, top--)
                    {
                        std::memcpy(img_with_border.GetPixel(bot, 0), img_with_border.GetPixel(top, 0), new_cols * channel);
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
                                img_with_border.GetPixel(i, left)[c] = const_border[c];
                            }
                        }
                        for(int right = new_cols - border_size - 1; right < new_cols; right++) //cols
                        {
                            for(int c = 0; c < channel; c++)
                            {
                                img_with_border.GetPixel(i, right)[c] = const_border[c];
                            }
                        }
                    }
                    //填充上下两边
                    for(int i = 0; i < new_cols; i++) //rows
                    {
                        for(int c = 0; c < channel; c++)
                        {
                            img_with_border.GetPixel(0, i)[c] = const_border[c];
                        }
                    }
                    for(int top = 1; top < border_size; top++)
                    {
                        std::memcpy(img_with_border.GetPixel(top, 0), img_with_border.GetPixel(0, 0), new_cols * channel);
                    }
                    for(int bottom = new_rows - border_size; bottom < new_rows; bottom++)
                    {
                        std::memcpy(img_with_border.GetPixel(bottom, 0), img_with_border.GetPixel(0, 0), new_cols * channel);
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
                                img_with_border.GetPixel(i, left)[c] = img_with_border.GetPixel(i,right)[c];
                            }
                        }
                        //右边
                        for(int left = new_cols - border_size - 1, right = new_cols - border_size; right < new_cols; right++) //cols
                        {
                            for(int c = 0; c < channel; c++)
                            {
                                img_with_border.GetPixel(i,right)[c] = img_with_border.GetPixel(i, left)[c];
                            }
                        }
                    }
                    //填充上下两边
                    for(int top = 0; top < border_size; top++)
                    {
                        std::memcpy(img_with_border.GetPixel(top, 0), img_with_border.GetPixel(border_size, 0), new_cols * channel);
                    }
                    for(int bottom = new_rows - border_size; bottom < new_rows; bottom++)
                    {
                        std::memcpy(img_with_border.GetPixel(bottom, 0), img_with_border.GetPixel(new_rows - border_size - 1, 0), new_cols * channel);
                    }
                    break;
                }
            }
          
            return img_with_border;
        }
    }

    
    Image::~Image()
    {

    }


    int Image::Read(const std::string& filename,  const IMAGE_FORMAT& format)
    {
        return image_impl_->Read(filename, format);
    }


    int Image::Save(const std::string& filename)
    {
        return image_impl_->Save(filename);
    }


    uint8_t* Image::GetData() const
    {
        return image_impl_->GetData();
    }


    uint8_t* Image::GetRow(const size_t& rows) const
    {
        return image_impl_->GetRow(rows);
    }

    uint8_t* Image::GetPixel(const size_t& rows, const size_t& cols) const
    {   
        return image_impl_->GetPixel(rows, cols);
    }

    uint8_t* Image::GetPixel(const Point2i& p)
    {
        return GetPixel(p.y, p.x);
    }


    size_t Image::GetWidth() const
    {
        return image_impl_->GetWidth();
    }

    size_t Image::GetHeight() const
    {
        return image_impl_->GetHeight();
    }


    size_t Image::GetChannel() const
    {
        return image_impl_->GetChannel();
    }

    int Image::Release()
    {
        return image_impl_->Release();
    }
    
} // namespace mvk


