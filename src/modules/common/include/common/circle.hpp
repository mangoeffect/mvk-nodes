/**
 * @file circle.h
 * @author mango (2321544362@qq.com)
 * @brief 
 * @version 0.1
 * @date 2021-08-21
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef MVK_CIRCLE_H_
#define MVK_CIRCLE_H_

#include "common/point.hpp"

namespace mvk
{    
    /**
     * @brief 圆形类
     * 
     */
    struct Circle
    {
        Point2f center;                 ///< 圆心
        float radius;                   ///< 半径
    };
    
} // namespace mvk


#endif //MVK_CIRCLE_H_

