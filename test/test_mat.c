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
    TEST_ASSERT_NOT_NULL(mat);

    for (int i = 0; i < (mat->row * mat->col); i++) {
        TEST_ASSERT_EQUAL(array[i], mat->data[i]);
    }

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
    for (int i = 0; i < (mat2->row * mat2->col); i++) {
        mat2->data[i] = 1;
    }

    TEST_ASSERT_EQUAL_PTR(mat2, mat_copy(mat2, mat));
    TEST_ASSERT_NOT_NULL(mat2);

    for (int i = 0; i < (mat2->row * mat2->col); i++) {
        TEST_ASSERT_EQUAL(array[i], mat2->data[i]);
    }

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

    mat_t* mat2 = mat_alloc(3, 2);
    for (int i = 0; i < (mat2->row * mat2->col); i++) {
        mat2->data[i] = 1;
    }

    TEST_ASSERT_NULL(mat_copy(mat2, mat));
    TEST_ASSERT_NOT_NULL(mat2);

    for (int i = 0; i < (mat2->row * mat2->col); i++) {
        TEST_ASSERT_EQUAL(1, mat2->data[i]);
    }

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

    for (int i = 0; i < (mat2->row * mat2->col); i++) {
        TEST_ASSERT_EQUAL(array[i], mat2->data[i]);
    }

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

    for (int i = 0; i < (2 * 3); i++) {
        TEST_ASSERT_EQUAL(correct[i], c->data[i]);
    }

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

    for (int i = 0; i < (2 * 3); i++) {
        TEST_ASSERT_EQUAL(correct[i], c->data[i]);
    }

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

    for (int i = 0; i < (2 * 3); i++) {
        TEST_ASSERT_EQUAL(correct[i], b->data[i]);
    }

    mat_free(a);
    mat_free(b);
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

    return UNITY_END();
}