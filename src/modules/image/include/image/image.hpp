/**
 * @file image.h
 * @author mango (2321544362@qq.com)
 * @brief 
 * @version 0.1
 * @date 2021-08-09
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef MVK_IMAGE_HPP_
#define MVK_IMAGE_HPP_

#include "image/image_defines.hpp"
#include "common/point.hpp"
#include "common/mat.hpp"
#include <string>
#include <memory>
#include <array>

namespace mvk
{
    class ImageImpl;                                                    ///< Image实现类声明

    /**
     * @brief 图像数据模块
     * 
     */
    class MVK_IMAGE_EXPORT Image
    {
    private:
        std::shared_ptr<ImageImpl> image_impl_;                         ///< image类实现对象
    public:
        /**
         * @brief 默认构造
         * 
         */
        Image();

        /**
         * @brief 构造函数
         * 
         * @param data(in) 图像数据
         * @param width(in) 图像宽度
         * @param height(in) 图像长度
         * @param format(in) 图像格式类型 
         */
        Image(uint8_t* data, const size_t& width, const size_t& height, const IMAGE_FORMAT& format);

        /**
         * @brief 构造函数，构造单通道图像
         * 
         * @param width(in) 图像宽度
         * @param height(in) 图像高度 
         * @param init_value(in) 像素初始值
         */
        Image(const size_t& width, const size_t& height, const uint8_t init_value = 0);

        
        Image(const size_t& width, const size_t& height, const std::array<uint8_t, 3>& init_value = {0, 0, 0});

        /**
         * @brief 构造函数，基于矩阵数据构造图像
         * 
         * @param matrix(in) uint8_t数据类型矩阵
         */
        Image(const Matrix<uint8_t>& matrix, const size_t channel);

        /**
         * @brief 深拷贝图像
         * 
         * @return Image 
         */
        Image Copy() const;


        /**
         * @brief 深拷贝图像填充边界
         * 
         * @param border_size(in) 填充边界大小
         * @param border_type(in) 边界类型 
         * @param const_border(in) 边界数值，边界类型选择常数时生效
         * @return Image 
         */
        Image CopyWithBorder(const size_t border_size, 
                             const BORDER_TYPE& border_type = BORDER_TYPE::DEFAULT, 
                             const std::array<uint8_t, 3>& const_border = {0, 0, 0}) const;
        
        ~Image();

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
        uint8_t* GetData() const;
        
        /**
         * @brief 获取行指针
         * 
         * @param rows(in) 行号索引 
         * @return uint8_t* 
         */
        uint8_t* GetRow(const size_t& rows) const;

        /**
         * @brief 返回像素的坐标指针
         * 
         * @param rows 
         * @param cols 
         * @return uint8_t* 
         */
        uint8_t* GetPixel(const size_t& rows, const size_t& cols) const;

        /**
         * @brief 返回像素的坐标指针
         * 
         * @param p(in) 坐标点 
         * @return uint8_t* 
         */
        uint8_t* GetPixel(const Point2i& p);

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

#endif //MVK_IMAGE_H_
