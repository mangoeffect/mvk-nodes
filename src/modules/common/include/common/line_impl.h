/**
 * @file line_impl.h
 * @author mango (2321544362@qq.com)
 * @brief 
 * @version 0.1
 * @date 2021-09-07
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef MVK_LINE_IMPL_H_
#define MVK_LINE_IMPL_H_

#include "common/common_defines.h"
#include "common/points.h"
#include <array>

namespace mvk
{
    class MVK_COMMON_EXPORT LineImpl
    {
    private:
        Point point1_;                                          ///< 两点式点1
        Point point2_;                                          ///< 两点式点2
        
        Point centroid_;                                        ///< 直线质心坐标
        Vector normal_;                                         ///< 直线法向量
        Vector direct_;                                         ///< 直线方向向量

        double intercept_;                                      ///< 直线截距
        double slope_;                                          ///< 直线斜率

        double a_;                                              ///< 直线一般式参数a
        double b_;                                              ///< 直线一般式参数b
        double c_;                                              ///< 直线一般式参数c  
    public:
        LineImpl(const Point& point, const Vector& direct);
        ~LineImpl();

        // ---------------------------两点式----------------------------
        void SetByTwoPointFormula(const Point& point1, const Point& point2);
        std::array<Point, 2> GetEndsPoints() const;

        // ---------------------------点法式、点向式---------------------
        void SetByPointNormalFormula(const Point& point, const Vector& normal);
        void SetByPointDirectFormula(const Point& point, const Vector& direct);
        
        Point GetPoint() const;

        Vector GetNormalVector() const;

        Vector GetDirectVector() const;

        // ----------------------------截距式---------------------------
        void SetByInterceptFormula(const double& slope, const double& intercept);
        double GetSlope() const;
        double GetIntercept() const;

        // ----------------------------一般式---------------------------
        void SetByGeneralFormula(const double& a, const double& b, const double& c);
        double GetA() const;
        double GetB() const;
        double GetC() const;

        bool HasIntersection(const LineImpl& other);

        Point GetIntersection(const LineImpl& other);
    };
        
} // namespace mvk


#endif //MVK_LINE_IMPL_H_
