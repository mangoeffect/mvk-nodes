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
    };

    using Point2f = Point<float>;
    using Point2d = Point<double>;
    using Point2i = Point<int>;    

    template<typename T>
    T DotProduct(const Point<T>& p1, const Point<T>& p2)
    {
        return p1.x * p2.x + p1.y * p2.y;
    }

    /**
     * @brief 判断直线段ab与ab是否正交，即判断角abc是否为直角
     * 
     * @tparam T 
     * @param a 
     * @param b 
     * @param c 
     * @return true 
     * @return false 
     */
    template<typename T>
    bool IsOrthogonal(const Point<T>& a,
                        const Point<T>& b,
                        const Point<T>& c)
    {
        Point<T> vba((b.x - a.x), (b.y - a.y));
        Point<T> vbc((b.x - c.x), (b.y - c.y));
        return DotProduct<T>(vba, vbc) == 0;
    }
    
} // namespace mvk


#endif //MVK_POINT_HPP_

