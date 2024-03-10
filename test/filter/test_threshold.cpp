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
#include "../test_helper.hpp"

using namespace mvk;

TEST_CASE("test mvk-filter threshold", "[mvk-filter]")
{
    std::string path = std::string(DATA) + "/images/mvk_filter/256X256_lena_mono.jpg";
    Image mono = LoadImage(path.c_str());
    REQUIRE(!mono.IsEmpty());

    Image binary;
    if(mono.Channels() >1)
    {
        REQUIRE(Threshold(mono.Convert(CONVERT_TYPE::RGB2GRAY), binary, 128 ) == 0);
    }

    std::string binary_png = "binary.png";
    REQUIRE(WriteImage(binary,binary_png.c_str() ) != -1);
    REQUIRE(IsFileExists(binary_png));
}