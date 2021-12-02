/**
 * @file mat.cpp
 * @author mango (2321544362@qq.com)
 * @brief 
 * @version 0.1
 * @date 2021-08-23
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "common/mat.hpp"
namespace mvk
{
    Matrix::Matrix()
    {

    }                

    Matrix::Matrix(const size_t& rows,
                   const size_t& cols,
                   const MatType& type)
    {

    }

    Matrix::Matrix(const size_t& rows,
            const size_t& cols,
            const MatType& type,
            const unsigned char* data)
    {

    }


    Matrix& Matrix::operator = (const Matrix& other)
    {
        return *this;
    }

    Matrix Matrix::Clone() const
    {
        unsigned char* data = new unsigned char[data_size_];
        std::memcpy(data, data_, data_size_);
        return Matrix(rows_, cols_, type_, data);
    }

    Matrix Matrix::Zero(const size_t& rows,
                       const size_t& cols,
                       const MatType& type)
    {
        Matrix  zero;
        return zero;
    }

    void Matrix::Release()
    {
        data_size_ = rows_ = cols_ = 0;
        delete [] data_;
        data_ = nullptr;
    }

    Matrix::~Matrix()
    {
       Release();
    }

    bool Matrix::IsEmpty() const
    {
        return nullptr == data_;
    }


    const unsigned char* Matrix::Ptr(const size_t& rows, const size_t& cols)
    {
        return data_ + (rows * this->cols_ + cols) * element_size_;
    }

    template<typename T> inline
    const T* Matrix::Ptr(const size_t& rows, const size_t& cols)
    {
        return static_cast<const T*>(data_ + (rows * this->cols_ + cols) * element_size_);
    }

    const unsigned char* Matrix::Ptr(const size_t& rows)
    {
        return data_ + cols_ * rows * element_size_;
    }

    template<typename T> inline
    const T* Matrix::Ptr(const size_t& rows)
    {
        return static_cast<const T*>(data_ + cols_ * rows * element_size_);
    }
} // namespace mvk


