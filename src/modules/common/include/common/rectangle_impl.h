/**
 * @file rectangle_impl.h
 * @author mango (2321544362@qq.com)
 * @brief 
 * @version 0.1
 * @date 2021-08-21
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef MVK_RECTANGLE_IMPL_H_
#define MVK_RECTANGLE_IMPL_H_

#include <array>
#include "common/points.h"
#include "common/common_defines.h"


namespace mvk
{
    /**
     * @brief 矩形类实现
     * 
     */
    class MVK_COMMON_EXPORT RectangleImpl
    {
    private:
        std::array<Point, 4> points_;                                       ///< 矩形四个顶点
        Point center_;                                                      ///< 矩形中心点
        float width_;                                                       ///< 矩形宽度
        float height_;                                                      ///< 矩形高度
        double area_;                                                       ///< 矩形面积
    public:
         /**
         * @brief 默认构造
         * 
         */
        RectangleImpl() = delete;

        /**
         * @brief 构造函数
         * 
         * @param top_left(in) 矩形左上角顶点坐标 
         * @param width(in) 矩形宽度 
         * @param height(in) 矩形高度 
         */
        RectangleImpl(const Point& top_left, const float& width, const float& height);

        /**
         * @brief 构造函数
         * 
         * @param top_left(in) 矩形左上角顶点坐标 
         * @param bottom_right(in) 矩形右下角顶点坐标 
         */
        RectangleImpl(const Point& top_left, const Point& bottom_right);

        /**
         * @brief 析构函数
         * 
         */
        ~RectangleImpl();

        /**
         * @brief 获取矩形宽度
         * 
         * @return float 
         */
        float GetWidth() const;

        /**
         * @brief 获取矩形高度
         * 
         * @return float 
         */
        float GetHeight() const;

        /**
         * @brief 获取矩形面积
         * 
         * @return double 
         */
        double GetArea() const;

        /**
         * @brief 获取矩形中心点坐标
         * 
         * @return Point 
         */
        Point GetCenter() const;

        /**
         * @brief 获取矩形左上角顶点坐标
         * 
         * @return Point 
         */
        Point GetTopleft() const;

        /**
         * @brief 获取矩形右上角顶点坐标
         * 
         * @return Point 
         */
        Point GetTopRight() const;

        /**
         * @brief 获取矩形右下角顶点坐标
         * 
         * @return Point 
         */
        Point GetBottomRight() const;

        /**
         * @brief 获取矩形左下角顶点坐标
         * 
         * @return Point 
         */
        Point GetBottomLeft() const;

        /**
         * @brief 获取矩形四个顶点坐标，顺序为左上-右上-右下-左下
         * 
         * @return std::array<Point, 4> 
         */
        std::array<Point, 4> GetPoints() const;

        /**
         * @brief 求取两个矩形交集
         * 
         * @param other(in) 另一个矩形
         * @return RectangleImpl 
         */
        RectangleImpl operator& (const RectangleImpl& other) const;

        /**
         * @brief 求取两个矩形并集
         * 
         * @param other 
         * @return Rectangle 
         */
        RectangleImpl operator| (const RectangleImpl& other) const;
    };
    
    

} // namespace mvk


#endif //MVK_RECTANGLE_IMPL_H_

