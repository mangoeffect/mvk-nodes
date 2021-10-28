/**
* @file caliper.cpp
* @brief 卡尺工具源代码文件
* @details 根据《机器视觉算法与应用》一维边缘点检测原理实现
* @author 芒果
* @date 2020-4-2
* @version 1.0.0
*/
#include "caliper.h"

#include <cmath>
#include <algorithm>
#include <cassert>

namespace mvp
{
    namespace caliper
    {
        Caliper::Caliper(const cv::Point2d _center, const size_t _len, const double _k)
        : center(_center) , len(_len), k(_k)
        {

        }//Caliper

        void Caliper::Init(cv::Mat input_image)
        {
            SetParam();
            if(input_image.channels() > 1)
                cv::cvtColor(input_image, input_image_, cv::COLOR_BGR2GRAY);
            else
				input_image_ = input_image;
        }//Init

        cv::Ptr<Caliper> Caliper::CreateInstance(const cv::Point2d center, const size_t len, const double k)
        {
            return  cv::makePtr<Caliper>(center, len, k);
        }//CreateInstance

        void Caliper::SearchCaliperPath()
        {
            assert(!input_image_.empty() && input_image_.channels() == 1);
            //1. 初始化卡尺路径直线方程
            angle = std::atan(k);
            // b = y - kx
            b = center.y - k * center.x;
            //2. 求取搜索起始点
            min_x = center.x - len * std::cos(angle) * 0.5;
            if (min_x < 0) return;
            max_x = center.x + len * std::cos(angle) * 0.5;

            //3. 从起始点搜索，保存卡尺路径点集
            path.clear();
            pathPixelValue.clear();
            // y = kx + b;
            double y = 0;
            for (int i = static_cast<int>(min_x); i < static_cast<int>(max_x); ++i)
            {
                y = i * k + b;
                path.push_back(cv::Point2d(i, y));
                pathPixelValue.push_back(input_image_.at<uchar>(static_cast<int>(y), i));
            }
        }//SearchCaliperPath


        //差分滤波
        void Caliper::DifferenceFilter(const size_t &_filterSize)
        {
            //1. 构造滤波核: [-1,-1...0...1,1]
            std::vector<int> filter(2 * _filterSize + 1, 1);
            for (size_t i = 0; i < _filterSize; ++i)
            {
                filter[i] = -1;
            }
            filter[_filterSize] = 0;

            //2. 滤波核滑动滤波，逐一相乘求和（省去反转的一维卷积）
            pathPixelValueAfterFilter.clear();
            pathPixelValueAfterFilter.assign(pathPixelValue.begin(), pathPixelValue.end());
            for (size_t j = _filterSize; j < pathPixelValue.size() - _filterSize; ++j)
            {
                double sum = 0.0;
                for (size_t i = 0; i < filter.size(); ++i)
                {
                    sum += pathPixelValue.at(j - _filterSize + i) * filter.at(i);
                }
                pathPixelValueAfterFilter.at(j) = static_cast<int>(sum);
            }
        };//DifferenceFilter

        void Caliper::Run()
        {
            //1. 搜索
            SearchCaliperPath();           //搜索卡尺路径，保存路径点集以供分析
            //2. 滤波
            DifferenceFilter(filterSize);  //一维差分滤波处理卡尺路径像素值
            //3. 查找边缘点
            FindExtremePoint();            //查找极值点
            //4. 筛选边缘点
            ExtremePointRating();          //极值点评分
        }//Run

        void Caliper::SetParam()
        {
            // 默认值
            filterSize = 2;
            contrastThreshold = 5;
            polarity = 0; // 黑到白
        }//SetParam

        void Caliper::SetParam(const std::string &name, const int &value)
        {
            if(name.empty())
                return;
            if("filterSize" == name)
            {
                filterSize = value;
            }else if("contrastThreshold" == name)
            {
                contrastThreshold = value;
            } else if("polarity" == name)
            {
                polarity = value;
            } else
            {
                std::string s = "Not found parameter '" + name + "' in Caliper.";
                throw s;
            }
        }

