/**
 * @file test_gaussian_filter.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-03-12
 * 
 * @copyright Copyright (c) 2022
 * 
 */

 #define CATCH_CONFIG_MAIN
#include "catch2/catch_test_macros.hpp"
#include "filter/gaussian_filter.hpp"

#include <random>

using namespace mvk;

TEST_CASE("test mvk-filter gaussian-filter","mvk-filter")
{
    Image mono_200x200(200, 200, 128);

    //添加噪声
    std::random_device rd;  
    std::mt19937 gen(rd()); 
    std::uniform_int_distribution<> uniform_dist(1, 190);
    std::normal_distribution<> normal_dist{128,50};
    for(int i = 0; i < 100; i++)
    {
        int x = uniform_dist(gen);
        int y = uniform_dist(gen);
        mono_200x200.GetPixel(y, x)[0] = static_cast<uint8_t>(normal_dist(gen));
    }

    REQUIRE(mono_200x200.Save("mono_200x200.png") == 0);

    Image mono_gaussian_1x1, mono_gaussian_3x3, mono_gaussian_5x5;
    REQUIRE(GaussianFilter(mono_200x200, mono_gaussian_1x1, 1) == 0);
    REQUIRE(GaussianFilter(mono_200x200, mono_gaussian_3x3, 3) == 0);
    REQUIRE(GaussianFilter(mono_200x200, mono_gaussian_5x5, 5) == 0);

    REQUIRE(mono_gaussian_1x1.Save("mono_gaussian_1x1.png") == 0);
    REQUIRE(mono_gaussian_3x3.Save("mono_gaussian_3x3.png") == 0);
    REQUIRE(mono_gaussian_5x5.Save("mono_gaussian_5x5.png") == 0);

    Image rgb_200x200(200, 200, {128, 128, 128});
    for(int i = 0; i < 100; i++)
    {
        int x = uniform_dist(gen);
        int y = uniform_dist(gen);
        rgb_200x200.GetPixel(y, x)[0] = static_cast<uint8_t>(normal_dist(gen));
        rgb_200x200.GetPixel(y, x)[1] = static_cast<uint8_t>(normal_dist(gen));
        rgb_200x200.GetPixel(y, x)[2] = static_cast<uint8_t>(normal_dist(gen));
    }

    Image rgb_gaussian_1x1, rgb_gaussian_3x3, rgb_gaussian_5x5;
    REQUIRE(GaussianFilter(rgb_200x200, rgb_gaussian_1x1, 1) == 0);
    REQUIRE(GaussianFilter(rgb_200x200, rgb_gaussian_3x3, 3) == 0);
    REQUIRE(GaussianFilter(rgb_200x200, rgb_gaussian_5x5, 5) == 0);

    REQUIRE(rgb_gaussian_1x1.Save("rgb_gaussian_1x1.png") == 0);
    REQUIRE(rgb_gaussian_3x3.Save("rgb_gaussian_3x3.png") == 0);
    REQUIRE(rgb_gaussian_5x5.Save("rgb_gaussian_5x5.png") == 0);

    Image rgb_img;
    Image rgb_img_gaussian_9x9;
    std::string rgb_path = std::string(DATA) + "/images/mvk_filter/512X512_lena_rgb.png";
    REQUIRE(rgb_img.Read(rgb_path, IMAGE_FORMAT::RGB_24_BIT) == 0);
    REQUIRE(GaussianFilter(rgb_img, rgb_img_gaussian_9x9, 9) == 0);
    REQUIRE(rgb_img_gaussian_9x9.Save("rgb_img_gaussian_9x9.png") == 0);
}
