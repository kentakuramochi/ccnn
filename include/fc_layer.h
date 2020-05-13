///
/// @file   fc_layer.h
/// @brief  fully connected layer
///

#ifndef FC_LAYER_H
#define FC_LAYER_H

#include "layer.h"

///
/// @fn     fc_forward
/// @brief  forward of fc layer
/// @param[in]  self    layer
/// @param[in]  x       input matrix
///
static void fc_forward(layer_t* self, const mat_t* x)
{
    mat_mul(x, self->w, self->y);
    mat_add(self->y, self->b, self->y);
}

///
/// @fn     fc_backward
/// @brief  backward of fc layer
/// @param[in]  self    layer
/// @param[in]  x       input matrix
///
static void fc_backward(layer_t* self, const mat_t* x)
{
}

///
/// @fn     fc_layer
/// @brief  alloc fc layer
/// @param[in]  x   input size
/// @param[in]  y   output size
/// @return     pointer to new layer
///
layer_t* fc_layer(const int x, const int y)
{
    layer_t* self = layer_alloc();
    if (self == NULL) {
        return NULL;
    }

    self->w     = mat_alloc(x, y);
    self->dw    = mat_alloc(x, y);

    self->b     = mat_alloc(1, y);
    self->db    = mat_alloc(1, y);

    self->y = mat_alloc(1, y);

    self->forward   = fc_forward;
    self->backward  = fc_backward;

    return self;
}

#endif
