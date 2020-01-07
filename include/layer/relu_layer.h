///
/// @file   relu_layer.h
/// @brief  ReLU layer
///

#ifndef RELU_LAYER_H
#define RELU_LAYER_H

#include "layer.h"

void forward_relu(layer* relu)
{
    for (int i = 0; i < relu->in->elem; i++) {
        relu->out->data[i] = (relu->in->data[i] > 0) ? relu->in->data[i] : 0;
    }
}

layer* relu(layer* prev)
{
    layer* relu = create_layer();

    relu->type = LAYER_RELU;

    if (prev != NULL) {
        relu->in   = prev->out;
        relu->prev = prev;

        relu->out = create_ndmat(4, prev->out->n, prev->out->c, prev->out->h, prev->out->w);
    }

    relu->forward = forward_relu;

    return relu;
}

#endif // RELU_LAYER_H
