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
#include "../test_helper.hpp"

#include <random>

using namespace mvk;

TEST_CASE("test mvk-filter gaussian-filter","mvk-filter")
{
    Image mono_200x200(Size(200, 200), IMAGE_TYPE::IMAGE_8UC1);
    for(int i = 0; i < 200; i++)
    {
        for(int j = 0; j < 200; j++)
        {
            mono_200x200.At<std::uint8_t>(j, i) = 128;
        }
    }

    //添加噪声
    std::random_device rd;  
    std::mt19937 gen(rd()); 
    std::uniform_int_distribution<> uniform_dist(1, 190);
    std::normal_distribution<> normal_dist{128,50};
    for(int i = 0; i < 100; i++)
    {
        int x = uniform_dist(gen);
        int y = uniform_dist(gen);
        mono_200x200.At<Vec3b>(x, y)[0] = static_cast<uint8_t>(normal_dist(gen));
    }

    std::string mono_200x200_png = "mono_200x200.png";
    REQUIRE(WriteImage(mono_200x200, mono_200x200_png.c_str()) != -1);
    REQUIRE(IsFileExists(mono_200x200_png));

    Image mono_gaussian_1x1, mono_gaussian_3x3, mono_gaussian_5x5;
    REQUIRE(GaussianFilter(mono_200x200, mono_gaussian_1x1, 1) == 0);
    REQUIRE(GaussianFilter(mono_200x200, mono_gaussian_3x3, 3) == 0);
    REQUIRE(GaussianFilter(mono_200x200, mono_gaussian_5x5, 5) == 0);


    REQUIRE(WriteImage(mono_gaussian_1x1, "mono_gaussian_1x1.png") != -1);
    REQUIRE(WriteImage(mono_gaussian_3x3, "mono_gaussian_3x3.png") != -1);
    REQUIRE(WriteImage(mono_gaussian_5x5, "mono_gaussian_5x5.png") != -1);
    REQUIRE(IsFileExists("mono_gaussian_1x1.png"));
    REQUIRE(IsFileExists("mono_gaussian_3x3.png"));
    REQUIRE(IsFileExists("mono_gaussian_5x5.png"));


    Image rgb_200x200(Size(200, 200), IMAGE_TYPE::IMAGE_8UC3);
    for(int i = 0; i < 200; i++)
    {
        for(int j = 0; j < 200; j++)
        {
            mono_200x200.At<Vec3b>(j, i)[0] = 128;
            mono_200x200.At<Vec3b>(j, i)[1] = 128;
            mono_200x200.At<Vec3b>(j, i)[2] = 128;
        }
    }
    for(int i = 0; i < 100; i++)
    {
        int x = uniform_dist(gen);
        int y = uniform_dist(gen);
        rgb_200x200.At<Vec3b>(x, y)[0] = static_cast<uint8_t>(normal_dist(gen));
        rgb_200x200.At<Vec3b>(x, y)[1] = static_cast<uint8_t>(normal_dist(gen));
        rgb_200x200.At<Vec3b>(x, y)[2] = static_cast<uint8_t>(normal_dist(gen));
    }

    Image rgb_gaussian_1x1, rgb_gaussian_3x3, rgb_gaussian_5x5;
    REQUIRE(GaussianFilter(rgb_200x200, rgb_gaussian_1x1, 1) == 0);
    REQUIRE(GaussianFilter(rgb_200x200, rgb_gaussian_3x3, 3) == 0);
    REQUIRE(GaussianFilter(rgb_200x200, rgb_gaussian_5x5, 5) == 0);


    REQUIRE(WriteImage(rgb_gaussian_1x1, "rgb_gaussian_1x1.png") != -1);
    REQUIRE(WriteImage(rgb_gaussian_3x3, "rgb_gaussian_3x3.png") != -1);
    REQUIRE(WriteImage(rgb_gaussian_5x5, "rgb_gaussian_5x5.png") != -1);

    REQUIRE(IsFileExists("rgb_gaussian_1x1.png"));
    REQUIRE(IsFileExists("rgb_gaussian_3x3.png"));
    REQUIRE(IsFileExists("rgb_gaussian_5x5.png"));

    Image rgb_img_gaussian_9x9;
    std::string rgb_path = std::string(DATA) + "/images/mvk_filter/512X512_lena_rgb.png";
    Image rgb_img = LoadImage(rgb_path.c_str());
    REQUIRE(!rgb_img.IsEmpty());
    REQUIRE(GaussianFilter(rgb_img, rgb_img_gaussian_9x9, 9) == 0);
    REQUIRE(WriteImage(rgb_img_gaussian_9x9, "rgb_img_gaussian_9x9.png") != -1);
    REQUIRE(IsFileExists("rgb_img_gaussian_9x9.png"));
}
