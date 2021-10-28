/**
 * @file mat_impl.cpp
 * @author mango (2321544362@qq.com)
 * @brief 
 * @version 0.1
 * @date 2021-08-23
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "common/mat_impl.h"
#include <cassert>

namespace mvk
{    
    template<typename T>
    MatImpl<T>::~MatImpl()
    {
        delete[] data_;
        data_ = nullptr;
    }

    template<typename T>
    MatImpl<T>::MatImpl(const size_t& rows, const size_t& cols)
    : rows_(rows), cols_(cols), data_(new T[rows * cols]())
    {

    }

    template<typename T>
    MatImpl<T>::MatImpl(const size_t& rows, const size_t& cols, const T* data)
    : rows_(rows), cols_(cols), data_(new T[rows * cols])
    {
        memcpy(data_, data, sizeof(T) * rows_ * cols_);
    }

    template<typename T>
    MatImpl<T> MatImpl<T>::GetClone()
    {
        T* new_data = new T[rows_ * cols_];
        memcpy(new_data, data_, sizeof(T) * rows_ * cols_);
        return MatImpl<T>(rows_, cols_, new_data);
    }

    template<typename T>
    void MatImpl<T>::operator= (const MatImpl<T>& other)
    {
        rows_ = other.GetRows();
        cols_ = other.GetCols();
        data_ = other.GetData();
    }

    template<typename T>
    T* MatImpl<T>::GetData() const
    {
        return data_;
    }

    template<typename T>
    size_t MatImpl<T>::GetRows() const
    {
        return rows_;
    }

    template<typename T>
    size_t MatImpl<T>::GetCols() const
    {
        return cols_;
    }

    template<typename T>
    T MatImpl<T>::GetElement(const size_t& row_index, const size_t& col_index) const
    {
        assert(row_index < rows_ && col_index < cols_);
        return data_[row_index * cols_ + cols_];
    }

    template<typename T>
    void MatImpl<T>::SetElement(const size_t& row_index, const size_t& col_index, const T& value)
    {
        assert(row_index < rows_ && col_index < cols_);
        data_[row_index * cols_ + cols_] = value;
    }

    template<typename T>
    MatImpl<T> MatImpl<T>::GetSubmat(const size_t& top_left_row_index, const size_t& top_left_col_index, const size_t& rows, const size_t& cols)
    {
        assert(top_left_row_index < rows_ && top_left_col_index < cols_);
        T* sub_data = new T[rows * cols];
        for(auto r = 0; r < rows; ++r)
        {
            for(auto c = 0; r < cols; ++c)
            {
                sub_data[r * cols + c] = data_[(top_left_row_index + r) * cols_ + (top_left_col_index + c)];
            }
        }
        return MatImpl<T>(rows, cols, sub_data);
    }

    template<typename T>
    void MatImpl<T>::SetSubMat(const size_t& top_left_row_index, const size_t& top_left_col_index, const MatImpl<T>& submat_data)
    {
        assert(top_left_row_index < rows_ && top_left_col_index < cols_);
        auto rows = submat_data.GetRows();
        auto cols = submat_data.GetCols();
        for(auto r = 0; r < rows; ++r)
        {
            for(auto c = 0; r < cols; ++c)
            {
                data_[(top_left_row_index + r) * cols_ + (top_left_col_index + c)] = submat_data.GetData()[r * cols + c];
            }
        }
    }

    template<typename T>
    MatImpl<T>  MatImpl<T>::operator + (const MatImpl<T>& other)
    {
        MatImpl<T> result(0,0);
        return result;
    }

    template<typename T>
    MatImpl<T> MatImpl<T>::operator - (const MatImpl<T>& other)
    {
        MatImpl<T> result(0,0);
        return result;
    }

    template<typename T>
    MatImpl<T> MatImpl<T>::operator * (const MatImpl<T>& other)
    {
        MatImpl<T> result(0,0);
        return result;
    }

    template<typename T>
    MatImpl<T> MatImpl<T>::GetInversion() const
    {
        MatImpl<T> result(0,0);
        return result;
    }

    template<typename T>
    MatImpl<T> MatImpl<T>::ScalarMulti(const T& scalar)
    {
        MatImpl<T> result(0,0);
        return result;
    }

    template<typename T>
    MatImpl<T> MatImpl<T>::GetEigenVector() const
    {
        MatImpl<T> result(0,0);
        return result;
    }

    template<typename T>
    MatImpl<T> MatImpl<T>::GetEigenValue() const
    {
        MatImpl<T> result(0,0);
        return result;
    }

    template<typename T>
    std::tuple<size_t, size_t> MatImpl<T>::GetMaxElement() const
    {
        std::tuple<size_t, size_t> result;
        return result;
    }

    template<typename T>
    std::tuple<size_t, size_t> MatImpl<T>::GetMinElement() const
    {
        std::tuple<size_t, size_t> result;
        return result;
    }

    template<typename T>
    T MatImpl<T>::GetSum() const
    {
        T result = 0;
        return result;
    }

    template<typename T>
    T MatImpl<T>::GetMean() const
    {
        T result = 0;
        return result;
    }

    template<typename T>
    MatImpl<T> MatImpl<T>::Transpose() const
    {
        MatImpl<T> result(0,0);
        return result;
    }

    //模板特例化
    template class MatImpl<char>;
    template class MatImpl<unsigned char>;
    template class MatImpl<int16_t>;
    template class MatImpl<int32_t>;
    template class MatImpl<float>;
    template class MatImpl<double>;
} // namespace mvk


