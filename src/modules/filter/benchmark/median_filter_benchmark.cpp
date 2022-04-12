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

using namespace mvk;

int main(int argc, char** argv)
{
    //halcon性能基准 640x480 0.09ms i7-4770 3.40 GHz
    Image img640x480(640, 480, 128);
    Image img1, img2;
    auto t0 = std::chrono::system_clock::now();
    MedianFilter3x3(img640x480, img1);
    auto t1 = std::chrono::system_clock::now();
    //MedianFilter(img640x480, img2, 3);
    auto t2 = std::chrono::system_clock::now();

    std::cout << "MedianFilter3x3 cost "<< std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0).count() << " ms." << std::endl;
    std::cout << "MedianFilter cost "<< std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count() << " ms." << std::endl;

    Image img1000x1000(1000, 1000, 128);
    Image img3, img4;
    auto t3 = std::chrono::system_clock::now();
    MedianFilter3x3(img1000x1000, img3);
    auto t4 = std::chrono::system_clock::now();
    MedianFilter(img1000x1000, img4, 3);
    auto t5 = std::chrono::system_clock::now();

    std::cout << "MedianFilter3x3 cost "<< std::chrono::duration_cast<std::chrono::milliseconds>(t4 - t3).count() << " ms." << std::endl;
    std::cout << "MedianFilter cost "<< std::chrono::duration_cast<std::chrono::milliseconds>(t5 - t4).count() << " ms." << std::endl;

    return 0;
}

