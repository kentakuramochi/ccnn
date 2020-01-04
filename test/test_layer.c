///
/// @file   test_layer.cpp
/// @brief  test of base layer
///

#include "unity.h"

#include "layer/layer.h"

void setUp(void) {}

void tearDown(void) {}

void test_createbaselayer(void)
{
    layer* l = (layer*)create_layer();

    TEST_ASSERT_EQUAL(LAYER_NONE, l->type);

    TEST_ASSERT_NULL(l->in);
    TEST_ASSERT_NULL(l->out);
    TEST_ASSERT_NULL(l->w);
    TEST_ASSERT_NULL(l->b);
    TEST_ASSERT_NULL(l->prev);
    TEST_ASSERT_NULL(l->next);
    TEST_ASSERT_NULL(l->forward);

    delete_layer(l);
}

int main(void)
{
    UNITY_BEGIN();

    RUN_TEST(test_createbaselayer);

    return UNITY_END();
}