        // 求取极值点
        void Caliper::FindExtremePoint()
        {
            // 1. 检查搜索路径像素数据是否为空
            if(pathPixelValueAfterFilter.empty())
                return;
            // 2. 遍历滤波后的数据，查找极值点
            extremePoints.clear();
            switch (polarity)
            {
                // 不考虑极性
                case 0 :
                    for(size_t i = 1; i < pathPixelValueAfterFilter.size() - 1; ++i)
                    {
                        // 两边异号为极值点
                        if (size_t(std::abs(pathPixelValueAfterFilter.at(i))) >= contrastThreshold
                            && (0 > (pathPixelValueAfterFilter.at(i) - pathPixelValueAfterFilter.at(i - 1)) *
                                (pathPixelValueAfterFilter.at(i + 1) - pathPixelValueAfterFilter.at(i)))
                        )
                        {
                            extremePoints.push_back(ExtremPointInfo(path.at(i), static_cast<int>(i), static_cast<int>(pathPixelValueAfterFilter.at(i))));
                        }
                    }
                    break;
                // 黑到白
                case 1 :
                    for(size_t i = 1; i < pathPixelValueAfterFilter.size() - 1; ++i)
                    {
                        // 两边异号为极值点
                        if (pathPixelValueAfterFilter.at(i) > 0
                            && size_t(std::abs(pathPixelValueAfterFilter.at(i))) >= contrastThreshold
                            && (0 > (pathPixelValueAfterFilter.at(i) - pathPixelValueAfterFilter.at(i - 1)) *
                                (pathPixelValueAfterFilter.at(i + 1) - pathPixelValueAfterFilter.at(i)))
                        )
                        {
                            extremePoints.push_back(ExtremPointInfo(path.at(i), static_cast<int>(i), static_cast<int>(pathPixelValueAfterFilter.at(i))));
                        }
                    }
                    break;
                // 白到黑
                case -1:
                    for(size_t i = 1; i < pathPixelValueAfterFilter.size() - 1; ++i)
                    {
                        // 两边异号为极值点
                        if (pathPixelValueAfterFilter.at(i) < 0
                            && size_t(std::abs(pathPixelValueAfterFilter.at(i))) >= contrastThreshold
                            && (0 > (pathPixelValueAfterFilter.at(i) - pathPixelValueAfterFilter.at(i - 1)) *
                                (pathPixelValueAfterFilter.at(i + 1) - pathPixelValueAfterFilter.at(i)))
                        )
                        {
                            extremePoints.push_back(ExtremPointInfo(path.at(i), static_cast<int>(i), static_cast<int>(pathPixelValueAfterFilter.at(i))));
                        }
                    }
                    break;
                default:
                    assert(false);
                    break;
            }

        }//FindExtremePoint

        // 极值点评分
        void Caliper::ExtremePointRating()
        {
            if(extremePoints.empty())
                return;

            // 评分： value * (1 - |i - 0.5 * le| / 0.5 * len)
            int halfLen = static_cast<int>(path.size() / 2);
            for(auto& e: extremePoints)
            {
                e.score = e.value * (1 - static_cast<double>(std::abs(e.ps - halfLen)) / halfLen);
            }

            //按评分排序：降序
            sort(extremePoints.begin(), extremePoints.end(), CompareExtremPointInfoBysocre);

            result.peak = extremePoints.at(0).pt;

            if(extremePoints.size() == 1)
            {
                result.center = result.front = result.back = extremePoints.at(0).pt;
                return;
            }

            if(extremePoints.size() == 2)
            {
                int a =  std::abs(extremePoints.at(0).ps - halfLen);
                int b =  std::abs(extremePoints.at(1).ps - halfLen);
                if(a > b)
                {
                    result.front = result.back = extremePoints.at(0).pt;
                    result.center = extremePoints.at(1).pt;
                }else
                {

                }
            }else
            {
                std::vector<ExtremPointInfo> epf(extremePoints.begin(), extremePoints.begin() + 3);

                sort(epf.begin(), epf.end(), CompareExtremPointInfoByPs);//降序
                result.back = epf.at(0).pt;
                result.center = epf.at(1).pt;
                result.front = epf.at(2).pt;
            }

        }//ExtremePointRating

    }//namespace caliper
}//namespace mvp

