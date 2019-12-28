///
/// @file   fc_layer.h
/// @brief  fully connected layer
///

#ifndef FC_LAYER_H
#define FC_LAYER_H

#include "layer.h"

void forward_fc(layer* fc)
{
    for (int n = 0; n < fc->out->n; n++) {
        for (int c = 0; c < fc->out->c; c++) {
            float sum = fc->b->data[n * fc->b->c + c];
            for (int i = 0; i < (fc->out->c * fc->out->h * fc->out->w); i++) {
                sum += fc->w->data[n * (fc->w->c * fc->w->h * fc->w->w) + i] * fc->in->data[n * (fc->in->c * fc->in->h * fc->in->w) + i];
            }
            fc->out->data[n * fc->out->c + c] = sum;
        }
    }
}

layer* fc(layer* prev, int out)
{
    layer* fc = create_layer();

    fc->type = LAYER_FC;

    fc->in  = create_ndmat(4, prev->out->n, prev->out->c, prev->out->h, prev->out->w);
    fc->out = create_ndmat(4, prev->out->n, out, 1, 1);

    fc->w = create_ndmat(4, prev->out->n, out, prev->out->h, prev->out->w);
    fc->b = create_ndmat(4, prev->out->n, out, 1, 1);

    fc->forward = forward_fc;

    return fc;
}

#endif // FC_LAYER_H
