/**
 * @file orthogonal_implement.hpp
 * @author mango (2321544362@qq.com)
 * @brief 基于回归正交算法直线拟合实现
 * @version 0.1
 * @date 2021-07-03
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef ORTHOGONAL_IMPLEMENT_HPP_
#define ORTHOGONAL_IMPLEMENT_HPP_

namespace mvk
{
    namespace line_fit
    {
        /**
         * @brief 基于回归正交算法直线拟合
         * 
         * @param points(in) 坐标点集合
         * @param result(out) 拟合结果 
         * @param type(in) 坐标点距离度量类型 
         * @return int 执行错误码
         */
        int OrthogonalLineFit(const std::vector<cv::Point2f>& points, LineFitResult& result, const DistType& type = DistType::DIST_L2)
        {
            if(points.size() < 2) {return -1;}

            double mean_x = 0.0;
            double mean_y = 0.0;

            //计算均值
            for(auto& p: points)
            {
                mean_x += p.x;
                mean_y += p.y;
            }
            mean_x /= points.size();
            mean_y /= points.size();

            //计算方差、协方差
            double Sxx = 0.0;
            double Syy = 0.0;
            double Sxy = 0.0;
            for(auto& p: points)
            {
                Sxx += (p.x - mean_x) * (p.x - mean_x);
                Sxy += (p.x - mean_x) * (p.y - mean_y);
                Syy += (p.y - mean_y) * (p.y - mean_y);
            }

            //一般式参数ax + by + c;
            double a = 0.0;
            double b = 0.0;
            double c = 0.0;

            bool is_vertical = (Sxy == 0) && (Sxx < Syy);
            bool is_horizontal = (Sxy == 0) && (Sxx > Syy);
            bool is_indeterminate = (Sxy == 0) && (Sxx == Syy);
            double slope = std::numeric_limits<double>::max();
            double intercept = std::numeric_limits<double>::max();

            if (is_vertical)
            {
                a = 1.0f;
                b = 0.0f;
                c = mean_x;
            }
            else if (is_horizontal)
            {
                a = 0.0f;
                b = 1.0f;
                c = mean_y;
            }
            else if (is_indeterminate)
            {
                a = 0.0;
                b = 0.0;
                c = 0.0;
                return -1;
            }
            else
            {
                slope = (Syy - Sxx + std::sqrt((Syy - Sxx) * (Syy - Sxx) + 4.0 * Sxy * Sxy)) / (2.0 * Sxy);
                intercept = mean_y - slope * mean_x;
                double norm_factor = (intercept >= 0.0 ? 1.0 : -1.0) * std::sqrt(slope * slope + 1.0);
                a = -slope / norm_factor;
                b = 1.0 / norm_factor;
                c = intercept / norm_factor;
            }
            result.a = a;
            result.b = b;
            result.c = c;
            return 0;
        }
    }//namespace line_fit
}//namespace mvk

#endif //ORTHOGONAL_IMPLEMENT_HPP_
