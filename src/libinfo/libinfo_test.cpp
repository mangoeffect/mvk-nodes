//
// Created by mango on 3/20/2020.
//

#include "opencvinfo.h"


int main()
{
    mv::OpenCVInfo op;
    op.Print();

	cv::Mat img = cv::Mat(100, 100, CV_8UC1);

    return 0;
}
