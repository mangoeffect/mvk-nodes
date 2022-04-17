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
#include "filter/filter_defines.hpp"

namespace mvk
{
    /**
    * @brief 方框滤波
    * 
    * @param src(in) 输入图像 
    * @param dst(out) 滤波输出图像 
    * @param kernel_size(in) 滤波核尺寸大小推荐奇数(1, 3, 5)
    * @param border_type(in) 边缘填充类型
    * @return int 
    */
    MVK_FILTER_EXPORT int BoxFilter(const Image& src, Image& dst, const size_t kernel_size, const BORDER_TYPE& border_type = BORDER_TYPE::DEFAULT);
}//

#endif //MVK_FILTER_BOX_FILTER_HPP_
