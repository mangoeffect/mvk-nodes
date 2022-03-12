/**
 * @file gaussian_filter.hpp
 * @author mango (2321544362@qq.com)
 * @brief 高斯滤波
 * @version 0.1
 * @date 2022-03-11
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef MVK_FILTER_GAUSSIAN_FILTER_HPP_
#define MVK_FILTER_GAUSSIAN_FILTER_HPP_

#include "image/image.hpp"

namespace mvk
{
    /**
     * @brief 高斯滤波
     * 
     * @param src(in) 输入图像 
     * @param dst(out) 滤波输出图像 
     * @param kernel_size(in) 滤波核尺寸大小推荐奇数(1, 3, 5)
     * @param sigma_x(in) 高斯核函数x方向标准差系数，如果为0则由kernel_size计算
     * @param sigma_y(in) 高斯核函数x方向标准差系数，如果为0则由kernel_size计算
     * @param border_type(in) 边缘填充类型 
     * @return int 
     */
    int GaussianFilter(const Image& src, 
                       Image& dst, const size_t kernel_size, 
                       const double sigma_x = 0.0,
                       const double sigma_y = 0.0,
                       const BORDER_TYPE& border_type = BORDER_TYPE::DEFAULT);

}//namespace mvk

#endif //MVK_FILTER_GAUSSIAN_FILTER_HPP_
