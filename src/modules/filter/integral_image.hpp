/**
 * @file integral_image.hpp
 * @author mango (2321544362@qq.com)
 * @brief 积分图
 * @version 0.1
 * @date 2022-03-09
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef MVK_FILTER_INTEGRAL_IMAGE_HPP_
#define MVK_FILTER_INTEGRAL_IMAGE_HPP_

#include "core/mat.hpp"
#include "core/image.hpp"


namespace mvk
{
    int ComputeIntegral(Image& src, Matrix<uint64_t>& integral);
}//namespace mvk

#endif //MVK_FILTER_INTEGRAL_IMAGE_HPP_

