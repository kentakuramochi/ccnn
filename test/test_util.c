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

void test_xorshift(void)
{
    random_seed(0);

    uint32_t x1 = xorshift_128();
    uint32_t x2 = xorshift_128();

    TEST_ASSERT_NOT_EQUAL(x1, x2);
}

int main(void)
{
    UNITY_BEGIN();

    RUN_TEST(test_xorshift);

    return UNITY_END();
}
