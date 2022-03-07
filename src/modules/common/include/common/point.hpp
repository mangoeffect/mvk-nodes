/**
 * @file point.hpp
 * @author mango (2321544362@qq.com)
 * @brief 2d坐标点类型
 * @version 0.1
 * @date 2021-08-21
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef MVK_POINT_HPP_
#define MVK_POINT_HPP_

#include <memory>

namespace mvk
{
    /**
     * @brief 二维坐标点
     * 
     */
    template<typename T = float>
    struct Point
    {
        T x;
        T y;
        Point(): x(0), y(0){}
        Point(const T& x_, const T& y_): x(x_), y(y_){}

        /**
         * @brief 坐标点乘
         * 
         * @param other(in) 另一个
         * @return T 
         */
        T Dot(const Point& other) const;

        /**
         * @brief 坐标相减
         * 
         * @param other(in) 另一个坐标点
         * @return Point 
         */
        Point operator - (const Point& other) const;

        /**
         * @brief 坐标相加
         * 
         * @param other(in) 另一个坐标点
         * @return Point 
         */
        Point operator + (const Point& other) const;
    };

    using Point2f = Point<float>;
    using Point2d = Point<double>;
    using Point2i = Point<int>;    

    template<typename T>
    T Point<T>::Dot(const Point& other) const
    {
        return x * other.x + y * other.y;
    }

    template<typename T>
    Point<T> Point<T>::operator - (const Point& other) const
    {
        return Point<T>(x - other.x, y - other.y);
    }

    template<typename T>
    Point<T> Point<T>::operator + (const Point& other) const
    {
        return Point<T>(x + other.x, y + other.y);
    }

    /**
     * @brief 判断直线段ab与bc是否正交，即判断角abc是否为直角
     * 
     * @tparam T 
     * @param a(in) 直线段坐标点a 
     * @param b(in) 直线段坐标点b 
     * @param c(in) 直线段坐标点c 
     * @return true 
     * @return false 
     */
    template<typename T>
    bool IsOrthogonal(const T& a,
                        const T& b,
                        const T& c)
    {
        T vba = b - a;
        T vbc = b - c;
        return vba.Dot(vbc) == 0;
    }
    
} // namespace mvk


#endif //MVK_POINT_HPP_

