///
/// @file   loss_function.h
/// @brief  loss function
///

#ifndef LOSS_FUNCTION_H
#define LOSS_FUNCTION_H

#include <math.h>

#include "mat.h"

///
/// @fn     loss_mse
/// @brief  mean squared error loss
/// @param[in]  y   predicted matrix
/// @param[in]  t   correct matrix
/// @return     mean squared error loss
///
static float loss_mse(const mat_t* y, const mat_t* t)
{
    int     size = y-> row * y->col;
    float   diff = 0;

    for (int i = 0; i < size; i++) {
        diff += ((y->data[i] - t->data[i]) * (y->data[i] - t->data[i]));
    }

    return (0.5 / size) * diff;
}

///
/// @fn     loss_cross_entropy
/// @brief  cross entropy loss
/// @param[in]  y   predicted matrix
/// @param[in]  t   correct matrix
/// @return     cross entropy loss
///
static float loss_cross_entropy(const mat_t* y, const mat_t* t)
{
    int     size = y-> row * y->col;
    float   diff = 0;

    for (int i = 0; i < size; i++) {
        diff += (t->data[i] * logf(y->data[i] + 1e-7));
    }

    return -1.0 * diff;
}

#endif
