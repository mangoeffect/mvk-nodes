/**
 * @file points.h
 * @author mango (2321544362@qq.com)
 * @brief 2d坐标点类型
 * @version 0.1
 * @date 2021-08-21
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef MVK_POINTS_H_
#define MVK_POINTS_H_

#include <memory>
#include "common/common_defines.h"

namespace mvk
{
    class MVK_COMMON_EXPORT PointImpl;                            ///Point实现类声明
    /**
     * @brief 2d坐标点类实现
     * 
     */
    class MVK_COMMON_EXPORT Point
    {  
    private:
        std::shared_ptr<PointImpl> point_impl_;                 ///< points实现类     
    public:
        /**
         * @brief 默认构造函数
         * 
         */
        Point();

        /**
         * @brief 构造函数
         * 
         * @param point_impl 
         */
        Point(const std::shared_ptr<PointImpl>& point_impl);


        /**
         * @brief 构造函数
         * 
         * @param x(in) 横坐标初值 
         * @param y(in) 纵坐标初值 
         */
        Point(const float& x, const float& y);

        /**
         * @brief 析构函数
         * 
         */
        ~Point();

        /**
         * @brief 由坐标点表示的两个向量点乘， x1 * y1 + x2 * y2
         * 
         * @param other(in) 另一个坐标点 
         * @return float 点乘结果
         */
        float Dot(const Point& other);

        /**
         * @brief 由坐标点表示的两个向量点乘， x1 * y1 + x2 * y2
         * 
         * @param other(in) 另一个坐标点 
         * @return double 点乘结果
         */
        double Ddot(const Point& other);

        /**
         * @brief 两坐标点相加
         * 
         * @param other(in) 另一个坐标点 
         * @return Point 
         */
        Point operator + (const Point& other);

        /**
         * @brief 两坐标点相减
         * 
         * @param other(in) 另一个坐标点 
         * @return Point 
         */
        Point operator - (const Point& other);

        /**
         * @brief 返回横坐标X值
         * 
         * @return float 
         */
        float GetX() const;

        /**
         * @brief 返回纵坐标Y值
         * 
         * @return float 
         */
        float GetY() const;

        /**
         * @brief 设置横坐标X值
         * 
         * @param x 
         */
        void SetX(const float& x);

        /**
         * @brief 设置纵坐标Y值
         * 
         * @param y 
         */
        void SetY(const float& y);
    };
    
    using Vector = Point;
} // namespace mvk


#endif //MVK_POINTS_H_

