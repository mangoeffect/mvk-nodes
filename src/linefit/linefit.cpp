//
// Created by mango on 4/10/2020.
//

#include "linefit.h"

#include <cassert>



cv::Ptr<mv::LineFit> mv::LineFit::CreateInstance(const std::vector<cv::Point2d> &points, const FitAlgorithms &fitAlgorithms)
{
    return  cv::makePtr<mv::LineFit>(points, fitAlgorithms);
}//CreateInstance

void mv::LineFit::Run()
{
    switch (_fitAlgorithms)
    {
        case FitAlgorithms ::REGRESSION:
            FitLineByRegression();
            break;
        case FitAlgorithms ::HUBER:
            FitLineByHuber();
            break;
        case FitAlgorithms ::TUKEY:
            FitLineByTukey();
            break;
        case FitAlgorithms ::DROP:
            FitLineByDrop();
            break;
        case FitAlgorithms ::GAUSS:
            FitLineByGauss();
            break;
        default:
            assert(false);
    }
}//Run

void mv::LineFit::FitLineByRegression()
{
    // 设置权重 | weights setting
    _weigths = std::vector<double>(_points.size(), 1);

    // AX = B
    // 构造A矩阵 | Construct A mat
    const int N = 2;
    cv::Mat A = cv::Mat::zeros(N, N, CV_64FC1);

    for (int row = 0;row < A.rows;row++)
    {
        for (int col = 0; col < A.cols;col++)
        {
            for (int k = 0;k < _points.size();k++)
            {
                A.at<double>(row, col) = A.at<double>(row, col) + pow(_points[k].x, row + col) * _weigths[k];
            }
        }
    }

    //构造B矩阵 | Construct B mat
    cv::Mat B = cv::Mat::zeros(N, 1, CV_64FC1);
    for (int row = 0;row < B.rows;row++)
    {

        for (int k = 0;k < _points.size();k++)
        {
            B.at<double>(row, 0) = B.at<double>(row, 0) + pow(_points[k].x, row)*_points[k].y * _weigths[k];
        }
    }

    // 求解A*X = B | Solve the A*X = B
    cv::Mat X;
    cv::solve(A, B, X,cv::DECOMP_LU);

    // y = b + ax
    _result.b = X.at<double>(0,0);
    _result.a = X.at<double>(1, 0);

}//FitLineByRegression

void mv::LineFit::FitLineByHuber()
{

}//FitLineByHuber

void mv::LineFit::FitLineByTukey()
{

}//FitLineByTukey

void mv::LineFit::FitLineByDrop()
{

}//FitLineByDrop


void mv::LineFit::FitLineByGauss()
{

}//FitLineByGauss


mv::LineFitResult mv::LineFit::GetResult() const
{
    return this->_result;
}//GetResult