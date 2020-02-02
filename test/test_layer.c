///
/// @file   test_layer.cpp
/// @brief  test of base layer
///

#include "unity.h"

#include "layer/layer.h"

void setUp(void) {}

void tearDown(void) {}

void test_create(void)
{
    layer_t* layer = (layer_t*)layer_create();

    TEST_ASSERT_EQUAL(LAYER_NONE, layer->type);
    TEST_ASSERT_NULL(layer->in);
    TEST_ASSERT_NULL(layer->out);
    TEST_ASSERT_NULL(layer->w);
    TEST_ASSERT_NULL(layer->b);
    TEST_ASSERT_NULL(layer->prev);
    TEST_ASSERT_NULL(layer->next);
    TEST_ASSERT_NULL(layer->forward);

    layer_delete(layer);
}

void test_create_data(void)
{
    layer_t* layer = (layer_t*)layer_create();

    layer_create_input(layer, 1, 3, 480, 640);
    TEST_ASSERT_EQUAL(1, layer->in->n);
    TEST_ASSERT_EQUAL(3, layer->in->c);
    TEST_ASSERT_EQUAL(480, layer->in->h);
    TEST_ASSERT_EQUAL(640, layer->in->w);
    TEST_ASSERT_EQUAL((1 * 3 * 480 * 640), layer->in->elem);

    layer_create_output(layer, 1, 10, 240, 320);
    TEST_ASSERT_EQUAL(1, layer->out->n);
    TEST_ASSERT_EQUAL(10, layer->out->c);
    TEST_ASSERT_EQUAL(240, layer->out->h);
    TEST_ASSERT_EQUAL(320, layer->out->w);
    TEST_ASSERT_EQUAL((1 * 10 * 240 * 320), layer->out->elem);

    layer_create_weight(layer, 10, 3, 5, 5);
    TEST_ASSERT_EQUAL(10, layer->w->n);
    TEST_ASSERT_EQUAL(3, layer->w->c);
    TEST_ASSERT_EQUAL(5, layer->w->h);
    TEST_ASSERT_EQUAL(5, layer->w->w);
    TEST_ASSERT_EQUAL((10 * 3 * 5 * 5), layer->w->elem);

    layer_create_bias(layer, 1, 10, 1, 1);
    TEST_ASSERT_EQUAL(1, layer->b->n);
    TEST_ASSERT_EQUAL(10, layer->b->c);
    TEST_ASSERT_EQUAL(1, layer->b->h);
    TEST_ASSERT_EQUAL(1, layer->b->w);
    TEST_ASSERT_EQUAL((1 * 10 * 1 * 1), layer->b->elem);

    layer_delete(layer);
}

void test_connect(void)
{
    layer_t* layer1 = (layer_t*)layer_create();
    layer_create_output(layer1, 1, 3, 32, 32);

    layer_t* layer2 = (layer_t*)layer_create();
    layer_connect(layer1, layer2);

    TEST_ASSERT_EQUAL(1, layer2->in->n);
    TEST_ASSERT_EQUAL(3, layer2->in->c);
    TEST_ASSERT_EQUAL(32, layer2->in->h);
    TEST_ASSERT_EQUAL(32, layer2->in->w);

    TEST_ASSERT_NULL(layer1->prev);
    TEST_ASSERT_EQUAL(layer2, layer1->next);
    TEST_ASSERT_EQUAL(layer1, layer2->prev);
    TEST_ASSERT_NULL(layer2->next);

    layer_delete(layer1);
    layer_delete(layer2);
}

int main(void)
{
    UNITY_BEGIN();

    RUN_TEST(test_create);
    RUN_TEST(test_create_data);
    RUN_TEST(test_connect);

    return UNITY_END();
}
