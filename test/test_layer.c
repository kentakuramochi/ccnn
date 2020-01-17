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
    layer* l = (layer*)layer_create();

    TEST_ASSERT_EQUAL(LAYER_NONE, l->type);
    TEST_ASSERT_NULL(l->in);
    TEST_ASSERT_NULL(l->out);
    TEST_ASSERT_NULL(l->w);
    TEST_ASSERT_NULL(l->b);
    TEST_ASSERT_NULL(l->prev);
    TEST_ASSERT_NULL(l->next);
    TEST_ASSERT_NULL(l->forward);

    layer_delete(l);
}

void test_create_data(void)
{
    layer* l = (layer*)layer_create();

    layer_create_input(l, 1, 3, 480, 640);
    TEST_ASSERT_EQUAL(1, l->in->n);
    TEST_ASSERT_EQUAL(3, l->in->c);
    TEST_ASSERT_EQUAL(480, l->in->h);
    TEST_ASSERT_EQUAL(640, l->in->w);
    TEST_ASSERT_EQUAL((1 * 3 * 480 * 640), l->in->elem);

    layer_create_output(l, 1, 10, 240, 320);
    TEST_ASSERT_EQUAL(1, l->out->n);
    TEST_ASSERT_EQUAL(10, l->out->c);
    TEST_ASSERT_EQUAL(240, l->out->h);
    TEST_ASSERT_EQUAL(320, l->out->w);
    TEST_ASSERT_EQUAL((1 * 10 * 240 * 320), l->out->elem);

    layer_create_weight(l, 10, 3, 5, 5);
    TEST_ASSERT_EQUAL(10, l->w->n);
    TEST_ASSERT_EQUAL(3, l->w->c);
    TEST_ASSERT_EQUAL(5, l->w->h);
    TEST_ASSERT_EQUAL(5, l->w->w);
    TEST_ASSERT_EQUAL((10 * 3 * 5 * 5), l->w->elem);

    layer_create_bias(l, 1, 10, 1, 1);
    TEST_ASSERT_EQUAL(1, l->b->n);
    TEST_ASSERT_EQUAL(10, l->b->c);
    TEST_ASSERT_EQUAL(1, l->b->h);
    TEST_ASSERT_EQUAL(1, l->b->w);
    TEST_ASSERT_EQUAL((1 * 10 * 1 * 1), l->b->elem);

    layer_delete(l);
}

void test_connect(void)
{
    layer* l1 = (layer*)layer_create();
    layer_create_output(l1, 1, 3, 32, 32);

    layer* l2 = (layer*)layer_create();
    layer_connect(l1, l2);

    TEST_ASSERT_EQUAL(1, l2->in->n);
    TEST_ASSERT_EQUAL(3, l2->in->c);
    TEST_ASSERT_EQUAL(32, l2->in->h);
    TEST_ASSERT_EQUAL(32, l2->in->w);

    TEST_ASSERT_NULL(l1->prev);
    TEST_ASSERT_EQUAL(l2, l1->next);
    TEST_ASSERT_EQUAL(l1, l2->prev);
    TEST_ASSERT_NULL(l2->next);
}

int main(void)
{
    UNITY_BEGIN();

    RUN_TEST(test_create);
    RUN_TEST(test_create_data);

    return UNITY_END();
}
