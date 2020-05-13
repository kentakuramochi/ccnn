///
/// @file   test_layer.c
/// @brief  test of basic layer
///

#include "unity.h"

#include "layer.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_layer_alloc(void)
{
    layer_t* layer = layer_alloc();

    TEST_ASSERT_NOT_NULL(layer);

    TEST_ASSERT_NULL(layer->x);
    TEST_ASSERT_NULL(layer->y);
    TEST_ASSERT_NULL(layer->w);
    TEST_ASSERT_NULL(layer->dw);
    TEST_ASSERT_NULL(layer->b);
    TEST_ASSERT_NULL(layer->db);
    TEST_ASSERT_NULL(layer->prev);
    TEST_ASSERT_NULL(layer->next);
    TEST_ASSERT_NULL(layer->forward);
    TEST_ASSERT_NULL(layer->backward);

    layer_free(layer);
}

int main(void)
{
    UNITY_BEGIN();

    RUN_TEST(test_layer_alloc);

    return UNITY_END();
}
