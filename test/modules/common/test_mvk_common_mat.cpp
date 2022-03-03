/**
 * @file test_mvk_common_mat.cpp
 * @author mango (2321544362@qq.com)
 * @brief 
 * @version 0.1
 * @date 2022-03-03
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "common/mat.hpp"

#include <iostream>

using namespace mvk;

int main(int argc, char** argv)
{
    auto m =  Matrix<uint8_t, 4, 4>::identity();
    std::cout << m.getval(0, 0) << std::endl;
    return 0;
}

