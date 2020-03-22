///
/// @file   test_activation.c
/// @brief  test of activation function
///

#include "unity.h"

#include "activation.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_sigmoid(void)
{
    TEST_ASSERT_EQUAL_FLOAT(0.5, sigmoid(0));

    TEST_ASSERT_EQUAL_FLOAT(0.7310585, sigmoid(1));

    TEST_ASSERT_EQUAL_FLOAT(0.2689414, sigmoid(-1));
}

int main(void)
{
    UNITY_BEGIN();

    RUN_TEST(test_sigmoid);
    //RUN_TEST();

    return UNITY_END();
}
