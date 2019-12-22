///
/// @file   test_ndmat.cpp
/// @brief  test of ndmat
///

#include "gtest/gtest.h"

extern "C"
{
    #include "ndmat.h"
}

TEST(TestNdmat, CreateValidShape)
{
    ndmat* mat = create_ndmat(3, 3, 4, 4);

    EXPECT_EQ(3, mat->dim);
    EXPECT_EQ((3 * 4 * 4), mat->elem);
    EXPECT_EQ(3, mat->shape[0]);
    EXPECT_EQ(4, mat->shape[1]);
    EXPECT_EQ(4, mat->shape[2]);
    EXPECT_EQ(1, mat->n);
    EXPECT_EQ(3, mat->c);
    EXPECT_EQ(4, mat->h);
    EXPECT_EQ(4, mat->w);

    delete_ndmat(mat);
}

TEST(TestNdmat, SetValidData)
{
    ndmat* mat = create_ndmat(3, 3, 4, 4);

    float array[] = {
        0, 0, 0, 0,
        0, 0, 0, 0,
        0, 0, 0, 0,
        0, 0, 0, 0,
        1, 1, 1, 1,
        1, 1, 1, 1,
        1, 1, 1, 1,
        1, 1, 1, 1,
        2, 2, 2, 2,
        2, 2, 2, 2,
        2, 2, 2, 2,
        2, 2, 2, 2
    };

    set_fromarray(mat, array, (sizeof(array) / sizeof(float)));

    for (int i = 0; i < mat->elem; i++) {
        EXPECT_EQ(array[i], mat->data[i]);
    }

    delete_ndmat(mat);
}
