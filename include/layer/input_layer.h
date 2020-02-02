///
/// @file   input_layer.h
/// @brief  input layer
///

#ifndef INPUT_LAYER_H
#define INPUT_LAYER_H

#include "layer.h"

void forward_input(layer_t* input) {}

layer_t* input(const int n, const int c, const int h, const int w)
{
    layer_t* input = layer_create();

    input->type = LAYER_INPUT;

    input->in  = ndmat_create(n, c, h, w);
    input->out = input->in;

    input->forward = forward_input;

    return input;
}

#endif // INPUT_LAYER_H
