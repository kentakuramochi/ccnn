///
/// @file   test_mat.c
/// @brief  test of ndmat
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

    TEST_ASSERT_NOT_NULL(mat_copy_array(mat, array));

    for (int i = 0; i < (mat->row * mat->col); i++) {
        TEST_ASSERT_EQUAL(array[i], mat->data[i]);
    }
}

int main(void)
{
    UNITY_BEGIN();

    RUN_TEST(test_mat_alloc);
    RUN_TEST(test_mat_alloc_failure);
    RUN_TEST(test_mat_copy_array);

    return UNITY_END();
}