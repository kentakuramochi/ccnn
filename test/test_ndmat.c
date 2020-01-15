///
/// @file   test_ndmat.cpp
/// @brief  test of ndmat
///

#include "unity.h"

#include "ndmat.h"

void setUp(void) {}

void tearDown(void) {}

void test_create(void)
{
    ndmat* mat = ndmat_create(1, 3, 4, 4);

    TEST_ASSERT_EQUAL(4, mat->dim);
    TEST_ASSERT_EQUAL((3 * 4 * 4), mat->elem);
    TEST_ASSERT_EQUAL(1, mat->shape[0]);
    TEST_ASSERT_EQUAL(3, mat->shape[1]);
    TEST_ASSERT_EQUAL(4, mat->shape[2]);
    TEST_ASSERT_EQUAL(4, mat->shape[3]);
    TEST_ASSERT_EQUAL(1, mat->n);
    TEST_ASSERT_EQUAL(3, mat->c);
    TEST_ASSERT_EQUAL(4, mat->h);
    TEST_ASSERT_EQUAL(4, mat->w);

    ndmat_delete(mat);
}

void test_set_array(void)
{
    ndmat* mat = ndmat_create(1, 3, 4, 4);

    float array[] = {
        0, 0, 0, 0,
        0, 0, 0, 0,
        0, 0, 0, 0,
        0, 0, 0, 0,
        1, 1, 1, 1,
        1, 1, 1, 1,
        1, 1, 1, 1,
        1, 1, 1, 1,
        2, 2, 2, 2,
        2, 2, 2, 2,
        2, 2, 2, 2,
        2, 2, 2, 2
    };

    ndmat_set_array(mat, array, (sizeof(array) / sizeof(float)));

    for (int i = 0; i < mat->elem; i++) {
        TEST_ASSERT_EQUAL(array[i], mat->data[i]);
    }

    ndmat_delete(mat);
}

void test_fill(void)
{
    ndmat* mat = ndmat_create(1, 3, 4, 4);

    ndmat_fill(mat, 1);

    for (int i = 0; i < mat->elem; i++) {
        TEST_ASSERT_EQUAL(1, mat->data[i]);
    }

    ndmat_delete(mat);
}

int main(void)
{
    UNITY_BEGIN();

    RUN_TEST(test_create);
    RUN_TEST(test_set_array);
    RUN_TEST(test_fill);

    return UNITY_END();
}

