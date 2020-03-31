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
/// @fn     xorshift
/// @brief  xorshift algorithm
/// @return pseudo random value
///
uint32_t xorshift(void)
{
    uint32_t t = xorsft_x ^ (xorsft_x << 11);

    xorsft_x = xorsft_y;
    xorsft_y = xorsft_z;
    xorsft_z = xorsft_w;
    xorsft_w ^= t ^ (t >> 8) ^ (xorsft_w >> 19);

    return xorsft_w;
}

#endif
