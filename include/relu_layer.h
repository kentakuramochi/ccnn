///
/// @file   relu_layer.h
/// @brief  relu layer
///

#ifndef RELU_LAYER_H
#define RELU_LAYER_H

#include <math.h>
#include <float.h>

#include "layer.h"

///
/// @fn         relu
/// @brief      relu function
/// @param[in]  x   x
/// @return     relu(x)
///
static float relu(const float x)
{
    return (x > 0) ? x : 0;
}

///
/// @fn     relu_forward
/// @brief  forward of relu layer
/// @param[in]  self    layer
/// @param[in]  x       input matrix
///
static void relu_forward(layer_t* self, const mat_t* x)
{
    for (int i = 0; i < (x->row * x->col); i++) {
        self->y->data[i] = relu(x->data[i]);
    }
}

///
/// @fn     relu_backward
/// @brief  backward of relu layer
/// @param[in]  self    layer
/// @param[in]  x       input matrix
///
static void relu_backward(layer_t* self, const mat_t* x)
{
}

///
/// @fn     relu_layer
/// @brief  alloc relu layer
/// @param[in]  x   input size 
/// @return     pointer to new layer
///
layer_t* relu_layer(const int x)
{
    layer_t* self = layer_alloc();
    if (self == NULL) {
        return NULL;
    }

    self->y = mat_alloc(1, x);

    self->forward   = relu_forward;
    self->backward  = relu_backward;

    return self;
}

#endif
