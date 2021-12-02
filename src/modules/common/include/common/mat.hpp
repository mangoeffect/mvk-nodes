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

namespace mvk
{    
    enum class MatType
    {
        MVK_8U = 0,
        MVK_8S = 1,
        MVK_16U = 2,
        MVK_16S = 3,
        MVK_32U = 4,
        MVK_32S = 5,
        MVK_32F = 6,
        MVK_64F = 7
    };

    /**
     * @brief 矩形类声明
     * 
     * @tparam T 
     */
    class Matrix
    {
    private:
        unsigned char* data_{nullptr};
        size_t rows_{0};
        size_t cols_{0};
        size_t element_size_{0};     ///< 每个元素内存占用大小，单位字节
        MatType type_;               ///< 矩阵数据类型
        size_t data_size_{0};        ///< 矩阵元素数据内存占用大小， data_size = element_size * rows * cols
    public:
        Matrix();                   

        Matrix(const size_t& rows,
               const size_t& cols,
               const MatType& type);

        Matrix(const size_t& rows,
               const size_t& cols,
               const MatType& type,
               const unsigned char* data);

        Matrix& operator = (const Matrix& other);

        Matrix Clone() const;

        static Matrix Zero(const size_t& rows,
                           const size_t& cols,
                           const MatType& type);

        void Release();

        ~Matrix();

        bool IsEmpty() const;

        const unsigned char* Ptr(const size_t& rows, const size_t& cols);

        template<typename T>
        const T* Ptr(const size_t& rows, const size_t& cols);

        const unsigned char* Ptr(const size_t& rows);

        template<typename T>
        const T* Ptr(const size_t& rows);
    };

} // namespace mvk

#endif //MVK_MAT_H_
