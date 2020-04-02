//
// Created by $mango on 4/2/2020.
//

#include "caliper.h"

#include <cmath>

mv::Caliper::Caliper(const cv::Point2d _center, const size_t _len, const double _k, const size_t _filterSize)
: center(_center) , len(_len), k(_k), filterSize(_filterSize)
{

}//Caliper

void mv::Caliper::Init(cv::Mat _inputImage)
{
    if(_inputImage.channels() > 1)
        cv::cvtColor(_inputImage, inputImage, cv::COLOR_BGR2GRAY);
    else
        inputImage = _inputImage;
}//Init

cv::Ptr<mv::Caliper> mv::Caliper::CreateInstance(const cv::Point2d center, const size_t len, const double k, const size_t filterSize)
{
    return  cv::makePtr<mv::Caliper>(center, len, k, filterSize);
}//CreateInstance

void mv::Caliper::SearchCaliperPath()
{
    CV_Assert(!inputImage.empty() && inputImage.channels() == 1);
    //1. 初始化卡尺路径直线方程
    angle = std::tan(k);
    // b = y - kx
    b = center.y - k * center.x;
    //2. 求取搜索起始点
    min_x = center.x - len * std::cos(angle) * 0.5;
    if (min_x < 0) return;
    max_x = center.x - len * std::cos(angle) * 0.5;

    //3. 从起始点搜索，保存卡尺路径点集
    path.clear();
    pathPixelValue.clear();
    // y = kx + b;
    double y = 0;
    for (int i = min_x; i < max_x; ++i)
    {
        y = i * k + b;
        path.push_back(cv::Point2d(i, y));
        pathPixelValue.push_back(inputImage.at<uchar>(y, i));
    }
}//SearchCaliperPath

void mv::Caliper::DifferenceFilter(const size_t &_filterSize)
{
    //1. 构造滤波核: [-1,-1...0...1,1]
    std::vector<int> filter(2 * _filterSize + 1, 1);
    for (int i = 0; i < _filterSize; ++i)
    {
        filter[i] = -1;
    }
    filter[_filterSize] = 0;

    //2. 滤波核滑动滤波，逐一相乘求和（省去反转的一维卷积）
    pathPixelValueAfterFilter.clear();
    pathPixelValueAfterFilter.assign(pathPixelValue.begin(), pathPixelValue.end());
    for (int j = _filterSize; j < pathPixelValue.size() - _filterSize; ++j)
    {
        int sum = 0.0;
        for (int i = 0; i < filter.size(); ++i)
        {
            sum += pathPixelValue.at(j - _filterSize + i) * filter.at(i);
        }
        pathPixelValueAfterFilter.at(j) = sum;
    }
};//DifferenceFilter

void mv::Caliper::Run()
{
    SearchCaliperPath();
    DifferenceFilter(filterSize);
}//Run

