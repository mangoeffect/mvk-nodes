/**
 * @file common_defines.h
 * @author mango (2321544362@qq.com)
 * @brief common模块类型定义
 * @version 0.1
 * @date 2021-08-21
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef MVK_COMMON_H_
#define MVK_COMMON_H_

namespace mvk
{
    #ifdef MVK_COMMON_STATIC_DEFINE
    #  define MVK_COMMON_EXPORT
    #  define MVK_COMMON_NO_EXPORT
    #else
    #  ifndef MVK_COMMON_EXPORT
    #    ifdef MVK_COMMON_EXPORTS
            /* 正在编译 */
    #      define MVK_COMMON_EXPORT __declspec(dllexport)
    #    else
            /* 正在使用 */
    #      define MVK_COMMON_EXPORT __declspec(dllimport)
    #    endif
    #  endif

    #  ifndef MVK_COMMON_NO_EXPORT
    #    define MVK_COMMON_NO_EXPORT 
    #  endif
    #endif

    constexpr double MVK_PI = 3.1415926535897932384626;       ///< 定义pi值

   /**
     * @brief 边缘像素极性
     * 
     */
    enum class Polarity
    {
        BLACK_TO_WHITE = 0,
        WHITE_TO_BLACK = 1
    };
    
} // namespace mvk


#endif //MVK_COMMON_H_
