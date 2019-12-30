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
    LAYER_RELU      ///< ReLU
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

    void*(forward)(struct layer_tag*);
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

    l->in   = NULL;
    l->out  = NULL;
    l->w    = NULL;
    l->b    = NULL;

    l->prev = NULL;
    l->next = NULL;

    l->forward = NULL;

    return l;
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

    next->in = create_ndmat(prev->out->dim, prev->out->n, prev->out->c, prev->out->h, prev->out->w);
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
    delete_ndmat(layer->out);
    delete_ndmat(layer->w);
    delete_ndmat(layer->b);

    free(layer);
    layer = NULL;
}

#endif // LAYER_H 
