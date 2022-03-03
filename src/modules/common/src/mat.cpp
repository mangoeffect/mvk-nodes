
/**
 * @file mat.cpp
 * @author mango (2321544362@qq.com)
 * @brief 
 * @version 0.1
 * @date 2021-09-07
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "common/mat.hpp"
#include <cassert>

namespace mvk
{
   template<typename T>
   Matrix<T>::Matrix(const size_t rows, const size_t cols)
   : rows_(rows), cols_(cols), value_(rows, std::vector<T>(cols, 0))
   {
       assert(rows > 0 &&  cols > 0 && "Invalied parameter rows or cols");
   }

   template<typename T>
   Matrix<T>::Matrix(std::initializer_list<std::initializer_list<T>> data_list)
   {

   }

   template<typename T>
   Matrix<T>::Matrix(const Matrix<T>& matrix)
   {

   }

   template<typename T>
   Matrix<T>& Matrix<T>::operator = (const Matrix<T>& matrix)
   {

   }

   template<typename T>
   Matrix<T>::Matrix(const Matrix<T>&& matrix)
   {

   }

   template<typename T>
   Matrix<T>& Matrix<T>::operator = (const Matrix<T>&& matrix)
   {

   }

        
   template<typename T>
   inline T& Matrix<T>::At(const size_t rows, const size_t cols)
   {
       assert(rows < rows_ && cols < cols_ &&  "Invalied parameter rows or cols");
       return value_[rows][cols];
   }

   template<typename T>
   Matrix<T> Matrix<T>::Identity(const size_t size)
   {
       assert(size > 0 &&  "Invalied parameter size");
       Matrix<T> mat(size, size);
       for(size_t i = 0; i < size; i++)
       {
           for(size_t j = 0; j < size; j++)
           {
               mat.At(i,j) = (i == j ? 1 : 0);
           }
       }
       return mat;
   }

   template<typename T>
   size_t Matrix<T>::Rows() const
   {
       return rows_;
   }

   template<typename T>
   size_t Matrix<T>::Cols() const
   {
       return cols_;
   }

   template<typename T>
   Matrix<T>  Matrix<T>::operator + (const Matrix<T>& matrix)
   {
       assert(rows_ == matrix.Rows() && cols_ == matrix.Cols() && "The tow matrixs must be the same size.");
       Matrix<T> result(rows_, cols_);
       for(size_t i = 0; i < rows_; i++)
       {
           for(size_t j = 0; j < cols_; j++)
           {
               result.At(i, j) = this->At(i, j) + matrix.At(i, j);
           }
       }
       return result;
   }

   template<typename T>
   Matrix<T> Matrix<T>::operator - (const Matrix<T>& matrix)
   {
       assert(rows_ == matrix.Rows() && cols_ == matrix.Cols() &&  "The tow matrixs must be the same size.");
       Matrix<T> result(rows_, cols_);
       for(size_t i = 0; i < rows_; i++)
       {
           for(size_t j = 0; j < cols_; j++)
           {
               result.At(i, j) = this->At(i, j) - matrix.At(i, j);
           }
       }
       return result;
   }

   template<typename T>
   Matrix<T> Matrix<T>::operator * (const Matrix<T>& matrix)
   {
       assert(cols_ == matrix.Rows() &&  "Matrix A's cols != matrix B' rows.");
       Matrix<T> result(rows_, matrix.Cols());
       
       for(size_t i = 0; i < rows_; i++)
       {
           for(size_t j = 0; j < matrix.Rows(); j++)
           {
                T temp = 0.0;
                for(size_t k = 0; k <  cols_; k++)
                {
                    temp += this->At(i, k) * matrix.At(k, j);
                }
                result.At(i, j) = temp;
           }
       }

       return result;
   }

   template<typename T>
   Matrix<T> Matrix<T>::Transpose()
   {
       Matrix<T> result(cols_, rows_);
       for(size_t i = 0;  i < rows_; i++)
       {
           for(size_t j = 0; j < cols_; j++)
           {
               result.At(j, i) = this->At(i, j);
           }
       }
       return result;
   }

   template<typename T>
   Matrix<T> Matrix<T>::Inverse()
   {
       Matrix<T> result(rows_, cols_);

       return result;
   }
} // namespace mvk