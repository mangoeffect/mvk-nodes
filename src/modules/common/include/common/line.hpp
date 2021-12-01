/**
 * @file line.h
 * @author mango (2321544362@qq.com)
 * @brief 
 * @version 0.1
 * @date 2021-09-07
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef MVK_LINE_H_
#define MVK_LINE_H_

#include "common/point.hpp"

namespace mvk
{
    /**
     * @brief 直线段，使用两点表示
     * 
     */
    struct Line
    {
        Point2f p1;
        Point2f p2;
        Line(): p1(Point2f()), p2(Point2f()){}
        Line(const Point2f& p1_, const Point2f& p2_)
            :p1(p1_), p2(p2_)
        {
            
        }
    };
    
} // namespace mvk


#endif //MVK_LINE_H_
