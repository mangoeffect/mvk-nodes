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

#include "common/mat.h"
#include "common/mat_impl.h"

namespace mvk
{
    template<typename T>
    Mat<T>::Mat(const MatImpl<T>& mat_impl)
    {
        *mat_impl_ = mat_impl;
    }

    
    template<typename T>
    Mat<T>::~Mat()
    {
        mat_impl_->~MatImpl();
    }   

    template<typename T>
    Mat<T>::Mat(const size_t& rows, const size_t& cols)
    : mat_impl_(new MatImpl<T>(rows, cols))
    {

    }

    template<typename T>
    Mat<T>::Mat(const size_t& rows, const size_t& cols, const T* data)
    : mat_impl_(new MatImpl<T>(rows, cols, data))
    {

    }

    template<typename T>
    Mat<T> Mat<T>::GetClone()
    {
        return Mat<T>(mat_impl_->GetClone());
    }

    template<typename T>
    void Mat<T>::operator = (const Mat<T>& other)
    {
        mat_impl_ = other.mat_impl_;
    }

    template<typename T>
    T* Mat<T>::GetData() const
    {
        return mat_impl_->GetData();
    }

    template<typename T>
    size_t Mat<T>::GetRows() const
    {
        return mat_impl_->GetRows();
    }

    template<typename T>
    size_t Mat<T>::GetCols() const
    {
        return mat_impl_->GetCols();
    }

    template<typename T>
    T Mat<T>::GetElement(const size_t& row_index, const size_t& col_index) const
    {
        return mat_impl_->GetElement(row_index, col_index);
    }

    template<typename T>
    void Mat<T>::SetElement(const size_t& row_index, const size_t& col_index, const T& value)
    {
        mat_impl_->SetElement(row_index, col_index, value);
    }

    template<typename T>
    Mat<T> Mat<T>::GetSubmat(const size_t& top_left_row_index, const size_t& top_left_col_index, const size_t& rows, const size_t& cols)
    {
        return Mat<T>(mat_impl_->GetSubmat(top_left_row_index, top_left_col_index, rows, cols));
    }

    template<typename T>
    void Mat<T>::SetSubMat(const size_t& top_left_row_index, const size_t& top_left_col_index, const Mat<T>& submat)
    {
        mat_impl_->SetSubMat(top_left_row_index, top_left_col_index, *submat.mat_impl_);
    }

    template<typename T>
    Mat<T> Mat<T>::operator + (const Mat<T>& other)
    {
        return Mat<T>(mat_impl_->operator+(*other.mat_impl_));
    }   

    template<typename T>
    Mat<T> Mat<T>::operator - (const Mat<T>& other)
    {
        return Mat<T>(mat_impl_->operator-(*other.mat_impl_));
    }

    template<typename T>
    Mat<T> Mat<T>::operator * (const Mat<T>& other)
    {
        return Mat<T>(mat_impl_->operator*(*other.mat_impl_));
    }

    template<typename T>
    Mat<T> Mat<T>::GetInversion() const
    {
        return Mat<T>(mat_impl_->GetInversion());
    }

    template<typename T>
    Mat<T> Mat<T>::ScalarMulti(const T& scalar)
    {
        return Mat<T>(mat_impl_->ScalarMulti(scalar));
    }

    template<typename T>
    Mat<T> Mat<T>::GetEigenVector() const
    {
        return Mat<T>(mat_impl_->GetEigenVector());
    }

    template<typename T>
    Mat<T> Mat<T>::GetEigenValue() const
    {
        return Mat<T>(mat_impl_->GetEigenValue());
    }

    template<typename T>
    std::tuple<size_t, size_t> Mat<T>::GetMaxElement() const
    {
        return mat_impl_->GetMaxElement();
    }

    template<typename T>
    std::tuple<size_t, size_t> Mat<T>::GetMinElement() const
    {
        return mat_impl_->GetMinElement();   
    }

    template<typename T>
    T Mat<T>::GetSum() const
    {
        return mat_impl_->GetSum();
    }

    template<typename T>
    T Mat<T>::GetMean() const
    {
        return mat_impl_->GetMean();
    }

    template<typename T>
    Mat<T> Mat<T>::Transpose() const
    {
        return Mat<T>(mat_impl_->Transpose());
    }

    // 模板特例化
    template class Mat<char>;
    template class Mat<unsigned char>;
    template class Mat<int16_t>;
    template class Mat<int32_t>;
    template class Mat<float>;
    template class Mat<double>;

} // namespace mvk


