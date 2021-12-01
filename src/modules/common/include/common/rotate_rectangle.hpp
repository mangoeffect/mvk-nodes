/**
 * @file rotate_rectangle.hpp
 * @author mango (2321544362@qq.com)
 * @brief 旋转矩形类
 * @version 0.1
 * @date 2021-08-24
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef MVK_ROTATE_RECTANGLE_HPP_
#define MVK_ROTATE_RECTANGLE_HPP_

#include "common/point.hpp"
#include <array>

namespace mvk
{
    /**
     * @brief 旋转矩形
     * 
     */
    struct RotateRect
    {
        std::array<Point2f, 4> points;
    };
    
} // namespace mvk

#endif //MVK_ROTATE_RECTANGLE_H_
