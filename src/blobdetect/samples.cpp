//
// Created by mango on 3/20/2020.
//

#include "blobdetect.h"
#include "opencv2/opencv.hpp"

#include <iostream>

int main()
{
    std::cout<<"blob detection"<<std::endl;
    Ptr<mv::BlobDetect> blobdetect = mv::BlobDetect::CreateInstance();
    cv::Mat img = cv::imread("F:\\Code\\machine-vision-algorithms-library\\test\\image\\blob.jpg", 0);
    if(img.empty())
        return  -1;
    blobdetect->Init(img);
    blobdetect->SetParams();
    blobdetect->Run();
    blobdetect->PrintResultInfo();
    blobdetect->PrintParameter();

    blobdetect.release();
    return 0;
}