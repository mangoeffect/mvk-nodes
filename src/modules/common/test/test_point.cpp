/**
 * @file test_point.cpp
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
#include "common/point.hpp"

using namespace mvk;

TEST_CASE("test mvk_common points", "[mvk_common point]")
{
    //构造函数
    Point<int> pt1(1, 2);
    REQUIRE(pt1.x == 1);
    REQUIRE(pt1.y == 2);

    //点乘测试
    Point v1(0.0f, 1.0f);
    Point v2(1.0f, 0.0f);
    REQUIRE(v1.Dot(v2) == 0.0f);

    //坐标点相加
    Point p1(1, 2);
    Point p2(2, 1);
    REQUIRE((p1 + p2).x == 3);
    REQUIRE((p1 + p2).y == 3);

    //坐标点相减
    REQUIRE((p1 - p2).x == -1);
    REQUIRE((p1 - p2).y == 1);

    //正交判断
    Point a(0, 1);
    Point b(0, 0);
    Point c(1, 0);
    REQUIRE(IsOrthogonal(a, b, c));
}

