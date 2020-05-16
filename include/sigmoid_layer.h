///
/// @file   sigmoid_layer.h
/// @brief  sigmoid layer
///

#ifndef SIGMOID_LAYER_H
#define SIGMOID_LAYER_H

#include <math.h>
#include <float.h>

#include "layer.h"

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

///
/// @fn     sigmoid_forward
/// @brief  forward of sigmoid layer
/// @param[in]  self    layer
/// @param[in]  x       input matrix
///
static void sigmoid_forward(layer_t* self, const mat_t* x)
{
    for (int i = 0; i < (x->row * x->col); i++) {
        self->y->data[i] = sigmoid(x->data[i]);
    }
}

///
/// @fn     sigmoid_backward
/// @brief  backward of sigmoid layer
/// @param[in]  self    layer
/// @param[in]  dy      output differential
///
static void sigmoid_backward(layer_t* self, const mat_t* dy)
{
    for (int i = 0; i < (dy->row * dy->col); i++) {
        self->dx->data[i] = dy->data[i] * self->y->data[i] * (1 - self->y->data[i]);
    }
}

///
/// @fn     sigmoid_layer
/// @brief  alloc sigmoid layer
/// @param[in]  x   input size 
/// @return     pointer to new layer
///
layer_t* sigmoid_layer(const int x)
{
    layer_t* self = layer_alloc();
    if (self == NULL) {
        return NULL;
    }

    self->dx = mat_alloc(1, x);

    self->y = mat_alloc(1, x);

    self->forward   = sigmoid_forward;
    self->backward  = sigmoid_backward;

    return self;
}

#endif
