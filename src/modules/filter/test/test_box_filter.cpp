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
    Image rgb_img;
    std::string rgb_path = std::string(DATA) + "/images/mvk_filter/512X512_lena_rgb.png";
    REQUIRE(rgb_img.Read(rgb_path, IMAGE_FORMAT::RGB_24_BIT) == 0);
    Image rgb_5x5_filter;
    REQUIRE(BoxFilter(rgb_img, rgb_5x5_filter, 5) == 0);
    REQUIRE(rgb_5x5_filter.Save(std::string(DATA) + "/images/mvk_filter/rgb_5x5_filter.png") == 0);
    
    Image rgb_15x15_filter;
    REQUIRE(BoxFilter(rgb_img, rgb_15x15_filter, 15) == 0);
    REQUIRE(rgb_15x15_filter.Save(std::string(DATA) + "/images/mvk_filter/rgb_15x15_filter.png") == 0);

    Image mono;
    REQUIRE(mono.Read(std::string(DATA) + "/images/mvk_filter/256X256_lena_mono.jpg", IMAGE_FORMAT::MONO_8_BIT) == 0);
    Image mono_7x7_filter;
    REQUIRE(BoxFilter(mono, mono_7x7_filter, 7) == 0);
    REQUIRE(mono_7x7_filter.Save(std::string(DATA) + "/images/mvk_filter/mono_7x7_filter.png") == 0);
}
