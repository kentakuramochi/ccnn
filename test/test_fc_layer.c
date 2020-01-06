///
/// @file   test_fc_layer.cpp
/// @brief  test of fc layer
///

#include "unity.h"

#include "layer/fc_layer.h"

void setUp(void) {}

void tearDown(void) {}

void test_createfclayer(void)
{
    layer* l = fc(NULL, 10);

    TEST_ASSERT_EQUAL(LAYER_FC, l->type);
    TEST_ASSERT_NULL(l->in);
    TEST_ASSERT_NULL(l->out);
    TEST_ASSERT_NULL(l->w);
    TEST_ASSERT_NULL(l->b);
    TEST_ASSERT_NULL(l->prev);
    TEST_ASSERT_NULL(l->next);

    delete_layer(l);
}

int main(void)
{
    UNITY_BEGIN();

    RUN_TEST(test_createfclayer);

    return UNITY_END();
}

