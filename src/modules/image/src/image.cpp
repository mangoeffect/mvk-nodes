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


    Image Image::Copy() const
    {
        size_t data_size = GetHeight() * GetWidth() * GetChannel();
        uint8_t* data = new uint8_t[data_size];
        std::memcpy(data, GetData(),data_size);

        auto format = GetChannel() == 1 ? IMAGE_FORMAT::MONO_8_BIT : IMAGE_FORMAT::RGB_24_BIT;
        return Image(data, GetWidth(), GetHeight(), format);
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


