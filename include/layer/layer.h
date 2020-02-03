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
    LAYER_FC,       ///< fully connected
    LAYER_RELU,     ///< ReLU
    LAYER_SIGMOID,  ///< sigmoid
    LAYER_SOFTMAX   ///< softmax
} LAYER_TYPE;

///
/// @struct layer_t
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
} layer_t;

///
/// @fn     layer_create
/// @brief  create layer
/// @return pointer to layer
///
layer_t* layer_create(void)
{
    layer_t* layer = (layer_t*)malloc(sizeof(layer_t));

    layer->type = LAYER_NONE;

    layer->in  = NULL;
    layer->out = NULL;
    layer->w   = NULL;
    layer->b   = NULL;

    layer->prev = NULL;
    layer->next = NULL;

    layer->forward = NULL;

    return layer;
}

///
/// @fn     layer_create_input
/// @brief  create input data with shape
/// @param[out] layer   layer
/// @param[in]  n       num of data
/// @param[in]  c       num of data channel
/// @param[in]  h       data height
/// @param[in]  w       data width
///
void layer_create_input(layer_t* layer, const int n, const int c, const int h, const int w)
{
    if (layer->in != NULL) {
        ndmat_delete(layer->in);
    }

    layer->in = ndmat_create(n, c, h, w);
}

///
/// @fn     layer_create_output
/// @brief  create output data with shape
/// @param[out] layer   layer
/// @param[in]  n       num of data
/// @param[in]  c       num of data channel
/// @param[in]  h       data height
/// @param[in]  w       data width
///
void layer_create_output(layer_t* layer, const int n, const int c, const int h, const int w)
{
    if (layer->out != NULL) {
        ndmat_delete(layer->out);
    }

    layer->out = ndmat_create(n, c, h, w);
}

///
/// @fn     layer_create_weight
/// @brief  create weight data with shape
/// @param[out] layer   layer
/// @param[in]  n       num of data
/// @param[in]  c       num of data channel
/// @param[in]  h       data height
/// @param[in]  w       data width
///
void layer_create_weight(layer_t* layer, const int n, const int c, const int h, const int w)
{
    if (layer->w != NULL) {
        ndmat_delete(layer->w);
    }

    layer->w = ndmat_create(n, c, h, w);
}

///
/// @fn     layer_create_bias
/// @brief  create bias data with shape
/// @param[out] layer   layer
/// @param[in]  n       num of data
/// @param[in]  c       num of data channel
/// @param[in]  h       data height
/// @param[in]  w       data width
///
void layer_create_bias(layer_t* layer, const int n, const int c, const int h, const int w)
{
    if (layer->b != NULL) {
        ndmat_delete(layer->b);
    }

    layer->b = ndmat_create(n, c, h, w);
}

///
/// @fn     layer_connect
/// @brief  connect layer
/// @param[in]  prev    previous layer
/// @param[in]  next    next layer
///
void layer_connect(layer_t* prev, layer_t* next)
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
void layer_delete(layer_t* layer)
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
