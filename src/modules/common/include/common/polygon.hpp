/**
 * @file polygon.h
 * @author mango (2321544362@qq.com)
 * @brief 
 * @version 0.1
 * @date 2021-09-08
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef MVK_POLYGON_H_
#define MVK_POLYGON_H_

#include "common/point.hpp"
#include <vector>

namespace mvk
{
    /**
     * @brief 多边形
     * 
     */
    template<typename T>
    struct Polygon
    {
        std::vector<Point<T>> points;
    };
    
} // namespace mvk


#endif //MVK_POLYGON_H_
