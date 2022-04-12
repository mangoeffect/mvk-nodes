/**
 * @file common_defines.hpp
 * @author mango (2321544362@qq.com)
 * @brief 
 * @version 0.1
 * @date 2022-03-02
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef MVK_COMMON_DEFINES_HPP_
#define MVK_COMMON_DEFINES_HPP_

#ifndef BUILD_STATIC_LIB
  #include "mvk_common_export.hpp"
#endif 
#if __cplusplus >= 202003L
#include <numbers>
#endif 

namespace mvk
{
    #if __cplusplus >= 202003L
        #define MVK_PI std::numbers::pi
    #else 
        #define MVK_PI 3.1415926
    #endif

    /**
     * @brief 分解矩阵方法
     * 
     */
    enum class MATRIX_SOLVE_METHOD
    {
        LU = 0,
        SVD = 1
    };
}//namespace mvk

#endif 
