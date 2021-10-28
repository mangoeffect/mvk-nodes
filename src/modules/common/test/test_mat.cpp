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
#include "common/mat.h"
#include "catch2/catch_test_macros.hpp"
#include "catch2/catch_session.hpp"

TEST_CASE("test instanctiation type", "[mvk_common mat]")
{
	mvk::MatInt32 int_mat(100, 100);
	int_mat.SetElement(50, 50, 100);
	REQUIRE(int_mat.GetElement(50, 50) == 100);
}

int main()
{
	Catch::Session session;
	return session.run();
}


