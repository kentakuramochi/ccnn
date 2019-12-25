///
/// @file   output_layer.h
/// @brief  output layer
///

#ifndef OUTPUT_LAYER_H
#define OUTPUT_LAYER_H

#include "layer.h"

void forward_output(layer* l) {}

layer* output(layer* prev)
{
    layer* l_out = create_layer();

    l_out->type = LAYER_OUT;

    l_out->in  = create_ndmat(4, prev->out->n, prev->out->c, prev->out->h, prev->out->w);
    l_out->out = l_out->in;

    l_out->forward = forward_output;

    return l_out;
}

#endif // OUTPUT_LAYER_H
