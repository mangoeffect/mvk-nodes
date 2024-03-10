/**
 * @file test_sobel.cpp
 * @author mango (2321544362@qq.com)
 * @brief 
 * @version 0.1
 * @date 2022-04-16
 * 
 * @copyright Copyright (c) 2022
 * 
 */

 #define CATCH_CONFIG_MAIN
#include "catch2/catch_test_macros.hpp"
#include "filter/sobel.hpp"
#include "../test_helper.hpp"

using namespace mvk;

TEST_CASE("test mvk-filter sobel", "[mvk-filter]")
{
    std::string path = std::string(DATA) + "/images/mvk_filter/256X256_lena_mono.jpg";
    Image mono = LoadImage(path.c_str());
    REQUIRE(!mono.IsEmpty());

    Image edge;
    int rows = mono.GetSize().height;
    int cols = mono.GetSize().width;
    Matrix<float> gx(rows, cols);
    Matrix<float> gy(rows, cols);

    if(mono.Channels() >1)
    {
        REQUIRE(Sobel(mono.Convert(CONVERT_TYPE::RGB2GRAY), edge, gx, gy) == 0);
    }

    std::string sobel_png = "sobel.png";
    REQUIRE(WriteImage(edge, sobel_png.c_str()) != -1);
    REQUIRE(IsFileExists(sobel_png));
}