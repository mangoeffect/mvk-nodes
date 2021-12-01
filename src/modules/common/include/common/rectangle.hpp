/**
 * @file rectangle.h
 * @author mango (2321544362@qq.com)
 * @brief 矩形相关定义
 * @version 0.1
 * @date 2021-08-21
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef MVK_RECTANGLE_H_
#define MVK_RECTANGLE_H_

#include "common/point.hpp"
#include <array>

namespace mvk
{
    /**
     * @brief 
     * 
     */
   struct Rect
   {
       Point2f topleft;
       Point2f topright;
       Point2f bottomright;
       Point2f bottomleft;
   };
   
   /**
    * @brief 获取矩形框的中心点坐标
    * 
    * @param rect(in) 矩形 
    * @return Point2f 
    */
   Point2f GetRectCenter(const Rect& rect);
} // namespace mvk


#endif //MVK_RECTANGLE_H_

