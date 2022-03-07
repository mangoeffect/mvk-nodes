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
#include "catch2/catch_test_macros.hpp"
#include "image/image.hpp"
#include <iostream>

using namespace mvk;

TEST_CASE("test mvk-imgae", "[mvk_image]")
{
    //彩色图片读取
    Image rgb_image;
    REQUIRE(rgb_image.GetData() == nullptr);
    std::string rgb_path = std::string(DATA) + "/images/mvk_image/512X512_lena_rgb.png";
    REQUIRE(rgb_image.Read(rgb_path, IMAGE_FORMAT::RGB_24_BIT) == 0);
    REQUIRE(rgb_image.GetData() != nullptr);
    REQUIRE(rgb_image.GetChannel() == 3);
    REQUIRE(rgb_image.GetHeight() == 512);
    REQUIRE(rgb_image.GetWidth() == 512);

    //单通道灰色图片读取
    Image mono_image;
    REQUIRE(mono_image.GetData() == nullptr);
    std::string mono_path = std::string(DATA) + "/images/mvk_image/256X256_lena_mono.jpg";
    REQUIRE(mono_image.Read(mono_path, IMAGE_FORMAT::MONO_8_BIT) == 0);
    REQUIRE(mono_image.GetData() != nullptr);
    REQUIRE(mono_image.GetChannel() == 1);
    REQUIRE(mono_image.GetHeight() == 256);
    REQUIRE(mono_image.GetWidth() == 256);

    //访问修改像素
    for(size_t i = 100; i < 200; i++) // row
    {
        for(size_t j = 150; j < 180; j++) //col
        {
            *mono_image.GetPixel(i, j) = 0;
        }
    }

    //保存文件
    mono_image.Save(std::string(DATA) + "/images/mvk_image/256X256_lena_mono_save.png");

    //再次检查
    Image mono_image_modify;
    REQUIRE(mono_image_modify.Read(std::string(DATA) + "/images/mvk_image/256X256_lena_mono_save.png", mvk::IMAGE_FORMAT::MONO_8_BIT) == 0);
    for(size_t i = 100; i < 200; i++) // row
    {
        for(size_t j = 150; j < 180; j++) //col
        {
            REQUIRE(uint8_t(*mono_image_modify.GetPixel(i, j)) == 0);
        }
    }

    //赋值值构造函数
    Image img1(10, 10, 1);
    auto img2 = img1;
    *img1.GetPixel(5, 5) = 2;
    //浅拷贝测试
    REQUIRE(2 == *img2.GetPixel(5,5));
    
    //深拷贝测试
    auto img3 = img1.Copy();
    *img1.GetPixel(5, 5) = 3;
    REQUIRE(3 != *img3.GetPixel(5, 5));
    REQUIRE(2 == *img3.GetPixel(5, 5));

    //坐标点访问像素
    *img3.GetPixel(3 ,2) = 5;
    REQUIRE(5 == *img3.GetPixel(Point2i(2 , 3)));

    //rgb像素点测试
    Image rgb1(10, 10, {1,2,3});
    REQUIRE(1 == rgb1.GetPixel(5,5)[0]);
    REQUIRE(2 == rgb1.GetPixel(5,5)[1]);
    REQUIRE(3 == rgb1.GetPixel(5,5)[2]);

    //rgb拷贝测试
    auto rgb1_copy = rgb1.Copy();
    rgb1.GetPixel(5,5)[0] = 0;
    auto rgb2 = rgb1;
    REQUIRE(1 == rgb1_copy.GetPixel(5, 5)[0]);
    REQUIRE(0 == rgb2.GetPixel(5, 5)[0]);
}

