/**
 * @file sobel_benchmark.cpp
 * @author mango (2321544362@qq.com)
 * @brief 
 * @version 0.1
 * @date 2022-04-16
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "filter/sobel.hpp"
#include <chrono>
#include <iostream>
#include <vector>
#include <tuple>
#include <fstream>

using namespace mvk;

int main(int argc, char** argv)
{
    std::vector<std::tuple<size_t, size_t>> img_sizes = {{640, 480}, {1280, 720}, {1280, 960}, {1920, 1080}, {1600, 1200}, {2048, 1536}, {2592, 1944}, {3264, 2448}, {3840, 2160}, {4224, 3168}, {5344, 4106}};
    std::ofstream out_csv;
    out_csv.open("mvk-sobel-benchmark.csv", std::ios::out); 

    std::cout << "-------------mvk-nodes filter sobel benchenmark------------------\n";
    for(auto&& [len, wid]: img_sizes)
    {
        Image src(len, wid, 100);
        Image dst;
        int rows = src.GetHeight();
        int cols = src.GetWidth();
        Matrix<float> gx(rows, cols);
        Matrix<float> gy(rows, cols);
        auto t0 = std::chrono::system_clock::now();
        for(int i = 0; i < 10; i++)
        {
            Sobel(src, dst, gx, gy);
        }
        auto t1 = std::chrono::system_clock::now();
        std::cout <<std::to_string(len) + "x" + std::to_string(wid) + " cost "<< std::chrono::duration_cast<std::chrono::microseconds>(t1 - t0).count()  / 10000.0 << " ms." << std::endl;
        out_csv <<std::to_string(len) + "x" + std::to_string(wid) + ","<< std::chrono::duration_cast<std::chrono::microseconds>(t1 - t0).count()  / 10000.0 << std::endl;
    }

    return 0;
}