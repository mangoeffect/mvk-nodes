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
    template<typename T>
    struct Line
    {
        Point<T> p1;
        Point<T> p2;
        Line(): p1(Point<T>()), p2(Point<T>()){}
        Line(const Point<T>& p1_, const Point<T>& p2_)
            :p1(p1_), p2(p2_)
        {
            
        }
    };

    template<typename T>
    bool IsOrthogonal(const Line<T>& l1, const Line<T>& l2)
    {
        Point<T> v1(l1.p1.x - l1.p2.x, l1.p1.y, l1.p2.y);
        Point<T> v2(l2.p1.x - l2.p2.x, l2.p1.y, l2.p2.y);
        return DotProduct<T>(v1, v2) == 0;
    }
    
} // namespace mvk


#endif //MVK_LINE_H_
