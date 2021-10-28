/**
 * @file rotate_rectangle_impl.h
 * @author mango (2321544362@qq.com)
 * @brief 
 * @version 0.1
 * @date 2021-08-24
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef MVK_ROTATE_RECTANGLE_IMPL_H_
#define MVK_ROTATE_RECTANGLE_IMPL_H_

#include "common/points.h"
#include "common/common_defines.h"
#include <array>

namespace mvk
{
    /**
     * @brief 旋转矩形实现类
     * 
     */
    class MVK_COMMON_EXPORT RotateRectangleImpl
    {
    private:
        std::array<Point, 4> points_;                                       ///< 矩形四个顶点
        Point center_;                                                      ///< 矩形中心点
        float width_;                                                       ///< 矩形宽度
        float height_;                                                      ///< 矩形高度
        double area_;                                                       ///< 矩形面积
        double angle_;                                                      ///< 旋转矩形角度
    public:
        RotateRectangleImpl() = delete;

        RotateRectangleImpl(const std::array<Point, 4>& points);

        ~RotateRectangleImpl();

        std::array<Point, 4> GetPoints() const;

        Point GetCenter() const;

        float GetWidth() const;

        float GetHeight() const;

        double GetArea() const;

        double GetAngle() const;
    };
    
} // namespace mvk


#endif //MVK_ROTATE_RECTANGLE_IMPL_H_
