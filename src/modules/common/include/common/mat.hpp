/**
 * @file mat.h
 * @author mango (2321544362@qq.com)
 * @brief 矩阵类声明
 * @version 0.1
 * @date 2021-08-23
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef MVK_MAT_H_
#define MVK_MAT_H_

#include <memory>
#include <tuple>
#include <vector>
#include <initializer_list>


namespace mvk
{    
    /**
     * @brief 矩阵类
     * 
     * @tparam T 
     */
    template<typename T>
    class Matrix
    {
    private:
        std::vector<std::vector<T>> value_;               ///< 矩阵元素值
        size_t rows_;
        size_t cols_;
    public:
        /**
         * @brief 虚析构函数
         * 
         */
        virtual ~Matrix();

        /**
         * @brief 构造函数
         * 
         * @param rows(in) 矩阵行数
         * @param cols(in) 矩阵列数
         */
        Matrix(const size_t rows, const size_t cols);

        /**
         * @brief 初始化列表构造函数
         * 
         */
        Matrix(std::initializer_list<std::initializer_list<T>> data_list);

        /**
         * @brief 拷贝构造函数
         * 
         * @param matrix(in) 另一个矩阵对象 
         */
        Matrix(const Matrix<T>& matrix);

        /**
         * @brief 赋值构造
         * 
         * @param matrix(in) 另一个矩阵对象 
         * @return Matrix& 
         */
        Matrix& operator = (const Matrix<T>& matrix);

        /**
         * @brief 移动语义构造
         * 
         * @param matrix 
         */
        Matrix(const Matrix<T>&& matrix);

        /**
         * @brief 移动语义赋值构造
         * 
         * @param matrix(in) 另一个矩阵对象 
         * @return Matrix& 
         */
        Matrix& operator = (const Matrix<T>&& matrix);

        
        /**
         * @brief 获取矩阵元素
         * 
         * @param rows(in) 元素位置行标 
         * @param cols(in) 元素位置列标
         * @return T 
         */
        inline T& At(const size_t rows, const size_t cols);

        /**
         * @brief 单位矩阵
         * 
         * @param size(in) 矩阵尺寸 
         * @return Matrix 
         */
        static Matrix Identity(const size_t size);

        /**
         * @brief 矩阵行数
         * 
         * @return size_t 
         */
        size_t Rows() const;

        /**
         * @brief 矩阵列数
         * 
         * @return size_t 
         */
        size_t Cols() const;

        /**
         * @brief 矩阵相加
         * 
         * @param matrix 
         * @return Matrix<T> 
         */
        Matrix<T> operator + (const Matrix<T>& matrix);

        /**
         * @brief 矩阵相减
         * 
         * @param matrix 
         * @return Matrix<T> 
         */
        Matrix<T> operator - (const Matrix<T>& matrix);

         /**
         * @brief 矩阵相乘
         * 
         * @param matrix 
         * @return Matrix<T> 
         */
        Matrix<T> operator * (const Matrix<T>& matrix);

        /**
         * @brief 矩阵转置
         * 
         * @return Matrix<T> 
         */
        Matrix<T> Transpose();

        /**
         * @brief 矩阵求逆
         * 
         * @return Matrix<T> 
         */
        Matrix<T> Inverse();
    };
} // namespace mvk

#endif //MVK_MAT_H_
