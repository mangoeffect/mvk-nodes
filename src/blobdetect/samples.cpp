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
    cv::Mat img = cv::imread("../../../test/image/blob.jpg");
    if(img.empty())
        return  -1;
    blobdetect->Init(img);
    blobdetect->SetParams();
    int s = cv::getTickCount();
    blobdetect->Run();
    int e = cv::getTickCount();
    std::cout<<"BlobDetect cost time: "<< static_cast<double >(e -  s) /cv::getTickFrequency() * 1000<<"ms" <<std::endl;
    blobdetect->PrintResultInfo();

//    blobdetect->PrintParameter();
//    blobdetect->DrawOutline();
    blobdetect.release();

    Ptr<cv::SimpleBlobDetector> sblobdetect = cv::SimpleBlobDetector::create();
    std::vector<cv::KeyPoint> kps;
    s = cv::getTickCount();
    sblobdetect->detect(img, kps);
    e = cv::getTickCount();
    std::cout<<"SimpleBlobDetector cost time: "<< static_cast<double >(e -  s) /cv::getTickFrequency() * 1000<<"ms" <<std::endl;
    std::cout<<"keypoints size: "<<kps.size()<<std::endl;
    for(int i = 0; i < kps.size(); ++i)
    {
        std::cout<<i+1<<": location:"<<kps[i].pt<<std::endl;
    }
    cv::Mat im_with_keypoints;
    cv::drawKeypoints( img, kps, im_with_keypoints, Scalar(0,0,255), DrawMatchesFlags::DRAW_RICH_KEYPOINTS );
    cv::imshow("keypoints", im_with_keypoints );
    cv::waitKey(0);
    sblobdetect.release();

    return 0;
}
