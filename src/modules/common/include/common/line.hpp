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

        /**
         * @brief 判断两直线是否垂直
         *
         * @param other 
         * @return true 
         * @return false 
         */
        bool IsOrthogonal(const Line<T>&  other) const;

        /**
         * @brief 
         * 
         * @param other 
         * @return true 
         * @return false 
         */
        bool IsParallel(const Line<T>& other) const;
    };

    template<typename T>
    bool Line<T>::IsOrthogonal(const Line<T>&  other) const 
    {
        Point<T> v1  = p1 - p2;
        Point<T> v2 =  other.p1 - other.p2;
        return v1.Dot(v2) == 0;
    }
    
} // namespace mvk


#endif //MVK_LINE_H_
