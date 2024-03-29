//
// Created by $mango on 4/1/2020.
//

#include "plot.h"

// y = f(x), (x,y)

namespace mvp
{
    void Plot(const std::vector<int> &x, const std::vector<int> &y, const std::string& title)
    {
        // 1. input parameters
        CV_Assert(x.size() == y.size() && !x.empty());

        // 2. transfer to mat
        int trow = 0;
        for(const auto& e: y)
        {
            if (trow< e)
                trow = e;
        }
        int col = x.size();
        int row = trow + 50;

        cv::Mat m = cv::Mat(row, col, CV_8UC3, cv::Scalar::all(255));
        // Draw function Line
        for(int i = 0; i < x.size(); ++i) //
        {
            m.at<cv::Vec3b>(row - y[i], x[i])[0] = 255;//blue
            m.at<cv::Vec3b>(row - y[i], x[i])[1] = 0;
            m.at<cv::Vec3b>(row - y[i], x[i])[2] = 0;
        }
    //    std::cout<<"row:"<<row
    //            <<" col:"<<col<<std::endl;
        cv::Mat ms = cv::Mat(row + 30, col + 30, CV_8UC3, cv::Scalar::all(168));

        cv::Mat mask =  cv::Mat(row, col, CV_8UC1);
        cv::cvtColor(m, mask, cv::COLOR_BGR2GRAY);
        cv::Mat msRoi = ms(cv::Rect(30,0, m.cols, m.rows));
        m.copyTo(msRoi, mask);

        // 3. show on screen
        cv::namedWindow(title, cv::WINDOW_NORMAL);
        cv::imshow(title, ms);
        cv::waitKey(0);
    }
}//namespace mvp
