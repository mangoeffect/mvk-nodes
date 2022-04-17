/**
 * @file sobel.hpp
 * @author mango (2321544362@qq.com)
 * @brief 索贝尔算子实现
 * @version 0.1
 * @date 2022-04-02
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef MVK_FILTER_SOBEL_HPP_
#define MVK_FILTER_SOBEL_HPP_

#include "image/image.hpp"
#include "filter/filter_defines.hpp"
#include "common/mat.hpp"

namespace mvk
{
    /**
     * @brief 3x3索贝尔算子实现
     * 
     * @param src(in) 输入图像 
     * @param dst(out) 输出图像， dst = sqrt(Gx*Gx + Gy*Gy)
     * @param Gx(out) x方向模板卷积结果，数据类型为float
     * @param Gy(out) y方向模板卷积结果，数据类型为float 
     * @return int 
     */
    MVK_FILTER_EXPORT int Sobel(const Image& src, Image& dst, Matrix<float>& Gx, Matrix<float>& Gy);
}//namespace mvk

#endif //MVK_FILTER_SOBEL_HPP_
