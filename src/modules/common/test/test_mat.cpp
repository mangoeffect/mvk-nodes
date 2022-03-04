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
#include "catch2/catch_test_macros.hpp"
#include "common/mat.hpp"
#include <random>

using namespace mvk;

TEST_CASE("test mvk-common-mat ", "[mvk_common mat]")
{
	//行列数测试
	Matrix<int> mat10x10(10, 10);
	REQUIRE(mat10x10.Rows() == 10);
	REQUIRE(mat10x10.Cols() == 10);

	//单位矩阵测试
	auto identity = Matrix<int>::Identity(4);
	for(size_t i = 0; i < 4; i++)
	{
		for(size_t j = 0; j < 4; j++)
		{
			if(i == j)
			{
				REQUIRE(1 == identity(i, j));
			}else
			{
				REQUIRE(0 == identity(i, j));
			}
		}
	}

	//赋值测试
	Matrix<int> mat100x100(100, 100);
	mat100x100(50, 50) = 50;
	REQUIRE(mat100x100(50, 50) == 50);

	//转置矩阵测试
	Matrix<int> mat2x3(2, 3);
	mat2x3(0, 0) = 1;
	mat2x3(0, 1) = 2;
	mat2x3(0, 2) = 3;
	auto mat3x2 = mat2x3.Transpose();
	REQUIRE(mat3x2(0, 0) == 1);
	REQUIRE(mat3x2(1, 0) == 2);
	REQUIRE(mat3x2(2, 0) == 3);

	//矩阵相乘测试
	identity(0, 3) = 10;
	identity(1, 3) = 20;
	identity(2, 3) = -30;
	
	Matrix<int> vec4(4,1);
	vec4(0, 0) = 1; //x
	vec4(1, 0) = 2; //y
	vec4(2, 0) = 3; //z
	vec4(3, 0) = 1;
	auto result = identity * vec4;
	REQUIRE(result.Rows() == 4);
	REQUIRE(result.Cols() == 1);
	REQUIRE(result(0, 0) == 11); //x 1 + 10
	REQUIRE(result(1, 0) == 22); //y 2 + 20
	REQUIRE(result(2, 0) == -27); //z 3 -30;
	

	//矩阵相加测试
	Matrix<int> mat_a(3, 3, 1);
	Matrix<int> mat_b(3, 3, 1);
	auto mat_c = mat_a + mat_b;
	for(size_t i = 0; i < 3; i++)
	{
		for(size_t j = 0; j < 3; j++)
		{
			REQUIRE(mat_c(i, j) == 2);
		}
	}
	//矩阵相减测试
	auto mat_d = mat_a - mat_b;
	for(size_t i = 0; i < 3; i++)
	{
		for(size_t j = 0; j < 3; j++)
		{
			REQUIRE(mat_d(i, j) == 0);
		}
	}

	//构造函数测试
	Matrix<int> origin(2, 2, 1);
	//赋值构造
	Matrix<int> assigned = origin;
	REQUIRE(assigned.Rows() == 2);
	REQUIRE(assigned.Cols() == 2);
	REQUIRE(assigned(0, 0) == 1);
	
	//移动语义赋值构造
	Matrix<int> move_assigned = std::move(origin);
	REQUIRE(move_assigned.Rows() == 2);
	REQUIRE(move_assigned.Cols() == 2);
	REQUIRE(move_assigned(0, 0) == 1);

	//拷贝构造
	Matrix<int> copy_construct(origin);
	REQUIRE(copy_construct.Rows() == 2);
	REQUIRE(copy_construct.Cols() == 2);
	REQUIRE(copy_construct(0, 0) == 1);

	//移动语义拷贝构造
	Matrix<int> move_copy(std::move(origin));
	REQUIRE(move_copy.Rows() == 2);
	REQUIRE(move_copy.Cols() == 2);
	REQUIRE(move_copy(0, 0) == 1);

	//初始化列表构造
	Matrix<int> init_list({{1, 2, 3}, {1, 2, 3}});
	REQUIRE(init_list.Rows() == 2);
	REQUIRE(init_list.Cols() == 3);
	REQUIRE(init_list(0, 0) == 1);
	REQUIRE(init_list(1, 2) == 3);
}



