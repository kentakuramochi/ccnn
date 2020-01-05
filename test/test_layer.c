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

void test_setdatashape(void)
{
    layer* l = (layer*)create_layer();

    set_input_shape(l, 1, 3, 480, 640);
    TEST_ASSERT_EQUAL(1, l->in->n);
    TEST_ASSERT_EQUAL(3, l->in->c);
    TEST_ASSERT_EQUAL(480, l->in->h);
    TEST_ASSERT_EQUAL(640, l->in->w);
    TEST_ASSERT_EQUAL((1 * 3 * 480 * 640), l->in->elem);

    set_output_shape(l, 1, 10, 240, 320);
    TEST_ASSERT_EQUAL(1, l->out->n);
    TEST_ASSERT_EQUAL(10, l->out->c);
    TEST_ASSERT_EQUAL(240, l->out->h);
    TEST_ASSERT_EQUAL(320, l->out->w);
    TEST_ASSERT_EQUAL((1 * 10 * 240 * 320), l->out->elem);

    delete_layer(l);
}

int main(void)
{
    UNITY_BEGIN();

    RUN_TEST(test_createbaselayer);
    RUN_TEST(test_setdatashape);

    return UNITY_END();
}

