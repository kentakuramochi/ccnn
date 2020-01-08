///
/// @file   layer.h
/// @brief  network layer
///

#ifndef LAYER_H
#define LAYER_H

#include <stdlib.h>
#include <string.h>

#include "ndmat.h"

///
/// @def    LAYER_NAME_LEN
/// @brief  max length of layer name
///
#define LAYER_NAME_LEN 32

///
/// @enum   LAYER_TYPE
/// @brief  type of layer
///
typedef enum {
    LAYER_NONE,
    LAYER_IN,       ///< input
    LAYER_FC,       ///< fully convolution
    LAYER_RELU,     ///< ReLU
    LAYER_SIGMOID,  ///< sigmoid
    LAYER_SOFTMAX   ///< softmax
} LAYER_TYPE;

///
/// @struct layer
/// @brief  network layer
///
typedef struct layer_tag {
    LAYER_TYPE type;
    char name[LAYER_NAME_LEN + 1];

    ndmat* in;
    ndmat* out;
    ndmat* w;
    ndmat* b;

    struct layer_tag* prev;
    struct layer_tag* next;

    void (*forward)(struct layer_tag*);
} layer;

///
/// @fn     create_layer
/// @brief  create layer
/// @return pointer to layer
///
layer* create_layer(void)
{
    layer* l = (layer*)malloc(sizeof(layer));

    l->type = LAYER_NONE;

    l->in  = NULL;
    l->out = NULL;
    l->w   = NULL;
    l->b   = NULL;

    l->prev = NULL;
    l->next = NULL;

    l->forward = NULL;

    return l;
}

///
/// @fn     set_input_shape
/// @brief  set input data with shape
/// @param[out] l   layer
/// @param[in]  n   num of data
/// @param[in]  c   num of data channel
/// @param[in]  h   data height
/// @param[in]  w   data width
///
void set_input_shape(layer* l, const int n, const int c, const int h, const int w)
{
    if (l->in != NULL) {
        delete_ndmat(l->in);
    }

    l->in = create_ndmat(4, n, c, h, w);
}

///
/// @fn     set_output_shape
/// @brief  set output data with shape
/// @param[out] l   layer
/// @param[in]  n   num of data
/// @param[in]  c   num of data channel
/// @param[in]  h   data height
/// @param[in]  w   data width
///
void set_output_shape(layer* l, const int n, const int c, const int h, const int w)
{
    if (l->out != NULL) {
        delete_ndmat(l->out);
    }

    l->out = create_ndmat(4, n, c, h, w);
}

///
/// @fn     connect_layer
/// @brief  connect layer
/// @param[in]  prev    previous layer
/// @param[in]  next    next layer
///
void connect_layer(layer* prev, layer* next)
{
    if ((prev == NULL) || (next == NULL)) {
        return;
    }

    prev->next = next;
    next->prev = prev;

    next->in = prev->out;
}

///
/// @fn     delete_layer
/// @brief  delete layer
/// @param[in]  layer   layer
///
void delete_layer(layer* layer)
{
    if (layer == NULL) {
        return;
    }

    delete_ndmat(layer->in);
    layer->in = NULL;
    delete_ndmat(layer->out);
    layer->out = NULL;
    delete_ndmat(layer->w);
    layer->w = NULL;
    delete_ndmat(layer->b);
    layer->b = NULL;

    free(layer);
    layer = NULL;
}

#endif // LAYER_H 
