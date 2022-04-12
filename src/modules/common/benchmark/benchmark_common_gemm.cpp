/**
 * @file benchmark_common_gemm.cpp
 * @author mango (2321544362@qq.com)
 * @brief gemm性能测试
 * @version 0.1
 * @date 2022-04-02
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <iostream>
#include <chrono>
#include "algorithms/gemm/gemm_1.hpp"
#include "algorithms/gemm/gemm_2.hpp"
#include "algorithms/gemm/gemm_3.hpp"

using namespace mvk;

int main(int argc, char** argv)
{
    //朴素算法测试
    std::cout << "------------origin-gemm----------------"<< std::endl;
    for(int i = 10; i < 10000; i *= 10)
    {
        std::vector<std::vector<float>> A(i, std::vector<float>(i, 1.0f));
        std::vector<std::vector<float>> B(i, std::vector<float>(i, 0.0f));
        std::vector<std::vector<float>> C(i, std::vector<float>(i, 1.0f));
        auto t0 = std::chrono::system_clock::now();
        MatrixMulti1<float>(A, B, C);
        auto t1 = std::chrono::system_clock::now();

        std::cout << std::to_string(i) + "x" + std::to_string(i) + " cost "<< std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0).count() << " ms." <<std::endl;
    }

    //优化1：循环展开测试
    std::cout << "------------unrolling 4-gemm----------------"<< std::endl;
    for(int i = 10; i < 10000; i *= 10)
    {
        std::vector<std::vector<float>> A(i, std::vector<float>(i, 1.0f));
        std::vector<std::vector<float>> B(i, std::vector<float>(i, 0.0f));
        std::vector<std::vector<float>> C(i, std::vector<float>(i, 1.0f));
        auto t0 = std::chrono::system_clock::now();
        MatrixMulti2<float>(A, B, C);
        auto t1 = std::chrono::system_clock::now();

        std::cout << std::to_string(i) + "x" + std::to_string(i) + " cost "<< std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0).count() << " ms." <<std::endl;
    }

     //优化1：循环展开测试2
    std::cout << "------------unrolling 4-gemm 2----------------"<< std::endl;
    for(int i = 10; i < 10000; i *= 10)
    {
        std::vector<std::vector<float>> A(i, std::vector<float>(i, 1.0f));
        std::vector<std::vector<float>> B(i, std::vector<float>(i, 0.0f));
        std::vector<std::vector<float>> C(i, std::vector<float>(i, 1.0f));
        auto t0 = std::chrono::system_clock::now();
        MatrixMulti3<float>(A, B, C);
        auto t1 = std::chrono::system_clock::now();

        std::cout << std::to_string(i) + "x" + std::to_string(i) + " cost "<< std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0).count() << " ms." <<std::endl;
    }
    return 0;
}

