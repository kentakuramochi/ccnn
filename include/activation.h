///
/// @file   activation.h
/// @brief  activation function
///
//
#ifndef ACTIVATION_H
#define ACTIVATION_H

#include <math.h>
#include <float.h>

///
/// @fn         sigmoid
/// @brief      sigmoid function
/// @param[in]  x   x
/// @return     sigmoid(x)
///
static float sigmoid(const float x)
{
    return 1.0 / (1 + expf(-x));
}

#endif
