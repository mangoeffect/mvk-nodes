/**
 * @file test_box_filter.cpp
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
#include "filter/box_filter.hpp"

using namespace mvk;

TEST_CASE("test mvk-filter box-filter", "[mvk-filter]")
{
    std::string rgb_path = std::string(DATA) + "/images/mvk_filter/512X512_lena_rgb.png";
    Image rgb_img = LoadImage(rgb_path.c_str());
    REQUIRE(!rgb_img.IsEmpty());
    Image rgb_5x5_filter;
    REQUIRE(BoxFilter(rgb_img, rgb_5x5_filter, 5) == 0);
    REQUIRE(WriteImage(rgb_5x5_filter,"rgb_5x5_filter.png") != -1);
    
    Image rgb_15x15_filter;
    REQUIRE(BoxFilter(rgb_img, rgb_15x15_filter, 15) == 0);
    REQUIRE(WriteImage(rgb_5x5_filter,"rgb_15x15_filter.png") != -1);

    std::string mono_path = std::string(DATA) + "/images/mvk_filter/256X256_lena_mono.jpg";
    Image mono = LoadImage(mono_path.c_str());
    REQUIRE(!mono.IsEmpty());
    Image mono_7x7_filter;
    REQUIRE(BoxFilter(mono, mono_7x7_filter, 7) == 0);
    REQUIRE(WriteImage(mono_7x7_filter,"mono_7x7_filter.png") != -1);
}
