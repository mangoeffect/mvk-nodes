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
    T DotProduct(const Point<T>& p1, const Point<T>& p2);
} // namespace mvk


#endif //MVK_POINT_HPP_

