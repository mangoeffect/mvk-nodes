/**
 * @file gemm_1.hpp
 * @author mango (2321544362@qq.com)
 * @brief gemm通用矩阵乘法的朴素实现
 * @version 0.1
 * @date 2022-04-02
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef MVK_COMMON_ALGORITHMS_GEMM_1_HPP_
#define MVK_COMMON_ALGORITHMS_GEMM_1_HPP_

#include <cassert>
#include <vector>

namespace mvk
{

    /**
     * @brief C = A * B + C 的朴素算法实现
     * 
     *        A 大小为 m * k
     *        B 大小为 k * n
     * @tparam T 
     * @param A 
     * @param B 
     * @param C 
     */
    template<typename T>
    void MatrixMulti1(const std::vector<std::vector<T>>& A, const std::vector<std::vector<T>>& B, std::vector<std::vector<T>>& C)
    {
        assert(!A.empty() && !B.empty() && !C.empty());
        assert(A.size() == C.size() && A[0].size() == B.size() && B[0].size() == C[0].size());
        int m = A.size();
        int k = A[0].size();
        int n = B.size();

        for(int j = 0; j < n; j++)
        {
            for(int i = 0; i < m; i++)
            {
                for(int t = 0; t < k; t++)
                {
                    C[i][j] += A[i][t] * B[t][j];
                }
            }
        }
    }
}//namespace mvk

#endif //MVK_COMMON_ALGORITHMS_GEMM_1_HPP_
