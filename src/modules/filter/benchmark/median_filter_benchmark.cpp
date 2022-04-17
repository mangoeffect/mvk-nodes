/**
 * @file median_filter_benchmark.cpp
 * @author mango (2321544362@qq.com)
 * @brief 
 * @version 0.1
 * @date 2022-04-12
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "filter/median_filter.hpp"
#include <chrono>
#include <iostream>
#include <vector>
#include <tuple>
#include <fstream>

using namespace mvk;

int main(int argc, char** argv)
{
    std::vector<std::tuple<size_t, size_t>> img_sizes = {{640, 480}, {1280, 720}, {1280, 960}, {1920, 1080}, {1600, 1200}, {2048, 1536}, {2592, 1944}, {3264, 2448}, {3840, 2160}, {4224, 3168}, {5344, 4106}};

    std::cout << "-------------mvk-nodes filter mono median-filter3x3 benchenmark------------------\n";
    std::vector<double> mono3x3, rgb3x3, mono5x5, rgb5x5;

    for(auto&& [len, wid]: img_sizes)
    {
        Image src(len, wid, 128);
        Image dst;
        auto t0 = std::chrono::system_clock::now();
        for(int i = 0; i < 10; i++)
        MedianFilter3x3(src, dst);
        auto t1 = std::chrono::system_clock::now();
        auto t = std::chrono::duration_cast<std::chrono::microseconds>(t1 - t0).count() / 10000.0 ;
        mono3x3.push_back(t);
        std::cout <<std::to_string(len) + "x" + std::to_string(wid) + " cost "<< t << " ms." << std::endl;
    }

    std::cout << "-------------mvk-nodes filter rgb median-filter3x3 benchenmark------------------\n";
    for(auto&& [len, wid]: img_sizes)
    {
        Image src(len, wid, {128, 90, 150});
        Image dst;
        auto t0 = std::chrono::system_clock::now();
        for(int i = 0; i < 10; i++)
        MedianFilter3x3(src, dst);
        auto t1 = std::chrono::system_clock::now();
        auto t = std::chrono::duration_cast<std::chrono::microseconds>(t1 - t0).count() / 10000.0 ;
        rgb3x3.push_back(t);
        std::cout <<std::to_string(len) + "x" + std::to_string(wid) + " cost "<< t << " ms." << std::endl;
    }

 
    std::cout << "-------------mvk-nodes filter mono median-filter5x5 benchenmark------------------\n";
    for(auto&& [len, wid]: img_sizes)
    {
        Image src(len, wid, 128);
        Image dst;
        auto t0 = std::chrono::system_clock::now();
        for(int i = 0; i < 10; i++)
        MedianFilter5x5(src, dst);
        auto t1 = std::chrono::system_clock::now();
        auto t = std::chrono::duration_cast<std::chrono::microseconds>(t1 - t0).count() / 10000.0 ;
        mono5x5.push_back(t);
        std::cout <<std::to_string(len) + "x" + std::to_string(wid) + " cost "<< t << " ms." << std::endl;
    }

    std::cout << "-------------mvk-nodes filter rgb median-filter5x5 benchenmark------------------\n";
    for(auto&& [len, wid]: img_sizes)
    {
        Image src(len, wid, {128, 90, 150});
        Image dst;
        auto t0 = std::chrono::system_clock::now();
        for(int i = 0; i < 10; i++)
        MedianFilter5x5(src, dst);
        auto t1 = std::chrono::system_clock::now();
        auto t = std::chrono::duration_cast<std::chrono::microseconds>(t1 - t0).count() / 10000.0 ;
        rgb5x5.push_back(t);
        std::cout <<std::to_string(len) + "x" + std::to_string(wid) + " cost "<< t << " ms." << std::endl;
    }

    std::ofstream out_csv;
    out_csv.open("mvk-median-benchmark.csv", std::ios::out); 
    int data_size = mono3x3.size();
    for(int i = 0; i < data_size; i++)
    {
        auto len = std::get<0>(img_sizes[i]);
        auto wid = std::get<1>(img_sizes[i]);
        out_csv <<std::to_string(len) + "x" + std::to_string(wid) + ","<< mono3x3[i] << "," << rgb3x3[i] << "," << mono5x5[i] << "," << rgb5x5[i] << std::endl;
    }
    out_csv.close();

    return 0;
}

