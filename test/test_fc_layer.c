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
    layer_t* layer = fc(NULL, 10);

    TEST_ASSERT_EQUAL(LAYER_FC, layer->type);
    TEST_ASSERT_NULL(layer->in);
    TEST_ASSERT_NULL(layer->out);
    TEST_ASSERT_NULL(layer->w);
    TEST_ASSERT_NULL(layer->b);
    TEST_ASSERT_NULL(layer->prev);
    TEST_ASSERT_NULL(layer->next);

    layer_delete(layer);
}

void test_forwardfclayer(void)
{
    layer_t* layer = fc(NULL, 10);
    layer_create_input(layer, 1, 10, 3, 3);

    layer_delete(layer);
}

int main(void)
{
    UNITY_BEGIN();

    RUN_TEST(test_createfclayer);

    return UNITY_END();
}

