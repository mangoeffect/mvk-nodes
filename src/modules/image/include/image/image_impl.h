/**
 * @file image_impl.h
 * @author mango (2321544362@qq.com)
 * @brief image类的实现类
 * @version 0.1
 * @date 2021-08-17
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef MVK_IMAGE_IMPL_H_
#define MVK_IMAGE_IMPL_H_

#include "image/image_defines.h"
#include <string>

namespace mvk
{
    class ImageImpl
    {
    private:
        size_t width_{0};                    ///< 图像宽度
        size_t height_{0};                   ///< 图像高度
        size_t channels_{0};                 ///< 图像通道数
        unsigned char* data_{nullptr};       ///< 图像数据
    public:
        ImageImpl() = delete;

        ~ImageImpl();

        /**
         * @brief 构造函数
         * 
         * @param data(in) 图像数据
         * @param width(in) 图像宽度
         * @param height(in) 图像长度
         * @param format(in) 图像格式类型 
         */
        ImageImpl(const unsigned char* data, const size_t& width, const size_t& height, const IMAGE_FORMAT& format);
        

        /**
         * @brief 读取图像文件
         * 
         * @param filename(in) 图像文件名名称 
         * @param format(in) 图像格式类型 
         * @return int 执行错误码，0为正常值
         */
        int Read(const std::string& filename,  const IMAGE_FORMAT& format);

        /**
         * @brief 保存图像至本地文件
         * 
         * @param filename(in) 文件名称
         * @return int 执行错误码，0为正常值
         */
        int Save(const std::string& filename);

        /**
         * @brief 获取图像数据
         * 
         * @return char* 数据指针首地址
         */
        unsigned char* GetData() const;

        /**
         * @brief 获取图像宽度
         * 
         * @return size_t 
         */
        size_t GetWidth() const;

        /**
         * @brief 获取图像高度
         * 
         * @return size_t 
         */
        size_t GetHeight() const;

        /**
         * @brief 获取图像通道数
         * 
         * @return size_t 
         */
        size_t GetChannel() const;

        /**
         * @brief 释放图像内存
         * 
         * @return int 执行错误码，0为正常值
         */
        int Release();
    };

    
} // namespace mvk

#endif //MVK_IMAGE_IMPL_H_
