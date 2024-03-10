//
// Created by mango on 2024/2/2.
//

#define CATCH_CONFIG_MAIN
#include "catch2/catch_test_macros.hpp"
#include "core/graph.hpp"
#include "core/image_manager.hpp"
#include "../test_helper.hpp"


TEST_CASE("test mango-core image", "[mango-core]")
{
    Image img = Image(Size(500, 500), IMAGE_TYPE::IMAGE_8UC4);

    REQUIRE(!img.IsEmpty());
    for(int y = 0; y < 500; y++)
    {
        for(int x = 0; x < 500; x++)
        {
            img.Ptr<std::uint8_t>(x, y)[0] = 255;
            img.Ptr<std::uint8_t>(x, y)[1] = 0;
            img.Ptr<std::uint8_t>(x, y)[2] = 0;
            img.Ptr<std::uint8_t>(x, y)[3] = 255;
        }
    }
    REQUIRE(WriteImage(img, "test_core_img.png") != -1);
    REQUIRE(IsFileExists("test_core_img.png"));
    Image load_img = LoadImage("test_core_img.png");
    REQUIRE(!load_img.IsEmpty());
}


