/**
 * @file main.cpp
 * @author mango (2321544362@qq.com)
 * @brief 
 * @version 0.1
 * @date 2022-04-16
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "opencv2/opencv.hpp"
#include <chrono>
#include <iostream>
#include <vector>
#include <tuple>
#include <fstream>


int main(int argc, char** argv)
{
    std::vector<std::tuple<size_t, size_t>> img_sizes = {{640, 480}, {1280, 720}, {1280, 960}, {1920, 1080}, {1600, 1200}, {2048, 1536}, {2592, 1944}, {3264, 2448}, {3840, 2160}, {4224, 3168}, {5344, 4106}};

    std::cout << "------------opencv mono median-filter3x3 benchmark-------------\n";

    std::ofstream out_csv;
    out_csv.open("cv-threshold-benchmark.csv", std::ios::out); 
    for(auto&& [len, wid] : img_sizes)
    {
        cv::Mat img = cv::Mat(len, wid, CV_8UC1);
        cv::Mat dst;
        auto t0 = std::chrono::system_clock::now();
        for(int i = 0; i < 10; i++)
        {
            cv::medianBlur(img, dst, 3);
        }
        auto t1 = std::chrono::system_clock::now();
        std::cout << std::to_string(len) + "x" + std::to_string(wid) + " cost " << std::chrono::duration_cast<std::chrono::microseconds>(t1 - t0).count() / 10000.0 << " ms.\n";
        out_csv <<std::to_string(len) + "x" + std::to_string(wid) + ","<< std::chrono::duration_cast<std::chrono::microseconds>(t1 - t0).count()  / 10000.0 << std::endl;
    }

    std::cout << "------------opencv rgb median-filter3x3 benchmark-------------\n";
    for(auto&& [len, wid] : img_sizes)
    {
        cv::Mat img = cv::Mat(len, wid, CV_8UC3);
        cv::Mat dst;
        auto t0 = std::chrono::system_clock::now();
        for(int i = 0; i < 10; i++)
        {
            cv::medianBlur(img, dst, 3);
        }
        auto t1 = std::chrono::system_clock::now();
        std::cout << std::to_string(len) + "x" + std::to_string(wid) + " cost " << std::chrono::duration_cast<std::chrono::microseconds>(t1 - t0).count() / 10000.0 << " ms.\n";
    }
    

    return 0;
}
