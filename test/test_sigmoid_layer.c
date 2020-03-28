///
/// @file   test_sigmoid_layer.c
/// @brief  test of sigmoid layer
///

#include "unity.h"

#include "sigmoid_layer.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_sigmoid_alloc(void)
{
    layer_t* layer = sigmoid_layer(3);
    
    TEST_ASSERT_NOT_NULL(layer);
    TEST_ASSERT_NULL(layer->w);
    TEST_ASSERT_NULL(layer->b);
    TEST_ASSERT_NOT_NULL(layer->y);
    TEST_ASSERT_NOT_NULL(layer->forward);

    TEST_ASSERT_EQUAL(layer->y->row, 1);
    TEST_ASSERT_EQUAL(layer->y->col, 3);

    layer_free(layer);
}

void test_sigmoid_forward(void)
{
    layer_t* layer = sigmoid_layer(3);

    mat_t* x = mat_alloc(1, 3);
    mat_copy_array(x, (float[]){ 1, 0, -1 });

    layer->forward(layer, x);

    float answer[] = { 0.7310585, 0.5, 0.2689414 };

    for (int i = 0; i < 3; i++) {
        TEST_ASSERT_EQUAL_FLOAT(answer[i], layer->y->data[i]);
    }

    layer_free(layer);
}

int main(void)
{
    UNITY_BEGIN();

    RUN_TEST(test_sigmoid_alloc);
    RUN_TEST(test_sigmoid_forward);

    return UNITY_END();
}
