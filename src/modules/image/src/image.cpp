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

#include "image/image.h"
#include "image/image_impl.h"



namespace mvk
{
    Image::Image(const unsigned char* data, const size_t& width, const size_t& height, const IMAGE_FORMAT& format)
    : image_impl_(new ImageImpl(data, width, height, format))
    {

    }

    
    Image::~Image()
    {
        image_impl_->~ImageImpl();
    }


    int Image::Read(const std::string& filename,  const IMAGE_FORMAT& format)
    {
        return image_impl_->Read(filename, format);
    }


    int Image::Save(const std::string& filename)
    {
        return image_impl_->Save(filename);
    }


    unsigned char* Image::GetData() const
    {
        return image_impl_->GetData();
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


