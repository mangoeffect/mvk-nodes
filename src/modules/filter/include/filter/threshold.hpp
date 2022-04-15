/**
 * @file threshold.hpp
 * @author mango (2321544362@qq.com)
 * @brief 阈值化处理
 * @version 0.1
 * @date 2022-04-15
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef MVK_FILTER_THRESHOLD_HPP_
#define MVK_FILTER_THRESHOLD_HPP_

#include "image/image.hpp"
#include "filter/filter_defines.hpp"

namespace mvk
{
    /**
    * @brief 阈值化类型
    * 
    */
    enum class THRESHOLD_TYPE
    {
        THRESH_BINARY = 0,                  ///< if src > t  dst = 255 else dst = 0
        THRESH_BINARY_INV = 1,              ///< if src > t  dst = 0 else dst = 255
        THRESH_TRUNC = 2,                   ///< if src > t  dst = t else dst = src
        THRESH_TOZERO = 3,                  ///< if src > t  dst = src else dst = 0
        THRESH_TOZERO_INV = 4               ///< if src > t  dst = 0 else dst = src
    };

    /**
     * @brief 阈值化处理图像，图像灰度值最大为255
     * 
     * @param src(in) 输入图像 
     * @param dst(out) 输出图像 
     * @param thresh(in) 阈值 
     * @param type(in) 阈值化类型， 详情参考@class THRESHOLD_TYPE "threshold.hpp"
     * @return int 
     */
    MVK_FILTER_EXPORT int Threshold(const Image& src, Image& dst, const uint8_t thresh, const THRESHOLD_TYPE type = THRESHOLD_TYPE::THRESH_BINARY);
} //namespace mvk

#endif //MVK_FILTER_THRESHOLD_HPP_
