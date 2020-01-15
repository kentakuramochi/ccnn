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
    LAYER_INPUT,    ///< input
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
/// @fn     layer_create
/// @brief  create layer
/// @return pointer to layer
///
layer* layer_create(void)
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
/// @fn     layer_create_input
/// @brief  set input data with shape
/// @param[out] l   layer
/// @param[in]  n   num of data
/// @param[in]  c   num of data channel
/// @param[in]  h   data height
/// @param[in]  w   data width
///
void layer_create_input(layer* l, const int n, const int c, const int h, const int w)
{
    if (l->in != NULL) {
        ndmat_delete(l->in);
    }

    l->in = ndmat_create(n, c, h, w);
}

///
/// @fn     layer_create_output
/// @brief  set output data with shape
/// @param[out] l   layer
/// @param[in]  n   num of data
/// @param[in]  c   num of data channel
/// @param[in]  h   data height
/// @param[in]  w   data width
///
void layer_create_output(layer* l, const int n, const int c, const int h, const int w)
{
    if (l->out != NULL) {
        ndmat_delete(l->out);
    }

    l->out = ndmat_create(n, c, h, w);
}

///
/// @fn     layer_connect
/// @brief  connect layer
/// @param[in]  prev    previous layer
/// @param[in]  next    next layer
///
void layer_connect(layer* prev, layer* next)
{
    if ((prev == NULL) || (next == NULL)) {
        return;
    }

    prev->next = next;
    next->prev = prev;

    next->in = prev->out;
}

///
/// @fn     layer_delete
/// @brief  delete layer
/// @param[in]  layer   layer
///
void layer_delete(layer* layer)
{
    if (layer == NULL) {
        return;
    }

    ndmat_delete(layer->in);
    layer->in = NULL;
    ndmat_delete(layer->out);
    layer->out = NULL;
    ndmat_delete(layer->w);
    layer->w = NULL;
    ndmat_delete(layer->b);
    layer->b = NULL;

    free(layer);
    layer = NULL;
}

#endif // LAYER_H 
