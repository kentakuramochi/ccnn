///
/// @file   ndmat.h
/// @brief  data structure for network
///

#ifndef NDMAT_H
#define NDMAT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

///
/// @def    MAX_DIM
/// @brief  maximum dimension of ndmat
///
#define MAX_DIM 4

///
/// @struct ndmat
/// @brief  data structure for network
/// @note   row-major, NCHW format
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

///
/// @fn     ndmat_create
/// @brief  create ndmat with specified dimension
/// @param[in]  n   matrix number
/// @param[in]  c   matrix channel
/// @param[in]  h   matrix height
/// @param[in]  w   matrix width
/// @return     pointer to ndmat
///
ndmat* ndmat_create(const int n, const int c, const int h, const int w)
{
    if ((n <= 0) || (c <= 0) || (h <= 0) || (w <= 0)) {
        return NULL;
    }

    ndmat* mat = (ndmat*)malloc(sizeof(ndmat));
    if (mat == NULL) {
        return NULL;
    }

    mat->shape[0] = n;
    mat->shape[1] = c;
    mat->shape[2] = h;
    mat->shape[3] = w;

    mat->n = n;
    mat->c = c;
    mat->h = h;
    mat->w = w;

    mat->dim  = 4;

    int elem = n * c * h * w;
    mat->elem = elem;

    mat->data = (float*)malloc(sizeof(float) * elem);
    if (mat->data == NULL) {
        free(mat);
        mat = NULL;
        return NULL;
    }

    return mat;
}

///
/// @fn     ndmat_set_array
/// @brief  set ndmat data from specified array
/// @param[out] mat     ndmat
/// @param[in]  array   data source array
/// @param[in]  elem    number of elements
/// @retval     true    succeeded
/// @retval     false   failed
///
bool ndmat_set_array(ndmat* mat, const float* array, const int elem)
{
    if ((mat == NULL) || (array == NULL)) {
        return false;
    }

    if (elem != mat->elem) {
        return false;
    }

    memcpy(mat->data, array, (sizeof(float) * elem));

    return true;
}

///
/// @fn     ndmat_fill
/// @brief  fill ndmat data with specified value
/// @param[out] mat     ndmat
/// @param[in]  value   filling value
///
void ndmat_fill(ndmat* mat, const float value)
{
    if (mat == NULL) {
        return;
    }

    for (int i = 0; i < mat->elem; i++) {
        mat->data[i] = value;
    }
}

///
/// @fn     ndmat_delete
/// @brief  delete ndmat
/// @param[out] mat     ndmat data
///
void ndmat_delete(ndmat *mat)
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

///
/// @fn     ndmat_savenpy
/// @brief  save ndmat data as npy file
/// @param[out] mat     ndmat data
/// @param[out] file    file name
///
void ndmat_savenpy(const ndmat *mat, const char* file)
{
    // npy header
    // 4Byte float, little endian
    // row-major order
    char header[256];
    snprintf(header, sizeof(header),
        "\x93NUMPY@@@@{'descr': '<f4', 'fortran_order': False, 'shape': (%d, %d, %d, %d), }", mat->n, mat->c, mat->h, mat->w);

    // padding length for alignment
    int pad_len = 16 - (strlen(header) + 1) % 16;

    // append padding 0x20 (' ') to the end of header and terminate by LF
    int idx = strlen(header);
    for (int i = 0; i < pad_len; i++) {
        header[idx++] = ' ';
    }
    header[idx++] = '\n';

    // header length: unsigned 16bit integer, little endian
    uint16_t header_len = strlen(header) - 10;

    header[8] = (uint8_t)(header_len & 0x00ff);
    header[9] = (uint8_t)(header_len & 0xff00);

    // version number: v1.0
    header[6] = '\x1';
    header[7] = '\x0';

    FILE *fp = fopen(file, "wb");

    fwrite(header, 1, idx, fp);
    fwrite(mat->data, sizeof(float), mat->elem, fp);

    fclose(fp);
}

#endif // NDMAT_H 
