/**
 * @file box_filter.hpp
 * @author mango (2321544362@qq.com)
 * @brief 
 * @version 0.1
 * @date 2022-03-08
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef MVK_FILTER_BOX_FILTER_HPP_
#define MVK_FILTER_BOX_FILTER_HPP_

#include "image/image.hpp"
#include "common/common_defines.hpp"

namespace mvk
{
    /**
    * @brief 方框滤波
    * 
    * @param src 
    * @param dst 
    * @param kernel_size 
    * @param border_type 
    * @return int 
    */
    int BoxFilter(const Image& src, Image& dst, const size_t kernel_size, const BORDER_TYPE& border_type = BORDER_TYPE::DEFAULT);
}//

#endif //MVK_FILTER_BOX_FILTER_HPP_
