/**
 * @file test_mat.cpp
 * @author mango (2321544362@qq.com)
 * @brief 矩阵测试
 * @version 0.1
 * @date 2021-08-23
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"
#include "common/mat.h"


TEST_CASE("test instanctiation type", "[mvk_common mat]")
{
	mvk::MatInt32 int_mat(100, 100);
	int_mat.SetElement(50, 50, 100);
	REQUIRE(int_mat.GetElement(50, 50) == 100);
}



