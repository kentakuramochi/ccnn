///
/// @file   ndmat.h
/// @brief  data structure for network
///

#ifndef NDMAT_H
#define NDMAT_H

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdarg.h>

///
/// @struct MAX_DIM
/// @brief  maximum dimension of ndmat
///
#define MAX_DIM 32

///
/// @struct ndmat
/// @brief  data structure for network
///
typedef struct {
    int     shape[MAX_DIM]; ///< data shape
    int     dim;            ///< data dimension
    int     elem;           ///< num of total elements
    int     n;              ///< num
    int     c;              ///< channel
    int     h;              ///< height
    int     w;              ///< width
    float*  data;           ///< data
} ndmat;

ndmat* create_ndmat(const int dim, ...)
{
    if ((dim <= 0) || (dim >= MAX_DIM))  {
        return NULL;
    }

    va_list ap;

    va_start(ap, dim);

    int shape[MAX_DIM];

    for (int i = 0; i < dim; i++) {
        int d = va_arg(ap, int);
        shape[i] = d;
    }

    va_end(ap);

    int elem = 1;
    for (int i = 0; i < dim; i++) {
        if (shape[i] < 0) {
            return NULL;
        }
        elem *= shape[i];
    }

    ndmat* mat = (ndmat*)malloc(sizeof(ndmat));
    if (mat == NULL) {
        return NULL;
    }

    memcpy(mat->shape, shape, sizeof(int) * dim);
    mat->dim  = dim;
    mat->elem = elem;

    mat->data = (float*)malloc(sizeof(float) * elem);
    if (mat->data == NULL) {
        free(mat);
        mat = NULL;
        return NULL;
    }

    mat->n = 1;
    mat->c = 1;
    mat->h = 1;

    mat->w = shape[dim - 1];
    switch (dim) {
        case 1:
            break;
        case 2:
            mat->h = shape[dim - 2];
            break;
        case 3:
            mat->c = shape[dim - 3];
            mat->h = shape[dim - 2];
            break;
        default:
            mat->n = shape[dim - 4];
            mat->c = shape[dim - 3];
            mat->h = shape[dim - 2];
            break;
    }

    return mat;
}

bool set_fromarray(ndmat* mat, const float* array, const int size)
{
    if ((mat == NULL) || (array == NULL)) {
        return false;
    }

    if (size != mat->elem) {
        return false;
    }

    memcpy(mat->data, array, (sizeof(float) * size));

    return true;
}

void delete_ndmat(ndmat *mat)
{
    if (mat == NULL) {
        return;
    }

    if (mat->data != NULL) {
        free(mat->data);
        mat->data = NULL;
    }

    free(mat);
    mat = NULL;
}

#endif // NDMAT_H 
