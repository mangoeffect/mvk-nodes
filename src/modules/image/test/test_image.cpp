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
    //错误路径读取
    Image error_path;
    REQUIRE(error_path.Read("", IMAGE_FORMAT::RGB_24_BIT) != 0);
    REQUIRE(error_path.Read("abc", IMAGE_FORMAT::MONO_8_BIT) != 0);
    
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


    //矩阵构造图像
    Matrix<uint8_t> mat_100x100(100, 100, 128);
    for(size_t i = 40; i < 60; i++)
    {
        for(size_t j = 40; j < 60; j++)
        {
            mat_100x100(i, j) = 0;
        }
    }
    Image mono_mat(mat_100x100, 1);
    REQUIRE(mono_mat.Save(std::string(DATA) + "/images/mvk_image/mat_100x100.png") == 0);

    Matrix<uint8_t> mat_100x300(100, 300, 0);
    for(size_t i = 40; i < 60; i++)
    {
        for(size_t j = 120; j < 180; j+= 3)
        {
            mat_100x300(i, j) = 255; //r
        }
    }
    Image rgb_mat(mat_100x300, 3);
    REQUIRE(rgb_mat.Save(std::string(DATA) + "/images/mvk_image/rgb_mat.png") == 0);


    //拷贝边界测试
    Image img_border(100, 100, 255);

    //上边缘图案
    img_border.GetPixel(0, 50)[0] = 0;
    img_border.GetPixel(1, 49)[0] = 0;
    img_border.GetPixel(1, 50)[0] = 0;
    img_border.GetPixel(1, 51)[0] = 0;
    img_border.GetPixel(2, 49)[0] = 0;
    img_border.GetPixel(2, 51)[0] = 0;
    img_border.GetPixel(5, 50)[0] = 0;

    //下边缘图案
    img_border.GetPixel(99, 50)[0] = 0;
    img_border.GetPixel(98, 49)[0] = 0;
    img_border.GetPixel(98, 50)[0] = 0;
    img_border.GetPixel(98, 51)[0] = 0;
    img_border.GetPixel(97, 49)[0] = 0;
    img_border.GetPixel(97, 51)[0] = 0;
    img_border.GetPixel(95, 51)[0] = 0;

    //左边缘图案
    img_border.GetPixel(48, 0)[0] = 0;
    img_border.GetPixel(49, 0)[0] = 0;
    img_border.GetPixel(50, 0)[0] = 0;
    img_border.GetPixel(51, 0)[0] = 0;    
    img_border.GetPixel(52, 0)[0] = 0;
    img_border.GetPixel(49, 1)[0] = 0;
    img_border.GetPixel(50, 1)[0] = 0;
    img_border.GetPixel(51, 1)[0] = 0;  
    img_border.GetPixel(50, 2)[0] = 0;

    //右边缘图案
    img_border.GetPixel(48, 97)[0] = 0;
    img_border.GetPixel(49, 97)[0] = 0;
    img_border.GetPixel(50, 97)[0] = 0;
    img_border.GetPixel(51, 97)[0] = 0;    
    img_border.GetPixel(52, 97)[0] = 0;
    img_border.GetPixel(49, 98)[0] = 0;
    img_border.GetPixel(50, 98)[0] = 0;
    img_border.GetPixel(51, 98)[0] = 0;  
    img_border.GetPixel(50, 99)[0] = 0;

    //保存原图
    REQUIRE(img_border.Save(std::string(DATA) + "/images/mvk_image/img_border.png") == 0);
    auto img_border_default_3 = img_border.CopyWithBorder(3);
    REQUIRE(img_border_default_3.Save(std::string(DATA) + "/images/mvk_image/img_border_default_3.png") == 0);

    auto img_border_default_5 = img_border.CopyWithBorder(5);
    REQUIRE(img_border_default_5.Save(std::string(DATA) + "/images/mvk_image/img_border_default_5.png") == 0);

    auto img_border_default_7 = img_border.CopyWithBorder(7);
    REQUIRE(img_border_default_7.Save(std::string(DATA) + "/images/mvk_image/img_border_default_7.png") == 0);

    auto img_border_constant_3 = img_border.CopyWithBorder(3, BORDER_TYPE::CONSTANT, {50, 50, 50});
    REQUIRE(img_border_constant_3.Save(std::string(DATA) + "/images/mvk_image/img_border_constant_3.png") == 0);

    auto img_border_constant_5 = img_border.CopyWithBorder(5, BORDER_TYPE::CONSTANT, {100,100, 100});
    REQUIRE(img_border_constant_5.Save(std::string(DATA) + "/images/mvk_image/img_border_constant_5.png") == 0);

    auto img_border_replicate_3 = img_border.CopyWithBorder(3, BORDER_TYPE::REPLICATE);
    REQUIRE(img_border_replicate_3.Save(std::string(DATA) + "/images/mvk_image/img_border_replicate_3.png") == 0);

    auto img_border_replicate_5 = img_border.CopyWithBorder(5, BORDER_TYPE::REPLICATE);
    REQUIRE(img_border_replicate_5.Save(std::string(DATA) + "/images/mvk_image/img_border_replicate_5.png") == 0);

    //彩色边界测试
    Image rgb_border(100, 100, {255,255,255});
    std::vector<std::array<uint8_t, 3>> rgb{
        {255, 0, 0},
        {0, 255, 0},
        {0, 0, 255}
    };
    //上边缘
    for(int i = 0; i < 5;  i ++)
    {
        for(int c = 0; c < 3; c++)
        {
            if(i == 0)
            {
                rgb_border.GetPixel(i, 50)[c] = rgb[0][c];
            }
            else if(i == 1)
            {
                rgb_border.GetPixel(i, 47)[c] = rgb[1][c];
                rgb_border.GetPixel(i, 50)[c] = rgb[1][c];
                rgb_border.GetPixel(i, 53)[c] = rgb[1][c];
            }else if(i == 4)
            {
                rgb_border.GetPixel(i, 50)[c] = rgb[2][c];
            }
        }
    }

    //下边缘
    for(int i = 99; i > 95;  i--)
    {
        for(int c = 0; c < 3; c++)
        {
            if(i == 99)
            {
                rgb_border.GetPixel(i, 50)[c] = rgb[0][c];
                rgb_border.GetPixel(i, 52)[c] = rgb[0][c];
            }
            else if(i == 98)
            {
                rgb_border.GetPixel(i, 47)[c] = rgb[1][c];
                rgb_border.GetPixel(i, 53)[c] = rgb[1][c];
            }else if(i == 96)
            {
                rgb_border.GetPixel(i, 50)[c] = rgb[2][c];
            }
        }
    }

    //左边缘
    for(int i = 0; i < 5;  i ++)
    {
        for(int c = 0; c < 3; c++)
        {
            if(i == 0)
            {
                rgb_border.GetPixel(50, i)[c] = rgb[0][c];
            }
            else if(i == 1)
            {
                rgb_border.GetPixel(47, i)[c] = rgb[1][c];
                rgb_border.GetPixel(50, i)[c] = rgb[1][c];
                rgb_border.GetPixel(53, i)[c] = rgb[1][c];
            }else if(i == 4)
            {
                rgb_border.GetPixel(50, i)[c] = rgb[2][c];
            }
        }
    }

    //右边缘
    for(int i = 96; i < 100;  i ++)
    {
        for(int c = 0; c < 3; c++)
        {
            if(i == 98)
            {
                rgb_border.GetPixel(50, i)[c] = rgb[0][c];
            }
            else if(i == 97)
            {
                rgb_border.GetPixel(47, i)[c] = rgb[1][c];
                rgb_border.GetPixel(50, i)[c] = rgb[1][c];
                rgb_border.GetPixel(53, i)[c] = rgb[1][c];
            }else if(i == 99)
            {
                rgb_border.GetPixel(50, i)[c] = rgb[2][c];
            }
        }
    }
    REQUIRE(rgb_border.Save(std::string(DATA) + "/images/mvk_image/rgb_border.png") == 0);
    auto rgb_border_default_3 = rgb_border.CopyWithBorder(3);
    REQUIRE(rgb_border_default_3.Save(std::string(DATA) + "/images/mvk_image/rgb_border_default_3.png") == 0);

    auto rgb_border_default_5 = rgb_border.CopyWithBorder(5);
    REQUIRE(rgb_border_default_5.Save(std::string(DATA) + "/images/mvk_image/rgb_border_default_5.png") == 0);

    auto rgb_border_default_7 = rgb_border.CopyWithBorder(7);
    REQUIRE(rgb_border_default_7.Save(std::string(DATA) + "/images/mvk_image/rgb_border_default_7.png") == 0);

    auto rgb_border_constant_3 = rgb_border.CopyWithBorder(3, BORDER_TYPE::CONSTANT, {155, 188, 0});
    REQUIRE(rgb_border_constant_3.Save(std::string(DATA) + "/images/mvk_image/rgb_border_constant_3.png") == 0);

    auto rgb_border_constant_5 = rgb_border.CopyWithBorder(5, BORDER_TYPE::CONSTANT, {255, 0, 0});
    REQUIRE(rgb_border_constant_5.Save(std::string(DATA) + "/images/mvk_image/rgb_border_constant_5.png") == 0);

    auto rgb_border_replicate_3 = rgb_border.CopyWithBorder(3, BORDER_TYPE::REPLICATE);
    REQUIRE(rgb_border_replicate_3.Save(std::string(DATA) + "/images/mvk_image/rgb_border_replicate_3.png") == 0);

    auto rgb_border_replicate_5 = rgb_border.CopyWithBorder(5, BORDER_TYPE::REPLICATE);
    REQUIRE(rgb_border_replicate_5.Save(std::string(DATA) + "/images/mvk_image/rgb_border_replicate_5.png") == 0);
}

