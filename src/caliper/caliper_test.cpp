//
// Created by $mango on 4/2/2020.
//

#include "caliper.h"


int main()
{


    cv::Mat img = cv::imread("../../images/blob.jpg", 0);
    cv::Ptr<mv::Caliper> caliper = mv::Caliper::CreateInstance(cv::Point2d(80, 60), 100, 0);
    caliper->Init(img);
    caliper->SetParam();

    int64 s = cv::getTickCount();
    caliper->Run();
    int64 e = cv::getTickCount();
    std::cout<<"Caliper cost time: "<< static_cast<double >(e -  s) /cv::getTickFrequency() * 1000<<"ms" <<std::endl;


    std::cout<<"peak: "<<caliper->result.peak.x<<","<<caliper->result.peak.y<<std::endl;
    std::cout<<"front: "<<caliper->result.front<<std::endl;
    std::cout<<"center: "<<caliper->result.center<<std::endl;
    std::cout<<"back: "<<caliper->result.back<<std::endl;

    cv::Mat imgShow;
    cv::cvtColor(img, imgShow, cv::COLOR_GRAY2BGR);
    // 绘制卡尺结果
    cv::circle(imgShow, caliper->result.front, 1, cv::Scalar(0,0,255), 1);
    cv::circle(imgShow, caliper->result.center, 1, cv::Scalar(0,0,255), 1);
    cv::circle(imgShow, caliper->result.back, 1, cv::Scalar(0,0,255), 1);

    cv::imshow("Caliper Test", imgShow);
    cv::waitKey(0);
    return 0;
}
