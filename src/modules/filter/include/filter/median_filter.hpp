/**
 * @file median_filter.hpp
 * @author mango (2321544362@qq.com)
 * @brief 中值滤波
 * @version 0.1
 * @date 2022-03-31
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef MVK_FILTER_MEDIAN_FILTER_HPP_
#define MVK_FILTER_MEDIAN_FILTER_HPP_

#include "image/image.hpp"
#include "filter/filter_defines.hpp"


namespace mvk
{
    /**
     * @brief 中值滤波
     * 
     * @param src(in) 输入图像  
     * @param dst(out) 滤波输出图像
     * @param kernel_size(in) 滤波核大小
     * @param border_type(in) 边缘填充类型 
     * @return int 
     */
    MVK_FILTER_EXPORT int MedianFilter(const Image& src,
                     Image& dst,
                     const size_t kernel_size,
                     const BORDER_TYPE& border_type = BORDER_TYPE::DEFAULT);

    /**
     * @brief 3x3范围的小半径中值滤波，做特殊效率优化
     * 
     * @param src(in) 输入图像
     * @param dst(out) 输出图像
     * @return int 
     */
    MVK_FILTER_EXPORT int MedianFilter3x3(Image& src, Image& dst);

    /**
     * @brief 5x5范围的小半径中值滤波，做特殊效率优化
     * 
     * @param src(in) 输入图像
     * @param dst(out) 输出图像
     * @return int 
     */
    MVK_FILTER_EXPORT int MedianFilter5x5(Image& src, Image& dst);
}//namespace mvk

#endif //MVK_FILTER_MEDIAN_FILTER_HPP_
