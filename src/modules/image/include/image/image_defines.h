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

#ifndef MVK_IMAGE_DEFINES_H_
#define MVK_IMAGE_DEFINES_H_

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

    #ifdef MVK_IMAGE_STATIC_DEFINE
    #  define MVK_IMAGE_EXPORT
    #  define MVK_IMAGE_NO_EXPORT
    #else
    #  ifndef MVK_IMAGE_EXPORT
    #    ifdef MVK_IMAGE_EXPORTS
            /* 正在编译 */
    #      define MVK_IMAGE_EXPORT __declspec(dllexport)
    #    else
            /* 正在使用 */
    #      define MVK_IMAGE_EXPORT __declspec(dllimport)
    #    endif
    #  endif

    #  ifndef MVK_IMAGE_NO_EXPORT
    #    define MVK_IMAGE_NO_EXPORT 
    #  endif
    #endif
} // namespace mvk


#endif //MVK_IMAGE_DEFINES_H_
