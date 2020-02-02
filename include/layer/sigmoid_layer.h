///
/// @file   sigmoid_layer.h
/// @brief  sigmoid layer
///

#ifndef SIGMOID_LAYER_H
#define SIGMOID_LAYER_H

#include <math.h>

#include "layer.h"

void forward_sigmoid(layer_t* sigmoid)
{
    for (int i = 0; i < sigmoid->in->elem; i++) {
        sigmoid->out->data[i] = 1.0 / (1 + exp(-sigmoid->in->data[i]));
    }
}

layer_t* sigmoid(layer_t* prev)
{
    layer_t* sigmoid = layer_create();

    sigmoid->type = LAYER_SIGMOID;

    if (prev != NULL) {
        sigmoid->in   = prev->out;
        sigmoid->prev = prev;

        sigmoid->out = ndmat_create(prev->out->n, prev->out->c, prev->out->h, prev->out->w);
    }

    sigmoid->forward = forward_sigmoid;

    return sigmoid;
}

#endif // SIGMOID_LAYER_H
