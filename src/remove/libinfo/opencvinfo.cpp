
/**
* @file opencvinfo.cpp
* @brief OpenCV信息相关
* @details -
* @author 芒果
* @date 2020-3-20
* @version 1.0.0
*/

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
