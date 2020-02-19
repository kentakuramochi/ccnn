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

    TEST_ASSERT_EQUAL(2, mat->row);
    TEST_ASSERT_EQUAL(3, mat->col);

    mat_free(mat);
}

void test_mat_alloc_failure(void)
{
    mat_t* mat;
    mat = mat_alloc(0, 3);
    TEST_ASSERT_EQUAL_PTR(NULL, mat);

    mat = mat_alloc(2, 0);
    TEST_ASSERT_EQUAL_PTR(NULL, mat);

    mat = mat_alloc(-1, 3);
    TEST_ASSERT_EQUAL_PTR(NULL, mat);
 
    mat = mat_alloc(2, -1);
    TEST_ASSERT_EQUAL_PTR(NULL, mat);

    mat_free(mat);
}

int main(void)
{
    UNITY_BEGIN();

    RUN_TEST(test_mat_alloc);
    RUN_TEST(test_mat_alloc_failure);

    return UNITY_END();
}