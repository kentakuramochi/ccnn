///
/// @file   input_layer.h
/// @brief  input layer
///

#ifndef INPUT_LAYER_H
#define INPUT_LAYER_H

#include "layer.h"

void forward_input(layer* l) {}

layer* input(const int n, const int c, const int h, const int w)
{
    layer* l_in = create_layer();

    l_in->type = LAYER_IN;

    l_in->in  = create_ndmat(4, n, c, h, w);
    l_in->out = l_in->in;

    l_in->forward = forward_input;

    return l_in;
}

#endif // INPUT_LAYER_H
