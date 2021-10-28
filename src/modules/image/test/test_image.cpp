/**
 * @file test_image.cpp
 * @author mango (2321544362@qq.com)
 * @brief 
 * @version 0.1
 * @date 2021-10-28
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"
#include "image/image.h"



TEST_CASE("test imgae read and save method", "[mvk_image]")
{
    mvk::Image rgb_image;
    REQUIRE(rgb_image.GetData() == nullptr);

    std::string rgb_path = std::string(DATA) + "/images/mvk_image/512X512_lena_rgb.png";
    REQUIRE(rgb_image.Read(rgb_path, mvk::IMAGE_FORMAT::RGB_24_BIT) == 0);
    REQUIRE(rgb_image.GetData() != nullptr);
    REQUIRE(rgb_image.GetChannel() == 3);
    REQUIRE(rgb_image.GetHeight() == 512);
    REQUIRE(rgb_image.GetWidth() == 512);

    mvk::Image mono_image;
    REQUIRE(mono_image.GetData() == nullptr);

    std::string mono_path = std::string(DATA) + "/images/mvk_image/256X256_lena_mono.jpg";
    REQUIRE(mono_image.Read(mono_path, mvk::IMAGE_FORMAT::MONO_8_BIT) == 0);
    REQUIRE(mono_image.GetData() != nullptr);
    //REQUIRE(mono_image.GetChannel() == 1);//bug
    REQUIRE(mono_image.GetHeight() == 256);
    REQUIRE(mono_image.GetWidth() == 256);

}

