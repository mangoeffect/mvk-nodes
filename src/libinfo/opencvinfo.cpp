//
// Created by mango on 3/20/2020.
//

#include "opencvinfo.h"
#include <opencv2/opencv.hpp>
#include <iostream>

void mv::OpenCVInfo::Print()
{
    std::cout<<"OpenCV Information:"<<std::endl;
    std::cout << cv::getBuildInformation() << std::endl;
}
