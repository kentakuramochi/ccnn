///
/// @file   sigmoid_layer.h
/// @brief  sigmoid layer
///

#ifndef SIGMOID_LAYER_H
#define SIGMOID_LAYER_H

#include <math.h>

#include "layer.h"

void forward_sigmoid(layer* sigmoid)
{
    for (int i = 0; i < sigmoid->in->elem; i++) {
        sigmoid->out->data[i] = 1.0 / (1 + exp(-sigmoid->in->data[i]));
    }
}

layer* sigmoid(layer* prev)
{
    layer* sigmoid = create_layer();

    sigmoid->type = LAYER_SIGMOID;

    if (prev != NULL) {
        sigmoid->in   = prev->out;
        sigmoid->prev = prev;

        sigmoid->out = create_ndmat(prev->out->n, prev->out->c, prev->out->h, prev->out->w);
    }

    sigmoid->forward = forward_sigmoid;

    return sigmoid;
}

#endif // SIGMOID_LAYER_H
