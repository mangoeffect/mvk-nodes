//
// Created by mango on 2024/2/28.
//

#define CATCH_CONFIG_MAIN
#include "catch2/catch_test_macros.hpp"
#include "filter/blend.hpp"
#include "../test_helper.hpp"

TEST_CASE("test mvk-filter blend, normal-blend", "[mvk-filter]")
{
    std::string rgb_path = std::string(DATA) + "/images/mvk_filter/Doraemon.png";
    Image base = LoadImage(rgb_path.c_str());
    REQUIRE(!base.IsEmpty());
    Image origin = base.Clone();

    Image blend = Image(base.GetSize(), IMAGE_TYPE::IMAGE_8UC4);
    Image base_rgba = base.Convert(CONVERT_TYPE::RGB2RGBA);

    for(int i = 0; i < blend.GetSize().height; i++)
    {
        for (int j = 0; j < blend.GetSize().width; ++j)
        {
            blend.Ptr<std::uint8_t>(j, i)[0] = 10;
            blend.Ptr<std::uint8_t>(j, i)[1] = 100;
            blend.Ptr<std::uint8_t>(j, i)[2] = 200;
            blend.Ptr<std::uint8_t>(j, i)[3] = 255;
        }
    }


    Image normal_blend_alpha100;
    REQUIRE(NormalBlend(base_rgba, blend, normal_blend_alpha100) == 0);
    REQUIRE(!normal_blend_alpha100.IsEmpty());
    REQUIRE(WriteImage(normal_blend_alpha100, "normal_blend_alpha100.png")!= -1);
    REQUIRE(IsFileExists("normal_blend_alpha100.png"));

    //alpha-80
    int alpha = std::round(255 * 0.8);
    for(int i = 0; i < base_rgba.GetSize().height; i++)
    {
        for (int j = 0; j < base_rgba.GetSize().width; ++j)
        {
            base_rgba.Ptr<std::uint8_t>(j, i)[3] = alpha;
        }
    }

    Image normal_blend_alpha80;
    REQUIRE(NormalBlend(base_rgba, blend, normal_blend_alpha80) == 0);
    REQUIRE(!normal_blend_alpha80.IsEmpty());
    REQUIRE(WriteImage(normal_blend_alpha80, "normal_blend_alpha80.png")!= -1);
    REQUIRE(IsFileExists("normal_blend_alpha80.png"));

    //alpha-50
    alpha = std::round(255 * 0.5);
    for(int i = 0; i < base_rgba.GetSize().height; i++)
    {
        for (int j = 0; j < base_rgba.GetSize().width; ++j)
        {
            base_rgba.Ptr<std::uint8_t>(j, i)[3] = alpha;
        }
    }

    Image normal_blend_alpha50;
    REQUIRE(NormalBlend(base_rgba, blend, normal_blend_alpha50) == 0);
    REQUIRE(!normal_blend_alpha50.IsEmpty());
    REQUIRE(WriteImage(normal_blend_alpha50, "normal_blend_alpha50.png")!= -1);
    REQUIRE(IsFileExists("normal_blend_alpha50.png"));


    alpha = std::round(255 * 0.3);
    for(int i = 0; i < base_rgba.GetSize().height; i++)
    {
        for (int j = 0; j < base_rgba.GetSize().width; ++j)
        {
            base_rgba.Ptr<std::uint8_t>(j, i)[3] = alpha;
        }
    }
    Image normal_blend_alpha30;
    REQUIRE(NormalBlend(base_rgba, blend, normal_blend_alpha30) == 0);
    REQUIRE(!normal_blend_alpha30.IsEmpty());
    REQUIRE(WriteImage(normal_blend_alpha30, "normal_blend_alpha30.png")!= -1);
    REQUIRE(IsFileExists("normal_blend_alpha30.png"));
}

TEST_CASE("test mvk-filter blend, addweighted", "[mvk-filter]")
{
    Image img1 = Image(Size(500, 500), IMAGE_TYPE::IMAGE_8UC3);
    Image img2 = Image(Size(500, 500), IMAGE_TYPE::IMAGE_8UC3);

    for(int i = 0; i < img1.GetSize().height; i++)
    {
        for (int j = 0; j < img1.GetSize().width; ++j)
        {
            img1.Ptr<std::uint8_t>(j, i)[3] = 50;
            img2.Ptr<std::uint8_t>(j, i)[3] = 150;
        }
    }

    Image dst;
    REQUIRE(AddWeighted(img1, 0.5, img2, 0.5, dst, 1) == 0);

    auto CheckPixel = [](Image img, std::uint8_t v)
            {
                for(int i = 0; i < img.GetSize().height; i++)
                {
                    for (int j = 0; j < img.GetSize().width; ++j)
                    {
                        for(int k = 0; k < img.Channels(); k++)
                        {
                            if(img.Ptr<std::uint8_t>(j, i)[k] != v)
                            {
                                return false;
                            }
                        }
                    }
                }
                return true;
            };

    REQUIRE(CheckPixel(dst, 101));
}
