/**
 * @file test_sobel.cpp
 * @author mango (2321544362@qq.com)
 * @brief 
 * @version 0.1
 * @date 2022-04-16
 * 
 * @copyright Copyright (c) 2022
 * 
 */

 #define CATCH_CONFIG_MAIN
#include "catch2/catch_test_macros.hpp"
#include "filter/sobel.hpp"

using namespace mvk;

TEST_CASE("test mvk-filter sobel", "[mvk-filter]")
{
    Image mono;
    REQUIRE(mono.Read(std::string(DATA) + "/images/mvk_filter/256X256_lena_mono.jpg", IMAGE_FORMAT::MONO_8_BIT) == 0);

    Image edge;
    int rows = mono.GetHeight();
    int cols = mono.GetWidth();
    Matrix<float> gx(rows, cols);
    Matrix<float> gy(rows, cols);

    REQUIRE(Sobel(mono, edge, gx, gy) == 0);
    REQUIRE(edge.Save("sobel.png") == 0);
}