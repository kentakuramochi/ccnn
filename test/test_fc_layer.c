///
/// @file   test_fc_layer.c
/// @brief  test of fc layer
///

#include "unity.h"

#include "fc_layer.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_fc_alloc(void)
{
    layer_t* layer = fc_layer(2, 3);
    
    TEST_ASSERT_NOT_NULL(layer);
    TEST_ASSERT_NOT_NULL(layer->w);
    TEST_ASSERT_NOT_NULL(layer->dw);
    TEST_ASSERT_NOT_NULL(layer->b);
    TEST_ASSERT_NOT_NULL(layer->db);
    TEST_ASSERT_NOT_NULL(layer->y);
    TEST_ASSERT_NOT_NULL(layer->forward);

    TEST_ASSERT_EQUAL(layer->w->row, 2);
    TEST_ASSERT_EQUAL(layer->w->col, 3);
    TEST_ASSERT_EQUAL(layer->dw->row, 2);
    TEST_ASSERT_EQUAL(layer->dw->col, 3);
    TEST_ASSERT_EQUAL(layer->b->row, 1);
    TEST_ASSERT_EQUAL(layer->b->col, 3);
    TEST_ASSERT_EQUAL(layer->db->row, 1);
    TEST_ASSERT_EQUAL(layer->db->col, 3);
    TEST_ASSERT_EQUAL(layer->y->row, 1);
    TEST_ASSERT_EQUAL(layer->y->col, 3);

    layer_free(layer);
}

void test_fc_forward(void)
{
    layer_t* layer = fc_layer(2, 3);
    mat_copy_array(layer->w, (float[]){
        0, 1, 2,
        3, 4, 5
    });
    mat_copy_array(layer->b, (float[]){ 0, 1, 2 });

    mat_t* x = mat_alloc(1, 2);
    mat_copy_array(x, (float[]){ 1, 1 });

    fc_forward(layer, x);

    float answer[] = { 3, 6, 9 };

    TEST_ASSERT_EQUAL_FLOAT_ARRAY(answer, layer->y->data, 3);

    layer_free(layer);
}

int main(void)
{
    UNITY_BEGIN();

    RUN_TEST(test_fc_alloc);
    RUN_TEST(test_fc_forward);

    return UNITY_END();
}
