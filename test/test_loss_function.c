///
/// @file   test_loss_function.c
/// @brief  test of loss function
///

#include "unity.h"

#include "loss_function.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_mse(void)
{
    mat_t* y = mat_alloc(1, 5);
    mat_t* t = mat_alloc(1, 5);

    mat_copy_array(y, (float[]){ 1, 2, 3, 4, 5 });
    mat_copy_array(t, (float[]){ 1, 2, 3, 4, 4 });

    TEST_ASSERT_EQUAL_FLOAT(0.1, loss_mse(y, t));

    mat_free(y);
    mat_free(t);
}

void test_cross_entropy(void)
{
    mat_t* y = mat_alloc(1, 3);
    mat_t* t = mat_alloc(1, 3);

    mat_copy_array(y, (float[]){ 0.3, 0.3, 0.4 });
    mat_copy_array(t, (float[]){ 0, 0, 1 });

    TEST_ASSERT_EQUAL_FLOAT(0.91629048, loss_cross_entropy(y, t));

    mat_free(y);
    mat_free(t);
}

int main(void)
{
    UNITY_BEGIN();

    RUN_TEST(test_mse);
    RUN_TEST(test_cross_entropy);

    return UNITY_END();
}
