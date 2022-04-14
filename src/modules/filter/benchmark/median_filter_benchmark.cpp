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

using namespace mvk;

int main(int argc, char** argv)
{
    //halcon性能基准 640x480 0.09ms i7-4770 3.40 GHz
    std::vector<std::tuple<size_t, size_t>> img_sizes = {{640, 480}, {1280, 720}, {1280, 960}, {1920, 1080}, {1600, 1200}, {2048, 1536}, {2592, 1944}, {3264, 2448}, {3840, 2160}, {4224, 3168}, {5344, 4106}};

    std::cout << "-------------mvk-nodes filter mono median-filter3x3 benchenmark------------------\n";
    for(auto&& [len, wid]: img_sizes)
    {
        Image src(len, wid, 128);
        Image dst;
        auto t0 = std::chrono::system_clock::now();
        MedianFilter3x3(src, dst);
        auto t1 = std::chrono::system_clock::now();
        std::cout <<std::to_string(len) + "x" + std::to_string(wid) + " cost "<< std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0).count() << " ms." << std::endl;
    }

    std::cout << "-------------mvk-nodes filter rgb median-filter3x3 benchenmark------------------\n";
    for(auto&& [len, wid]: img_sizes)
    {
        Image src(len, wid, {128, 90, 150});
        Image dst;
        auto t0 = std::chrono::system_clock::now();
        MedianFilter3x3(src, dst);
        auto t1 = std::chrono::system_clock::now();
        std::cout <<std::to_string(len) + "x" + std::to_string(wid) + " cost "<< std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0).count() << " ms." << std::endl;
    }

 
    std::cout << "-------------mvk-nodes filter mono median-filter5x5 benchenmark------------------\n";
    for(auto&& [len, wid]: img_sizes)
    {
        Image src(len, wid, 128);
        Image dst;
        auto t0 = std::chrono::system_clock::now();
        MedianFilter5x5(src, dst);
        auto t1 = std::chrono::system_clock::now();
        std::cout <<std::to_string(len) + "x" + std::to_string(wid) + " cost "<< std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0).count() << " ms." << std::endl;
    }

    std::cout << "-------------mvk-nodes filter rgb median-filter5x5 benchenmark------------------\n";
    for(auto&& [len, wid]: img_sizes)
    {
        Image src(len, wid, {128, 90, 150});
        Image dst;
        auto t0 = std::chrono::system_clock::now();
        MedianFilter5x5(src, dst);
        auto t1 = std::chrono::system_clock::now();
        std::cout <<std::to_string(len) + "x" + std::to_string(wid) + " cost "<< std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0).count() << " ms." << std::endl;
    }
    return 0;
}

