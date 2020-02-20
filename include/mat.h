///
/// @file   mat.h
/// @brief  2-d matrix data and ops
///

#ifndef MAT_H
#define MAT_H

#include <stdlib.h>
#include <string.h>

///
/// @struct mat_t
/// @brief  2-d matrix data
/// @note   row-major, float
///
typedef struct {
    int     row;    ///< row
    int     col;    ///< column
    float*  data;   ///< matrix data
} mat_t;

///
/// @fn     mat_alloc
/// @brief  allocate new m x n matrix
/// @param[in]  m   matrix row
/// @param[in]  n   matrix column
/// @return     pointer to new matrix
///
mat_t* mat_alloc(const int m, const int n)
{
    if ((m <= 0) || (n <= 0)) {
        return NULL;
    }

    mat_t* mat = malloc(sizeof(mat_t));
    if (mat == NULL) {
        return NULL;
    }

    mat->row = m;
    mat->col = n;
    mat->data = malloc(sizeof(float) * m * n);
    if (mat->data == NULL) {
        free(mat);
        return NULL;
    }

    return mat;
}

///
/// @fn     mat_free
/// @brief  free matrix
/// @param[in]  mat matrix
///
void mat_free(mat_t* mat)
{
    if (mat == NULL) {
        return;
    }

    if (mat->data != NULL) {
        free(mat->data);
        mat->data = NULL;
    }

    free(mat);
}

///
/// @fn     mat_copy_array
/// @brief  copy matrix data from 1-d array
/// @param[out] mat     matrix
/// @param[in]  array   source
/// @return     pointer to matrix
///
mat_t* mat_copy_array(mat_t* mat, const float* array)
{
    if ((mat == NULL) || (array == NULL)) {
        return NULL;
    }

    return (mat_t*)memcpy(mat->data, array, (sizeof(float) * mat->row * mat->col));
}

#endif
