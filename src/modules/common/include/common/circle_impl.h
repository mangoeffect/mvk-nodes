/**
 * @file circle_impl.h
 * @author mango (2321544362@qq.com)
 * @brief 
 * @version 0.1
 * @date 2021-08-21
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef MVK_CIRCLE_IMPL_H_
#define MVK_CIRCLE_IMPL_H_

#include "common/points.h"

namespace mvk
{
    /**
     * @brief 圆形实现类
     * 
     */
    class CircleImpl
    {
    private:
        Point center_;
        float radius_;
        double area_;
    public:
        CircleImpl(/* args */) = delete;

        CircleImpl(const Point& center, const float& radius);
        
        ~CircleImpl();

        double GetArea() const;

        float GetRadius() const;

        Point GetCenter() const;
    };

} // namespace mvk


#endif //MVK_CIRCLE_IMPL_H_
