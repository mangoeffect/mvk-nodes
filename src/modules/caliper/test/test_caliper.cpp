/**
 * @file test_caliper.cpp
 * @author mango (2321544362@qq.com)
 * @brief 
 * @version 0.1
 * @date 2022-04-25
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "caliper/caliper.hpp"
#include "filter/gaussian_filter.hpp"
#include <iostream>
#include <cmath>
#include "matplotlibcpp.h"
namespace plt = matplotlibcpp;

using namespace mvk;



int main(int argc, char** argv)
{
    Caliper caliper(CALIPER_MODE::SINGLE_EDGE);
    Image img(800, 400, 255);
    Image rgb(800, 400, {255, 255, 255});

    //画横线
    for(int i = 0; i < 400; i++)
    {
        for(int j = 0; j < 800; j++)
        {
            if((j / 100) % 2 == 0)
            {
                img.GetPixel(i, j)[0] = 0;
                rgb.GetPixel(i, j)[0] = 0;
                rgb.GetPixel(i, j)[1] = 0;
                rgb.GetPixel(i, j)[2] = 0;
            }
        }
    }
    //高斯滤波处理
    Image mono;
    GaussianFilter(img, mono, 5);
    //mono.Save("caliper_mono.png");

    caliper.SetInputImage(img);
    RotateRectf roi;
    roi.points[0] = {50.0f, 200.0f};
    roi.points[1] = {750.0f, 200.0f};
    roi.points[2] = {750.0f, 300.0f};
    roi.points[3] = {50.0f, 300.0f};
    caliper.SetROI(roi);
    
    int ret = caliper.Measure();
    std::cout << " ret = "<< ret << std::endl;

    auto result = caliper.GetResult();

    for(auto& p: result.peaks)
    {
        std::cout << p.p.x << "," << p.p.y << std::endl;
        rgb.GetPixel(p.p.y, p.p.x)[0] = 255;
    }

    plt::plot(result.project_curve);
    plt::save("project_curve.png");
    rgb.Save("caliper.png");
    return 0;
}
