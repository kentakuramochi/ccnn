///
/// @file   layer.h
/// @brief  network layer
///

#ifndef LAYER_H
#define LAYER_H

#include <stdlib.h>

#include "mat.h"

///
/// @struct layer_t
/// @brief  layer structure
///
typedef struct layer_t {
    mat_t* x;   ///< input
    mat_t* y;   ///< output
    mat_t* w;   ///< weight
    mat_t* dw;  ///< weight differential
    mat_t* b;   ///< bias
    mat_t* db;  ///< bias differential

    struct layer_t* prev;   ///< pointer of prev layer
    struct layer_t* next;   ///< pointer of next layer

    void (*forward)(struct layer_t*, const mat_t*);   ///< forward processing
    void (*backward)(struct layer_t*, const mat_t*);  ///< backward processing
} layer_t;

///
/// @fn     layer_alloc
/// @brief  allocate new layer
/// @return pointer to new layer
///
layer_t* layer_alloc(void)
{
    layer_t* layer = (layer_t*)malloc(sizeof(layer_t));
    if (layer == NULL) {
        return NULL;
    }

    layer->x = NULL;
    layer->y = NULL;

    layer->w    = NULL;
    layer->dw   = NULL;

    layer->b    = NULL;
    layer->db   = NULL;

    layer->prev = NULL;
    layer->next = NULL;

    layer->forward  = NULL;
    layer->backward = NULL;

    return layer;
}

///
/// @fn     layer_free
/// @brief  free layer
/// @param[in]  layer   layer
///
void layer_free(layer_t* layer)
{
    if (layer == NULL) {
        return;
    }

    mat_free(layer->x);
    mat_free(layer->y);

    mat_free(layer->w);
    mat_free(layer->dw);

    mat_free(layer->b);
    mat_free(layer->db);

    free(layer);
}

#endif
