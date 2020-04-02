///
/// @file   util.h
/// @brief  utility functions 
///

#ifndef UTIL_H
#define UTIL_H

#include <stdint.h>

static uint32_t xorsft_x = 123456789;
static uint32_t xorsft_y = 362436069;
static uint32_t xorsft_z = 521288629;
static uint32_t xorsft_w = 88675123;

///
/// @fn     random_seed
/// @brief  set seed of random number
///
void random_seed(uint32_t seed)
{
    xorsft_w = seed;
}

///
/// @fn     xorshift_128
/// @brief  generate random number by xorshift algorithm
/// @return pseudo random number
///
uint32_t xorshift_128(void)
{
    uint32_t t = xorsft_x ^ (xorsft_x << 11);

    xorsft_x = xorsft_y;
    xorsft_y = xorsft_z;
    xorsft_z = xorsft_w;
    xorsft_w ^= (t ^ (t >> 8)) ^ (xorsft_w >> 19);

    return xorsft_w;
}

///
/// @fn     uniform 
/// @brief  generate uniform
/// @return pseudo random number [0, 1)
///
float uniform(void)
{
    return  xorshift_128() / UINT32_MAX;
}

#endif
