/**
 * @file image_impl.cpp
 * @author mango (2321544362@qq.com)
 * @brief image的实现类具体方法实现
 * @version 0.1
 * @date 2021-08-17
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "image/image_impl.h"

#include <cassert>
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb/stb_image_write.h"

namespace mvk
{
    ImageImpl::ImageImpl()
    {

    }

    ImageImpl::ImageImpl(const unsigned char* data, const size_t& width, const size_t& height, const IMAGE_FORMAT& format)
    : width_(width), height_(height)
    { 
        //通道数
        switch (format)
        {
        case IMAGE_FORMAT::MONO_8_BIT:
            channels_ = 1;
            break;
        case IMAGE_FORMAT::RGB_24_BIT:
            channels_ = 3;
            break;
        default:
            assert(false);
        }
        //申请内存
        size_t data_len = width_ * height_ * channels_;
        data_ = new unsigned char[data_len];

        //拷贝数据
        std::memcpy(data_, data, data_len);
    }

    
    ImageImpl::~ImageImpl()
    {
        Release();
    }


    int ImageImpl::Read(const std::string& filename,  const IMAGE_FORMAT& format)
    {
        if(nullptr != data_) {Release();}
        try
        {
            int x  = 0;
            int y = 0;
            int channels = 0;
            switch (format)
            {
            case IMAGE_FORMAT::MONO_8_BIT:
            {
                data_ = stbi_load(filename.c_str(), &x, &y, &channels, 1);
                break;
            }
            case IMAGE_FORMAT::RGB_24_BIT:
            {
                data_ = stbi_load(filename.c_str(), &x, &y, &channels, 3);
                break;
            }
            default:
                assert(false);
            }

            width_ = x;
            height_ = y;
            channels_ = channels;
        }
        catch(const std::exception& e)
        {
            std::cerr<<"Read image failed. info: "<< e.what() << std::endl;
            return -1;
        }
        return 0;
    }


    int ImageImpl::Save(const std::string& filename)
    {
        auto len = filename.length();
        std::string format = "";
        for(auto i = len - 1; i > 0; --i)
        {
            format = filename[i] + format;
            if(filename[i] == '.'){break;}
        }

        try
        {
            if(".bmp" == format)
            {
                stbi_write_bmp(filename.c_str(), static_cast<int>(width_), static_cast<int>(height_), static_cast<int>(channels_), data_);
            }else if (".jpg" == format)
            {   
                //图片质量范围【0-100】，默认95，与opencv一致
                stbi_write_jpg(filename.c_str(), static_cast<int>(width_), static_cast<int>(height_), static_cast<int>(channels_), data_, 95);
            }else if(".png" == format)
            {
                stbi_write_png(filename.c_str(), static_cast<int>(width_), static_cast<int>(height_), static_cast<int>(channels_), data_, 0);
            }else
            {
                std::cerr<<"Save image failed. info: the {" + format + "} is not supported." << std::endl;
                return -1;
            }
        }
        catch(const std::exception& e)
        {
            std::cerr <<"Save image failed. info: " <<  e.what() << std::endl;
        }
    
        return 0;
    }


    unsigned char* ImageImpl::GetData() const
    {
        return data_;
    }


    size_t ImageImpl::GetWidth() const
    {
        return width_;
    }

    size_t ImageImpl::GetHeight() const
    {
        return height_;
    }


    size_t ImageImpl::GetChannel() const
    {
        return channels_;
    }

    int ImageImpl::Release()
    {
        delete[] data_;
        data_ = nullptr;
        return 0;
    }
    

} // namespace mvk

