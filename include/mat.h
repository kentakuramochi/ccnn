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

    if (memcpy(mat->data, array, (sizeof(float) * mat->row * mat->col)) == NULL) {
        return NULL;
    }

    return mat;
}

///
/// @fn     mat_copy
/// @brief  copy matrix data
/// @param[out] dst dest matrix
/// @param[in]  src source matrix
/// @return     pointer to matrix
///
mat_t* mat_copy(mat_t* dst, const mat_t* src)
{
    if ((dst == NULL) || (src == NULL)) {
        return NULL;
    }

    if ((dst->row != src->row) || (dst->col != src->col)) {
        return NULL;
    }
    
    if (memcpy(dst->data, src->data, (sizeof(float) * src->row * src->col)) == NULL) {
        return NULL;
    }

    return dst;
}

///
/// @fn     mat_clone
/// @brief  clone matrix
/// @param[in]  src source matrix
/// @return     pointer to new matrix
///
mat_t* mat_clone(const mat_t* src)
{
    if (src == NULL) {
        return NULL;
    }

    mat_t* mat = mat_alloc(src->row, src->col);
    if (mat == NULL) {
        free(mat);
        return NULL;
    }
    
    if (memcpy(mat->data, src->data, (sizeof(float) * src->row * src->col)) == NULL) {
        mat_free(mat);
        return NULL;
    }

    return mat;
}

///
/// @fn     mat_add
/// @brief  add matrix c = a + b
/// @param[in]  a   src matrix 1
/// @param[in]  b   src matrix 2
/// @param[out] c   dst matrix
/// @return     pointer to c
/// @note   omit size checking
///
mat_t* mat_add(const mat_t* a, const mat_t* b, mat_t* c)
{
    for (int i = 0; i < (a->row * a->col); i++) {
        c->data[i] = a->data[i] + b->data[i];
    }

    return c;
}

///
/// @fn     mat_sub
/// @brief  subtract matrix c = a - b
/// @param[in]  a   src matrix 1
/// @param[in]  b   src matrix 2
/// @param[out] c   dst matrix
/// @return     pointer to c
/// @note   omit size checking
///
mat_t* mat_sub(const mat_t* a, const mat_t* b, mat_t* c)
{
    for (int i = 0; i < (a->row * a->col); i++) {
        c->data[i] = a->data[i] - b->data[i];
    }

    return c;
}

///
/// @fn     mat_mul_scalar
/// @brief  scalar multiply matrix b = k * a 
/// @param[in]  a   src matrix
/// @param[in]  k   coefficient
/// @param[out] b   dst matrix
/// @return     pointer to b
/// @note   omit size checking
///
mat_t* mat_mul_scalar(const mat_t* a, const float k, mat_t* b)
{
    for (int i = 0; i < (a->row * a->col); i++) {
        b->data[i] = k * a->data[i];
    }

    return b;
}

///
/// @fn     mat_mul
/// @brief  multiply matrix: c = a x b
/// @param[in]  a   matrix
/// @param[in]  b   matrix
/// @param[out] c   matrix
/// @return     pointer to c
/// @note   omit size checking
///
mat_t* mat_mul(const mat_t* a, const mat_t* b, mat_t* c)
{
    for (int i = 0; i < a->row; i++) {
        for (int j = 0; j < b->col; j++) {
            float sum = 0;
            for (int k = 0; k < a->col; k++) {
                sum += a->data[i * a->col + k] * b->data[k * b->col + j];
            }
            c->data[i * b->col + j] = sum;
        }
    }

    return c;
}

///
/// @fn     mat_trans
/// @brief  transpose matrix
/// @param[in]  a   src matrix
/// @param[out] ta  transposed matrix
/// @return     pointer to ta
/// @note   omit size checking
///
mat_t* mat_trans(const mat_t* a, mat_t* ta)
{
    for (int i = 0; i < a->row; i++) {
        for (int j = 0; j < a->col; j++) {
            ta->data[j * a->row + i] = a->data[i * a->col + j];
        }
    }

    return ta;
}

#endif
