///
/// @file   test_mat.c
/// @brief  test of matrix ops
///

#include "unity.h"

#include "mat.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_mat_alloc(void)
{
    mat_t* mat = mat_alloc(2, 3);

    TEST_ASSERT_NOT_NULL(mat);
    TEST_ASSERT_EQUAL(2, mat->row);
    TEST_ASSERT_EQUAL(3, mat->col);

    mat_free(mat);
}

void test_mat_alloc_failure(void)
{
    mat_t* mat;

    mat = mat_alloc(0, 1);
    TEST_ASSERT_NULL(mat);

    mat = mat_alloc(1, 0);
    TEST_ASSERT_NULL(mat);

    mat = mat_alloc(-1, 1);
    TEST_ASSERT_NULL(mat);
 
    mat = mat_alloc(1, -1);
    TEST_ASSERT_NULL(mat);

    mat_free(mat);
}

void test_mat_copy_array(void)
{
    mat_t* mat = mat_alloc(2, 3);

    float array[] = {
        0, 1, 2,
        3, 4, 5
    };

    TEST_ASSERT_EQUAL_PTR(mat, mat_copy_array(mat, array));

    TEST_ASSERT_EQUAL_FLOAT_ARRAY(array, mat->data, (2 * 3));

    mat_free(mat);
}

void test_mat_copy(void)
{
    mat_t* mat = mat_alloc(2, 3);

    float array[] = {
        0, 1, 2,
        3, 4, 5
    };

    mat_copy_array(mat, array);

    mat_t* mat2 = mat_alloc(2, 3);
    mat_copy_array(mat2, (float[]){ 1, 1, 1, 1, 1, 1 });

    TEST_ASSERT_EQUAL_PTR(mat2, mat_copy(mat2, mat));
    TEST_ASSERT_EQUAL_FLOAT_ARRAY(array, mat2->data, (2 * 3));

    mat_free(mat);
    mat_free(mat2);
}

void test_mat_copy_failure(void)
{
    mat_t* mat = mat_alloc(2, 3);

    float array[] = {
        0, 1, 2,
        3, 4, 5
    };

    mat_copy_array(mat, array);

    float array2[] = {
        1, 1,
        1, 1,
        1, 1
    };

    mat_t* mat2 = mat_alloc(3, 2);
    mat_copy_array(mat2, array2);
    TEST_ASSERT_NULL(mat_copy(mat2, mat));

    TEST_ASSERT_NOT_NULL(mat2);
    TEST_ASSERT_EQUAL_FLOAT_ARRAY(array2, mat2->data, (3 * 2));

    mat_free(mat);
    mat_free(mat2);
}

void test_mat_clone(void)
{
    mat_t* mat = mat_alloc(2, 3);

    float array[] = {
        0, 1, 2,
        3, 4, 5
    };

    mat_copy_array(mat, array);

    mat_t* mat2 = mat_clone(mat);
    TEST_ASSERT_NOT_NULL(mat2);

    TEST_ASSERT_EQUAL(2, mat2->row);
    TEST_ASSERT_EQUAL(3, mat2->col);

    TEST_ASSERT_EQUAL_FLOAT_ARRAY(array, mat2->data, (2 * 3));

    mat_free(mat);
    mat_free(mat2);
}

void test_mat_add(void)
{
    mat_t* a = mat_alloc(2, 3);
    mat_copy_array(a, (float[]){
        0, 1, 2,
        3, 4, 5
    });

    mat_t* b = mat_alloc(2, 3);
    mat_copy_array(b, (float[]){
        6, 7, 8,
        9, 10, 11
    });

    mat_t* c = mat_alloc(2, 3);

    TEST_ASSERT_EQUAL_PTR(c, mat_add(a, b, c));

    float correct[] = {
        6, 8, 10,
        12, 14, 16
    };

    TEST_ASSERT_EQUAL_FLOAT_ARRAY(correct, c->data, (c->row * c->col));

    mat_free(a);
    mat_free(b);
    mat_free(c);
}

void test_mat_sub(void)
{
    mat_t* a = mat_alloc(2, 3);
    mat_copy_array(a, (float[]){
        0, 1, 2,
        3, 4, 5
    });

    mat_t* b = mat_alloc(2, 3);
    mat_copy_array(b, (float[]){
        5, 4, 3,
        2, 1, 0
    });

    mat_t* c = mat_alloc(2, 3);

    TEST_ASSERT_EQUAL_PTR(c, mat_sub(a, b, c));

    float correct[] = {
        -5, -3, -1,
        1, 3, 5
    };

    TEST_ASSERT_EQUAL_FLOAT_ARRAY(correct, c->data, (c->row * c->col));

    mat_free(a);
    mat_free(b);
    mat_free(c);
}

void test_mat_mul_scalar(void)
{
    mat_t* a = mat_alloc(2, 3);
    mat_copy_array(a, (float[]){
        -2, -1, 0,
        1, 2, 3
    });

    float k = 2;

    mat_t* b  = mat_alloc(2, 3);

    TEST_ASSERT_EQUAL_PTR(b, mat_mul_scalar(a, k, b));

    float correct[] = {
        -4, -2, 0,
        2, 4, 6
    };

    TEST_ASSERT_EQUAL_FLOAT_ARRAY(correct, b->data, (b->row * b->col));

    mat_free(a);
    mat_free(b);
}

void test_mat_mul(void)
{
    mat_t* a = mat_alloc(2, 3);
    mat_copy_array(a, (float[]){
        0, 1, 2,
        3, 4, 5
    });

    mat_t* b = mat_alloc(3, 2);
    mat_copy_array(b, (float[]){
        4, 5,
        6, 7,
        8, 9
    });

    mat_t* c = mat_alloc(2, 2);

    TEST_ASSERT_EQUAL_PTR(c, mat_mul(a, b, c));

    float correct[] = {
        22, 25,
        76, 88
    };

    TEST_ASSERT_EQUAL_FLOAT_ARRAY(correct, c->data, (c->row * c->col));

    mat_free(a);
    mat_free(b);
    mat_free(c);
}

void test_mat_trans(void)
{
    mat_t* a = mat_alloc(2, 3);
    mat_copy_array(a, (float[]){
        0, 1, 2,
        3, 4, 5
    });

    mat_t* ta = mat_alloc(3, 2);

    TEST_ASSERT_EQUAL_PTR(ta, mat_trans(a, ta));

    float correct[] = {
        0, 3,
        1, 4,
        2, 5
    };

    TEST_ASSERT_EQUAL_FLOAT_ARRAY(correct, ta->data, (ta->row * ta->col));

    mat_free(a);
    mat_free(ta);
}

int main(void)
{
    UNITY_BEGIN();

    RUN_TEST(test_mat_alloc);
    RUN_TEST(test_mat_alloc_failure);
    RUN_TEST(test_mat_copy_array);
    RUN_TEST(test_mat_copy);
    RUN_TEST(test_mat_copy_failure);
    RUN_TEST(test_mat_clone);
    RUN_TEST(test_mat_add);
    RUN_TEST(test_mat_sub);
    RUN_TEST(test_mat_mul_scalar);
    RUN_TEST(test_mat_mul);
    RUN_TEST(test_mat_trans);

    return UNITY_END();
}