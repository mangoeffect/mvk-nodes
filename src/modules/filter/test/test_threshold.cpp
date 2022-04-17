/**
 * @file test_threshold.cpp
 * @author mango (2321544362@qq.com)
 * @brief 
 * @version 0.1
 * @date 2022-04-15
 * 
 * @copyright Copyright (c) 2022
 * 
 */

 #define CATCH_CONFIG_MAIN
#include "catch2/catch_test_macros.hpp"
#include "filter/threshold.hpp"

using namespace mvk;

TEST_CASE("test mvk-filter threshold", "[mvk-filter]")
{
    Image mono;
    REQUIRE(mono.Read(std::string(DATA) + "/images/mvk_filter/256X256_lena_mono.jpg", IMAGE_FORMAT::MONO_8_BIT) == 0);

    //二值化
    Image binary;
    REQUIRE(Threshold(mono, binary, 128, THRESHOLD_TYPE::THRESH_BINARY) == 0);
    REQUIRE(binary.Save("binary.png") == 0);

}