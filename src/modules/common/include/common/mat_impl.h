/**
 * @file mat_impl.h
 * @author mango (2321544362@qq.com)
 * @brief 矩阵类实现
 * @version 0.1
 * @date 2021-08-23
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef MVK_MAT_IMPL_H_
#define MVK_MAT_IMPL_H_

#include "common/common_defines.h"
#include <memory>
#include <tuple>

namespace mvk
{
    template<typename T>
    class MVK_COMMON_EXPORT MatImpl
    {
    private:
        size_t rows_;                                                       ///< 矩阵行数
        size_t cols_;                                                       ///< 矩阵列数
        T*     data_;                                                       ///< 矩阵数据
    public:
        MatImpl() = delete;
        /**
         * @brief 构造函数,初始化矩阵元素值为0
         * 
         * @param rows(in) 矩阵行数 
         * @param cols(in) 矩阵列数 
         */
        MatImpl(const size_t& rows, const size_t& cols);

        /**
         * @brief 构造函数，初始化矩阵元素为输入数据
         * 
         * @param rows(in) 矩阵行数 
         * @param cols(in) 矩阵列数 
         * @param data(in) 矩阵元素初始化数据 
         */
        MatImpl(const size_t& rows, const size_t& cols, const T* data);


        /**
         * @brief 获取矩阵克隆副本，深拷贝
         * 
         * @return MatImpl 
         */
        MatImpl GetClone();

        /**
         * @brief 获取矩阵副本，浅拷贝，共享内存数据
         * 
         * @param other 
         * @return void 
         */
        void operator = (const MatImpl<T>& other);

        /**
         * @brief 析构函数
         * 
         */
        ~MatImpl();

        /**
         * @brief 返回矩阵数据指针首地址
         * 
         * @return T* 
         */
        T* GetData() const;

        /**
         * @brief 获取矩阵行数
         * 
         * @return size_t 
         */
        size_t GetRows() const;

        /**
         * @brief 获取矩阵列数
         * 
         * @return size_t 
         */
        size_t GetCols() const;

        /**
         * @brief 获取矩阵元素
         * 
         * @param row_index(in) 矩阵元素行索引 
         * @param col_index(in) 矩阵元素列索引 
         * @return T 
         */
        T GetElement(const size_t& row_index, const size_t& col_index) const;

        /**
         * @brief 设置矩阵元素
         * 
         * @param row_index(in) 矩阵元素行索引
         * @param col_index(in) 矩阵元素列索引 
         * @param value(in) 矩阵元素值 
         */
        void SetElement(const size_t& row_index, const size_t& col_index, const T& value);

        /**
         * @brief 获取矩阵子矩阵,返回矩阵区域块
         * 
         * @param top_left_row_index(in) 子矩阵左上角行索引 
         * @param top_left_col_index(in) 子矩阵左上角列索引
         * @param rows(in) 子矩阵行数 
         * @param cols(in) 子矩阵列数 
         * @return MatImpl 
         */
        MatImpl GetSubmat(const size_t& top_left_row_index, const size_t& top_left_col_index, const size_t& rows, const size_t& cols);

        /**
         * @brief 设置子矩阵，设置矩阵区域快值
         * 
         * @param top_left_row_index(in) 子矩阵左上角行索引
         * @param top_left_col_index(in) 子矩阵左上角列索引
         * @param submat_data(in) 子矩阵数据
         * @return void 
         */
        void SetSubMat(const size_t& top_left_row_index, const size_t& top_left_col_index, const MatImpl<T>& submat_data);

        /**
         * @brief 矩阵加法
         * 
         * @param other(in) 另一个矩阵 
         * @return MatImpl 相加之和
         */
        MatImpl operator + (const MatImpl<T>& other);

        /**
         * @brief 矩阵减法
         * 
         * @param other(in) 另一个矩阵 
         * @return MatImpl 相减之差
         */
        MatImpl operator - (const MatImpl<T>& other);

        /**
         * @brief 矩阵乘法
         * 
         * @param other(in) 另一个矩阵
         * @return MatImpl 相乘之积
         */
        MatImpl operator * (const MatImpl<T>& other);

        /**
         * @brief 矩阵求逆
         * 
         * @return MatImpl 
         */
        MatImpl GetInversion() const;

        /**
         * @brief 矩阵数乘，返回
         * 
         * @param scalar 
         * @return MatImpl 
         */
        MatImpl ScalarMulti(const T& scalar); 

        /**
         * @brief 求取矩阵特征向量，返回特征向量矩阵
         * 
         * @return MatImpl 
         */
        MatImpl GetEigenVector() const;

        /**
         * @brief 求取矩阵特征值，返回矩阵特征值矩阵
         * 
         * @return MatImpl 
         */
        MatImpl GetEigenValue() const;

        /**
         * @brief 获取矩阵最大元素值，返回最大元素位置索引
         * 
         * @return std::tuple<size_t, size_t> 行索引，列索引
         */
        std::tuple<size_t, size_t> GetMaxElement() const;

        /**
         * @brief 获取矩阵最小元素值，返回最小元素位置索引
         * 
         * @return std::tuple<size_t, size_t> 行索引，列索引
         */
        std::tuple<size_t, size_t> GetMinElement() const;

        /**
         * @brief 矩阵数值求和
         * 
         * @return T 
         */
        T GetSum() const;

        /**
         * @brief 矩阵数值求取平均值
         * 
         * @return T 
         */
        T GetMean() const;

        /**
         * @brief 矩阵转置
         * 
         * @return MatImpl 
         */
        MatImpl Transpose() const;
    };
} // namespace mvk

#endif //MVK_MAT_IMPL_H_
