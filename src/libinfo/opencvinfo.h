//
// Created by mango on 3/20/2020.
//

#ifndef CMAKE_PROJECT_TEMPLATE_OPENCVINFO_H
#define CMAKE_PROJECT_TEMPLATE_OPENCVINFO_H

#include "opencv2/opencv.hpp"

#include <iostream>
#include <string>

namespace mv
{
    class OpenCVInfo
    {
    public:
        void Print();
    };//

    class MVLInfo
    {
    public:
        explict MVLInfo(): MV_MAJOR_VERSION(0), MV_MINOR_VERSION(1), MV_SUBMINOR_VERSION(1) , MV_VERSION("0.1.1") {}
        static cv::Ptr<MVLInfo> CreateInstance();

        int GetMajorVersion() const { return  MV_MAJOR_VERSION;}
        int GetMinorVersino() const { return  MV_MINOR_VERSION;}
        int GetSubminorVersion() const { return  MV_SUBMINOR_VERSION; }

        int GetOpenCVMajorVersion() const { return  CV_MAJOR_VERSION;}
        int GetOpenCVMinorVersino() const { return  CV_MINOR_VERSION;}
        int GetOpenCVSubminorVersion() const { return  CV_SUBMINOR_VERSION; }

        std::string GetMVLInfo() const;
        std::string GetOpenCVInfo() const;
        void PrintMVLInfo() const;
        void PrintOpenCVBuildInfo() const;

    private:
        const int MV_MAJOR_VERSION;
        const int MV_MINOR_VERSION;
        const int MV_SUBMINOR_VERSION;

        const std::string MV_VERSION;
    };//MVLInfo

}// namespace mv
#endif //CMAKE_PROJECT_TEMPLATE_OPENCVINFO_H
