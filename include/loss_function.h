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
/// @brief  mean squared error
/// @param[in]  y   predicted matrix
/// @param[in]  t   correct matrix
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

#endif
