/**
 * @file test_integral_image.cpp
 * @author mango (2321544362@qq.com)
 * @brief 
 * @version 0.1
 * @date 2022-03-09
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#define CATCH_CONFIG_MAIN
#include "catch2/catch_test_macros.hpp"
#include "filter/integral_image.hpp"

using namespace mvk;

TEST_CASE("test mvk-filter integral-image","[mvk-filter]")
{
    //5x5 
    //----------------
    // 1 1 1 1 1
    // 1 1 1 1 1
    // 1 1 1 1 1
    // 1 1 1 1 1
    // 1 1 1 1 1
    Image img(5, 5, 1); 
    Matrix<uint64_t> integral;
    REQUIRE(ComputeIntegral(img, integral) == 0); 
    REQUIRE(integral(0, 0) == 1);
    REQUIRE(integral(0, 4) == 5);
    REQUIRE(integral(4, 0) == 5);
    REQUIRE(integral(2, 2) == 9);
    REQUIRE(integral(4, 4) == 25);

    Image rgb(5, 5, {1, 2, 3});
    Matrix<uint64_t> rgb_integral;
    REQUIRE(ComputeIntegral(rgb, rgb_integral) == 0);
    REQUIRE(rgb_integral(0, 0) == 1);
    REQUIRE(rgb_integral(0, 1) == 2);
    REQUIRE(rgb_integral(0, 2) == 3);
    REQUIRE(rgb_integral(4, 4 * 3) == 25);
    REQUIRE(rgb_integral(4, 4 * 3 + 1) == 50);
    REQUIRE(rgb_integral(4, 4 * 3 + 2) == 75);
}

