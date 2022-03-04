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
#include <cassert>


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
         * @brief 构造函数
         * 
         * @param rows(in) 矩阵行数
         * @param cols(in) 矩阵列数
         * @param init_value(in) 使用该值初始化所有矩阵元素
         */
        Matrix(const size_t rows, const size_t cols, const T init_value);

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
        const T& operator ()(const size_t rows, const size_t cols) const;

        /**
         * @brief 获取矩阵元素
         * 
         * @param rows(in) 元素位置行标 
         * @param cols(in) 元素位置列标
         * @return T 
         */
        T& operator ()(const size_t rows, const size_t cols);



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

   template<typename T>
   Matrix<T>::~Matrix()
   {

   }

   template<typename T>
   Matrix<T>::Matrix(const size_t rows, const size_t cols)
   : rows_(rows), cols_(cols), value_(rows, std::vector<T>(cols, 0))
   {
       assert(rows > 0 &&  cols > 0 && "Invalied parameter rows or cols");
   }

   template<typename T>
   Matrix<T>::Matrix(const size_t rows, const size_t cols, const T init_value)
   : rows_(rows), cols_(cols), value_(rows, std::vector<T>(cols, init_value))
   {
       assert(rows > 0 &&  cols > 0 && "Invalied parameter rows or cols");
   }


   template<typename T>
   Matrix<T>::Matrix(std::initializer_list<std::initializer_list<T>> data_list)
   {
       rows_ = 0;
       cols_ = 0;
       for(auto row = data_list.begin(); row != data_list.end(); row++)
       {
           value_.push_back(std::vector<T>());
           for(auto col = row->begin(); col != row->end(); col++)
           {
               value_[rows_].push_back(*col);
           }
           rows_++;
       }
       cols_ = value_[0].size();
       for(auto& r: value_)
       {
           assert(cols_ == r.size());
       }
   }

   template<typename T>
   Matrix<T>::Matrix(const Matrix<T>& matrix)
   {
       rows_ = matrix.Rows();
       cols_ = matrix.Cols();
       value_ = std::vector<std::vector<T>>(rows_,  std::vector<T>(cols_, 0));
       for(size_t i = 0; i < rows_; i++)
       {
           for(size_t j = 0; j < cols_; j++)
           {
               value_[i][j] = matrix(i, j);
           }
       }
   }

   template<typename T>
   Matrix<T>& Matrix<T>::operator = (const Matrix<T>& matrix)
   {
       if(this == &matrix)
       {
           return *this;
       }
       rows_ = matrix.Rows();
       cols_ = matrix.Cols();
       value_ = std::vector<std::vector<T>>(rows_,  std::vector<T>(cols_, 0));
       for(size_t i = 0; i < rows_; i++)
       {
           for(size_t j = 0; j < cols_; j++)
           {
               value_[i][j] = matrix(i, j);
           }
       }
       return *this;
   }

   template<typename T>
   Matrix<T>::Matrix(const Matrix<T>&& matrix)
   {
       rows_ = matrix.Rows();
       cols_ = matrix.Cols();
       value_ = std::vector<std::vector<T>>(rows_,  std::vector<T>(cols_, 0));
       for(size_t i = 0; i < rows_; i++)
       {
           for(size_t j = 0; j < cols_; j++)
           {
               value_[i][j] = matrix(i, j);
           }
       }
   }

   template<typename T>
   Matrix<T>& Matrix<T>::operator = (const Matrix<T>&& matrix)
   {
       if(this == &matrix)
       {
           return *this;
       }
       rows_ = matrix.Rows();
       cols_ = matrix.Cols();
       value_ = std::vector<std::vector<T>>(rows_,  std::vector<T>(cols_, 0));
       for(size_t i = 0; i < rows_; i++)
       {
           for(size_t j = 0; j < cols_; j++)
           {
               value_[i][j] = matrix(i, j);
           }
       }
       return *this;
   }

        
   template<typename T>
   T& Matrix<T>::operator() (const size_t rows, const size_t cols)
   {
       assert(rows < rows_ && cols < cols_ &&  "Invalied parameter rows or cols");
       return value_[rows][cols];
   }

   template<typename T>
   const T& Matrix<T>::operator() (const size_t rows, const size_t cols) const
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
               mat(i,j) = (i == j ? 1 : 0);
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
               result(i, j) = value_[i][j] + matrix(i, j);
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
               result(i, j) = value_[i][j] - matrix(i, j);
           }
       }
       return result;
   }

   template<typename T>
   Matrix<T> Matrix<T>::operator * (const Matrix<T>& matrix)
   {
       assert(cols_ == matrix.Rows() &&  "Matrix A's cols != matrix B' rows.");
       //mxp * pxn ---> mxn
       Matrix<T> result(rows_, matrix.Cols());
       
       for(size_t i = 0; i < result.Rows(); i++)
       {
           for(size_t j = 0; j < result.Cols(); j++)
           {
                T temp = 0;
                for(size_t k = 0; k <  cols_; k++)
                {
                    temp += value_[i][k] * matrix(k, j);
                }
                result(i, j) = temp;
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
               result(j, i) = value_[i][j];
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

#endif //MVK_MAT_H_
