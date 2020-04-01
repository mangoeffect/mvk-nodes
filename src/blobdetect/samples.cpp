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
    int s = cv::getTickCount();
    blobdetect->Run();
    int e = cv::getTickCount();
    std::cout<<"BlobDetect cost time: "<< static_cast<double >(e -  s) /cv::getTickFrequency()<<"ms" <<std::endl;
    blobdetect->PrintResultInfo();
//    blobdetect->PrintParameter();
    blobdetect.release();

    Ptr<cv::SimpleBlobDetector> sblobdetect = cv::SimpleBlobDetector::create();
    std::vector<cv::KeyPoint> kps;
    s = cv::getTickCount();
    sblobdetect->detect(img, kps);
    e = cv::getTickCount();
    std::cout<<"SimpleBlobDetector cost time: "<< static_cast<double >(e -  s) /cv::getTickFrequency()<<"ms" <<std::endl;
    std::cout<<"keypoints size: "<<kps.size()<<std::endl;
    sblobdetect.release();

    return 0;
}