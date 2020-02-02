///
/// @file   fc_layer.h
/// @brief  fully connected layer
///

#ifndef FC_LAYER_H
#define FC_LAYER_H

#include "layer.h"

void forward_fc(layer_t* fc)
{
    for (int n = 0; n < fc->out->n; n++) {
        float* in  = &fc->in->data[n * (fc->in->c * fc->in->h * fc->in->w)];
        float* w   = &fc->w->data[n * (fc->w->c * fc->w->h * fc->w->w)];
        float* out = &fc->out->data[n * (fc->in->c * fc->in->h * fc->in->w)];
        float* b   = &fc->b->data[n * (fc->b->c * fc->b->c * fc->b->h * fc->w->w)];
        for (int c = 0; c < fc->out->c; c++) {
            float sum = b[c];
            for (int i = 0; i < (fc->out->c * fc->out->h * fc->out->w); i++) {
                sum += w[i] * in[i];
            }
            out[c] = sum;
        }
    }
}

layer_t* fc(layer_t* prev, int out)
{
    layer_t* fc = layer_create();

    fc->type = LAYER_FC;

    if (prev != NULL) {
        fc->in   = prev->out;
        fc->prev = prev;

        fc->out = ndmat_create(prev->out->n, out, 1, 1);

        fc->w = ndmat_create(prev->out->n, out, prev->out->h, prev->out->w);
        fc->b = ndmat_create(prev->out->n, out, 1, 1);
    }

    fc->forward = forward_fc;

    return fc;
}

#endif // FC_LAYER_H
