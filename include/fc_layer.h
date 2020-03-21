///
/// @file   fc_layer.h
/// @brief  fully connected layer
///

#ifndef FC_LAYER_H
#define FC_LAYER_H

#include "layer.h"

///
/// @fn     fc_forward
/// @brief  forward 
/// @param[in]  fc  fc layer
/// @param[in]  x   input matrix
///
static void fc_forward(layer_t* fc, const mat_t* x)
{
    mat_mul(x, fc->w, fc->y);
    mat_add(fc->y, fc->b, fc->y);
}

///
/// @fn     fc
/// @brief  alloc fc layer
/// @param[in]  x   input width 
/// @param[in]  y   output width
///
layer_t* fc(const int x, const int y)
{
    layer_t* fc = layer_alloc();
    if (fc == NULL) {
        return NULL;
    }

    fc->w = mat_alloc(x, y);
    fc->b = mat_alloc(1, y);
    fc->y = mat_alloc(1, y);

    fc->forward = fc_forward;

    return fc;
}

#endif
