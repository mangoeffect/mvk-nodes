/**
 * @file test_algorithms_gemm1.cpp
 * @author mango (2321544362@qq.com)
 * @brief gemm1算法朴素测试
 * @version 0.1
 * @date 2022-04-02
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#define CATCH_CONFIG_MAIN
#include "catch2/catch_test_macros.hpp"
#include "algorithms/gemm/gemm_1.hpp"
#include <random>

using namespace mvk;

TEST_CASE("test mvk-common-algorithms-gemm1 ", "[mvk_common algorithms]")
{
    std::vector<std::vector<int>> A{{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    std::vector<std::vector<int>> B{{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};
    std::vector<std::vector<int>> C(3, std::vector<int>(3, 0));

    MatrixMulti1<int>(A, B, C);

    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            REQUIRE(A[i][j] == C[i][j]);
        }
    }

    //2x3 * 3x2 = 2x2
    A = {{1, 1, 1}, {2, 2, 2}};
    B = {{1, 0}, {0, 0}, {0, 0}};
    std::vector<std::vector<int>> CC(2, std::vector<int>(2, 0));

    MatrixMulti1<int>(A, B, CC);
    REQUIRE(CC[0][0] == 1);
    REQUIRE(CC[0][1] == 0);
    REQUIRE(CC[1][1] == 0);
    REQUIRE(CC[1][0] == 2);
}

