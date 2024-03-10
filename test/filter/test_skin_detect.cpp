//
// Created by mango on 2024/3/7.
//
#define CATCH_CONFIG_MAIN
#include "catch2/catch_test_macros.hpp"
#include "filter/skin_detect.hpp"
#include "../test_helper.hpp"


TEST_CASE("test mvk-filter skin detect", "[mvk-filter]")
{
    std::string rgb_path = std::string(DATA) + "/images/mvk_filter/pengyuyan.jpeg";
    Image rgb_img = LoadImage(rgb_path.c_str());
    REQUIRE(!rgb_img.IsEmpty());

    Image dst;
    REQUIRE(SkinDetectByColorSpace(rgb_img,dst) == 0);
    REQUIRE(!dst.IsEmpty());
    REQUIRE(WriteImage(dst, "test_filter_skin_detect.png") != -1);
}