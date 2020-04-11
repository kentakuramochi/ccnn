///
/// @file   test_util.c
/// @brief  test of utility functions
///

#include "unity.h"

#include "util.h"

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

int main(void)
{
    UNITY_BEGIN();

    RUN_TEST(test_rand_uint);

    return UNITY_END();
}
