/**
 * @file test_xsimd.cpp
 * @author mango (2321544362@qq.com)
 * @brief 测试xsimd库
 * @version 0.1
 * @date 2022-04-11
 * 
 * @copyright Copyright (c) 2022
 * 
 */


#include <iostream>
#include "xsimd/xsimd.hpp"

namespace xs = xsimd;

int main(int argc, char* argv[])
{
    xs::batch<double, xs::avx> a = {1.5, 2.5, 3.5, 4.5};
    xs::batch<double, xs::avx> b = {2.5, 3.5, 4.5, 5.5};
    auto mean = (a + b) / 2;
    std::cout << mean << std::endl;
    return 0;
}