///
/// @file   test_random.c
/// @brief  test of random numbers
///

#include "unity.h"

#include "random.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_rand_uint(void)
{
    rand_seed(0);

    uint32_t x1 = rand_uint();
    uint32_t x2 = rand_uint();

    TEST_ASSERT_NOT_EQUAL(x1, x2);
}

void test_rand_uniform(void)
{
    rand_seed(0);

    float x1 = rand_uniform();
    float x2 = rand_uniform();

    TEST_ASSERT_NOT_EQUAL(x1, x2);
}

void test_rand_normal(void)
{
    rand_seed(0);

    float x1 = rand_normal(0, 0.1);
    float x2 = rand_normal(0, 0.1);

    TEST_ASSERT_NOT_EQUAL(x1, x2);
}

int main(void)
{
    UNITY_BEGIN();

    RUN_TEST(test_rand_uint);
    RUN_TEST(test_rand_uniform);
    RUN_TEST(test_rand_normal);

    return UNITY_END();
}
