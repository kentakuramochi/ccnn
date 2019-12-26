///
/// @file   fc_layer.h
/// @brief  fully convolution layer
///

#ifndef FC_LAYER_H
#define FC_LAYER_H

#include "layer.h"

void forward_fc(layer* l) {

}

layer* fc(layer* prev, int out)
{
    layer* l_fc = create_layer();

    l_fc->type = LAYER_FC;

    l_fc->in  = create_ndmat(4, prev->out->n, prev->out->c, prev->out->h, prev->out->w);
    l_fc->out = create_ndmat(4, prev->out->n, out, 1, 1);

    l_fc->w = create_ndmat(4, prev->out->n, out, prev->out->h, prev->out->w);
    l_fc->b = create_ndmat(4, prev->out->n, out, 1, 1);

    l_fc->forward = forward_fc;

    return l_fc;
}

#endif // FC_LAYER_H
