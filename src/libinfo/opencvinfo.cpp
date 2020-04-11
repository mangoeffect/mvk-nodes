//
// Created by mango on 3/20/2020.
//

#include "opencvinfo.h"


void mv::OpenCVInfo::Print()
{
    std::cout<<"OpenCV Information:"<<std::endl;
    std::cout << cv::getBuildInformation() << std::endl;
}

cv::Ptr<mv::MVLInfo> mv::MVLInfo::CreateInstance()
{
    return cv::makePtr<mv::MVLInfo>();
}

std::string mv::MVLInfo::GetMVLInfo() const
{
    std::string res;

    return res;
}
