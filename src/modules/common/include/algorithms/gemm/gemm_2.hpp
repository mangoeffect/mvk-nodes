/**
 * @file gemm_2.hpp
 * @author mango (2321544362@qq.com)
 * @brief gemm通用矩阵乘法优化-外层循环展开
 * @version 0.1
 * @date 2022-04-02
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef MVK_COMMON_ALGORITHMS_GEMM_2_HPP_
#define MVK_COMMON_ALGORITHMS_GEMM_2_HPP_

#include <cassert>
#include <vector>

namespace mvk
{

    template<typename T>
    void AddDot(const std::vector<std::vector<T>>& A,
                const std::vector<std::vector<T>>& B, 
                std::vector<std::vector<T>>& C,
                const int i,
                const int j,
                const int k)
    {
        for(int t = 0; t < k; t++)
        {
            C[i][j] += A[i][t] * B[t][j];
        }
    }

    /**
     * @brief C = A * B + C 
     * 
     *        A 大小为 m * k
     *        B 大小为 k * n
     * @tparam T 
     * @param A 
     * @param B 
     * @param C 
     */
    template<typename T>
    void MatrixMulti2(const std::vector<std::vector<T>>& A, const std::vector<std::vector<T>>& B, std::vector<std::vector<T>>& C)
    {
        assert(!A.empty() && !B.empty() && !C.empty());
        assert(A.size() == C.size() && A[0].size() == B.size() && B[0].size() == C[0].size());
        int m = A.size();
        int k = A[0].size();
        int n = B.size();

        //外层循环展开4
        int j = 0;
        for(; j < n - 4; j += 4)
        {
            for(int i = 0; i < m; i++)
            {
                AddDot(A, B, C, i, j, k);
                AddDot(A, B, C, i, j + 1, k);
                AddDot(A, B, C, i, j + 2, k);
                AddDot(A, B, C, i, j + 3, k);
            }
        }
        for(; j < n; j++)
        {
            for(int i = 0; i < m; i++)
            {
                AddDot(A, B, C, i, j, k);
            }
        }
    }
}//namespace mvk


#endif //MVK_COMMON_ALGORITHMS_GEMM_2_HPP_
