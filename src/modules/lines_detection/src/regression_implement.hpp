/**
 * @file regression_implement.hpp
 * @author mango (2321544362@qq.com)
 * @brief 基于标准残差回归算法直线拟合实现
 * @version 0.1
 * @date 2021-07-03
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef REGRESSION_IMPLEMENT_HPP_
#define REGRESSION_IMPLEMENT_HPP_

#include "line_fit.h"

namespace mvk
{
    namespace line_fit
    {
        /**
         * @brief 基于标准残差回归算法直线拟合实现
         * 
         * @param points(in) 输入点集 
         * @param result(out) 拟合结果 
         * @param type(in) 点坐标距离度量类型 
         * @return int 执行错误码
         */
        int RegressionLineFit(const std::vector<cv::Point2f>& points, LineFitResult& result, const DistType& type = DistType::DIST_L2)
        {
            if(points.size() < 2) {return -1;}

             // 设置权重 | weights setting
            auto weigths = std::vector<double>(points.size(), 1);

            // AX = B
            // 构造A矩阵
            const int N = 2;
            cv::Mat A = cv::Mat::zeros(N, N, CV_64FC1);

            for (int row = 0;row < A.rows;row++)
            {
                for (int col = 0; col < A.cols;col++)
                {
                    for (int k = 0;k < points.size();k++)
                    {
                        A.at<double>(row, col) = A.at<double>(row, col) + pow(points[k].x, row + col) * weigths[k];
                    }
                }
            }

            //构造B矩阵
            cv::Mat B = cv::Mat::zeros(N, 1, CV_64FC1);
            for (int row = 0;row < B.rows;row++)
            {
                for (int k = 0;k < points.size();k++)
                {
                    B.at<double>(row, 0) = B.at<double>(row, 0) + pow(points[k].x, row)*points[k].y * weigths[k];
                }
            }

            // 求解A*X = B
            cv::Mat X;
            cv::solve(A, B, X,cv::DECOMP_LU);

            // y = b + ax
            result.b = X.at<double>(0,0);
            result.a = X.at<double>(1, 0);

            return 0;
        }
    }//namespace line_fit
}//namespace mvk

#endif //REGRESSION_IMPLEMENT_HPP_
