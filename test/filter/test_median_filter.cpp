#define CATCH_CONFIG_MAIN
#include "catch2/catch_test_macros.hpp"
#include "filter/median_filter.hpp"
#include <random>

using namespace mvk;

TEST_CASE("test mvk-filter median-filter", "[mvk-filter]")
{
    std::string rgb_path = std::string(DATA) + "/images/mvk_filter/rgb_nosie_5x5.png";
    Image rgb_img = LoadImage(rgb_path.c_str());
    REQUIRE(!rgb_img.IsEmpty());

    Image rgb_medianfilter_5x5;
    REQUIRE(MedianFilter(rgb_img, rgb_medianfilter_5x5, 5) == 0);
    REQUIRE( WriteImage(rgb_medianfilter_5x5, "rgb_medianfilter_5x5.png") != -1);

    
    std::string mono_path = std::string(DATA) + "/images/mvk_filter/256X256_lena_mono.jpg";
    Image mono = LoadImage(mono_path.c_str()).Convert(CONVERT_TYPE::RGB2GRAY);
    REQUIRE(!mono.IsEmpty());

    //添加噪声
    std::random_device rd;  
    std::mt19937 gen(rd()); 
    std::uniform_int_distribution<> dist(1, 230);
    for(int i = 0; i < 100; i++)
    {
        int x = dist(gen);
        int y = dist(gen);
        mono.At<std::uint8_t>(x, y) = 0;
    }

    Image mono_medianfilter_7x7;
    REQUIRE(MedianFilter(mono, mono_medianfilter_7x7, 7) == 0);
    REQUIRE(WriteImage(mono_medianfilter_7x7, "mono_medianfilter_7x7.png") != -1);

    //测试3x3滤波
    Image mono_medianfilter_fast3x3;
    REQUIRE(MedianFilter3x3(mono, mono_medianfilter_fast3x3) == 0);
    REQUIRE(WriteImage(mono_medianfilter_fast3x3, "mono_medianfilter_fast3x3.png") != -1);


    Image rgb_medianfilter_fast3x3;
    REQUIRE(MedianFilter3x3(rgb_img, rgb_medianfilter_fast3x3) == 0);
    REQUIRE(WriteImage(rgb_medianfilter_fast3x3, "rgb_medianfilter_fast3x3.png") != -1);


    //测试5x5滤波
    Image mono_medianfilter_fast5x5;
    REQUIRE(MedianFilter5x5(mono, mono_medianfilter_fast5x5) == 0);
    REQUIRE(WriteImage(mono_medianfilter_fast5x5, "mono_medianfilter_fast5x5.png") != -1);


    Image rgb_medianfilter_fast5x5;
    REQUIRE(MedianFilter5x5(rgb_img, rgb_medianfilter_fast5x5) == 0);
    REQUIRE(WriteImage(rgb_medianfilter_fast5x5, "rgb_medianfilter_fast5x5.png") != -1);
}