///
/// @file   sigmoid_layer.h
/// @brief  sigmoid layer
///

#ifndef SIGMOID_LAYER_H
#define SIGMOID_LAYER_H

#include "layer.h"
#include "activation.h"

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
/// @fn     sigmoid_layer
/// @brief  alloc sigmoid layer
/// @param[in]  x   input size 
///
layer_t* sigmoid_layer(const int x)
{
    layer_t* self = layer_alloc();
    if (self == NULL) {
        return NULL;
    }

    self->y = mat_alloc(1, x);

    self->forward = sigmoid_forward;

    return self;
}

#endif
