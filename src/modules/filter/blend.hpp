//
// Created by mango on 2024/2/28.
//

#ifndef MANGO_BLEND_H
#define MANGO_BLEND_H

#include "core/image.hpp"

/**
 * dst = src1 * alpha + src2 * beta + gamma
 * @param src1
 * @param alpha
 * @param src2
 * @param beta
 * @param dst
 * @param gamma
 * @return
 */
int AddWeighted(Image src1, const float alpha, Image src2, const float beta, Image dst ,const float gamma = 0);


/**
 *
 * @param src
 * @param blend
 * @param dst
 * @return
 */
int NormalBlend(Image src, Image blend, Image& dst);

#endif //MANGO_BLEND_H
