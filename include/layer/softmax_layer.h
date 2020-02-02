///
/// @file   softmax_layer.h
/// @brief  softmax layer
///

#ifndef SOFTMAX_LAYER_H
#define SOFTMAX_LAYER_H

#include <math.h>

#include "layer.h"

void forward_softmax(layer_t* softmax)
{
    for (int n = 0; n < softmax->in->n; n++) {
        float *in  = &softmax->in->data[n * (softmax->in->c * softmax->in->h * softmax->in->w)];
        float *out = &softmax->out->data[n * (softmax->out->c * softmax->out->h * softmax->out->w)];

        float sum = 0;
        for (int i = 0; i < (softmax->in->c * softmax->in->h * softmax->in->w); i++) {
            sum += exp(in[i]);
        }

        for (int i = 0; i < (softmax->in->c * softmax->in->h * softmax->in->w); i++) {
            out[i] = exp(in[i]) / sum;
        }
    }
}

layer_t* softmax(layer_t* prev)
{
    layer_t* softmax = layer_create();

    softmax->type = LAYER_SOFTMAX;

    if (prev != NULL) {
        softmax->in   = prev->out;
        softmax->prev = prev;

        softmax->out = ndmat_create(prev->out->n, prev->out->c, prev->out->h, prev->out->w);
    }

    softmax->forward = forward_softmax;

    return softmax;
}

#endif // SOFTMAX_LAYER_H
