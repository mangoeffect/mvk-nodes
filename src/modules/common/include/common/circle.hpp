/**
 * @file circle.h
 * @author mango (2321544362@qq.com)
 * @brief 
 * @version 0.1
 * @date 2021-08-21
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef MVK_CIRCLE_H_
#define MVK_CIRCLE_H_

#include "common/point.hpp"
#include "common/common_defines.hpp"

namespace mvk
{    
    /**
     * @brief 圆形类
     * 
     */
    struct Circle
    {
        Point2f center;                 ///< 圆心
        float radius;                   ///< 半径
        Circle(const Point2f& center_, const float& radius_)
        : center(center_), radius(radius_){}
    };
    
    /**
     * @brief 计算圆形面积
     * 
     * @param circle(in) 圆形 
     * @return double 
     */
    MVK_COMMON_EXPORT double GetCircleArea(const Circle& circle);
} // namespace mvk


#endif //MVK_CIRCLE_H_

