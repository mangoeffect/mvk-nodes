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
    /**
     * @brief 矩形类声明
     * 
     * @tparam T 
     */
    template<typename T = int>
    struct Mat
    {
        T* data{nullptr};
        size_t rows{0};
        size_t cols{0};
        size_t data_size{0};        ///< data_size = sizeof(T) * rows * cols
        ~Mat()
        {
            data_size = rows = cols = 0;
            delete [] data;
            data = nullptr;
        }
    };

} // namespace mvk

#endif //MVK_MAT_H_
