#define CATCH_CONFIG_MAIN
#include "catch2/catch_test_macros.hpp"
#include "filter/median_filter.hpp"
#include <random>

using namespace mvk;

TEST_CASE("test mvk-filter median-filter", "[mvk-filter]")
{
    Image rgb_img;
    std::string rgb_path = std::string(DATA) + "/images/mvk_filter/rgb_nosie_5x5.png";
    REQUIRE(rgb_img.Read(rgb_path, IMAGE_FORMAT::RGB_24_BIT) == 0);

    Image rgb_medianfilter_5x5;
    REQUIRE(MedianFilter(rgb_img, rgb_medianfilter_5x5, 5) == 0);
    REQUIRE(rgb_medianfilter_5x5.Save(std::string(DATA) + "/images/mvk_filter/rgb_medianfilter_5x5.png") == 0);
    
    Image mono;
    REQUIRE(mono.Read(std::string(DATA) + "/images/mvk_filter/256X256_lena_mono.jpg", IMAGE_FORMAT::MONO_8_BIT) == 0);

    //添加噪声
    std::random_device rd;  
    std::mt19937 gen(rd()); 
    std::uniform_int_distribution<> dist(1, 230);
    for(int i = 0; i < 100; i++)
    {
        int x = dist(gen);
        int y = dist(gen);
        mono.GetPixel(y, x)[0] = 0;
    }

    Image mono_medianfilter_7x7;
    REQUIRE(MedianFilter(mono, mono_medianfilter_7x7, 7) == 0);
    REQUIRE(mono_medianfilter_7x7.Save(std::string(DATA) + "/images/mvk_filter/mono_medianfilter_7x7.png") == 0);
}