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

#include "common/mat.hpp"
#include "image/image.hpp"
#include "filter/filter_defines.hpp"


namespace mvk
{
    MVK_FILTER_EXPORT int ComputeIntegral(const Image& src, Matrix<uint64_t>& integral);
}//namespace mvk

#endif //MVK_FILTER_INTEGRAL_IMAGE_HPP_

