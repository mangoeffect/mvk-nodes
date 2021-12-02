/**
 * @file rectangle.h
 * @author mango (2321544362@qq.com)
 * @brief 矩形相关定义
 * @version 0.1
 * @date 2021-08-21
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef MVK_RECTANGLE_H_
#define MVK_RECTANGLE_H_

#include "common/point.hpp"
#include <array>
#include <algorithm>

namespace mvk
{
    /**
     * @brief 
     * 
     */
   template<typename T = float>
   struct Rect
   {
       Point<T> topleft;
       Point<T> topright;
       Point<T> bottomright;
       Point<T> bottomleft;

       T width;
       T height;
       
       /**
        * @brief Construct a new Rect object
        * 
        * @param tl 
        * @param width 
        * @param height 
        */
       Rect(const Point<T>& tl,
            const T& width,
            const T& height);
       
       /**
        * @brief Construct a new Rect object
        * 
        * @param tl 
        * @param br 
        */
       Rect(const Point<T>& tl,
            const Point<T>& br);
   };

    template<typename T>
    Rect<T>::Rect(const Point<T>& tl,
        const T& width,
        const T& height)
    
    {
        topright = topleft = topleft;
        topright.x += width;
        bottomright = Point<T>(topleft.x + width, topleft.y + height);
        bottomleft = bottomright;
        bottomleft.x = topleft.x;

        this->width = width;
        this->height = height;
    }
    
    template<typename T>
    Rect<T>::Rect(const Point<T>& tl,
        const Point<T>& br)
    {
        float width = br.x - tl.x;
        float height = br.y - tl.y;
        Rect(tl, width, height); 
    }

    /**
    * @brief 获取矩形框的中心点坐标
    * 
    * @param rect(in) 矩形 
    * @return Point2f 
    */
    template<typename T>
    Point<T> GetRectCenter(const Rect<T>& rect)
    {
        return Point<T>(0.5 * (rect.topleft.x + rect.bottomright.x), 
                        0.5 * (rect.topleft.y + rect.bottomright.y));
    }

    template<typename T>
    bool IsRectangleOrdered(const Point<T>& a,
                     const Point<T>& b, 
                     const Point<T>& c,
                     const Point<T>& d)
    {
        return IsOrthogonal<T>(a, b, c) && IsOrthogonal<T>(b, c, d) && IsOrthogonal<T>(c, d, a);
    }

    template<typename T>
    bool IsRectangle(const Point<T>& a,
                     const Point<T>& b, 
                     const Point<T>& c,
                     const Point<T>& d)
    {
        return IsRectangleOrdered<T>(a, b, c, d) ||
               IsRectangleOrdered<T>(b, c, a, d) ||
               IsRectangleOrdered<T>(c, a, b, d);
    }

    template<typename T>
    bool IsRectangle(const std::array<Point<T>, 4>& points)
    {
        return IsRectangle<T>(points[0], points[1], points[2], points[3]);
    }
} // namespace mvk


#endif //MVK_RECTANGLE_H_

