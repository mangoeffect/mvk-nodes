/**
 * @file image_defines.h
 * @author mango (2321544362@qq.com)
 * @brief image类一些公共定义
 * @version 0.1
 * @date 2021-08-17
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef MVK_IMAGE_DEFINES_HPP_
#define MVK_IMAGE_DEFINES_HPP_

#ifndef BUILD_STATIC_LIB
  #include "mvk_image_export.hpp"
#endif 

namespace mvk
{
    /**
     * @brief 图像格式类型
     * 
     */
    enum class IMAGE_FORMAT
    {
        MONO_8_BIT = 0,                     ///< 单通道8比特灰度图像
        RGB_24_BIT = 1,                     ///< RGB三通道24比特彩色图像
    };// enum class IMAGE_FORMAT


    /**
     * @brief 填充边界的类型
     * 
     */
    enum class BORDER_TYPE
    {
        DEFAULT = 0,            ///<默认 镜像， 123 | 321
        CONSTANT = 1,           ///<常数填充，  123 | ccc
        REPLICATE = 2,          ///<边界复制,   123 | 333
    };
} // namespace mvk


#endif //MVK_IMAGE_DEFINES_HPP_
