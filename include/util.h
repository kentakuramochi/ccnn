///
/// @file   util.h
/// @brief  utility functions 
///

#ifndef UTIL_H
#define UTIL_H

#include <math.h>
#include <stdint.h>

///
/// @def    MATH_PI
/// @brief  static pi value
///
#define MATH_PI 3.14159265358979

static uint32_t xorsft_x = 123456789;
static uint32_t xorsft_y = 362436069;
static uint32_t xorsft_z = 521288629;
static uint32_t xorsft_w = 88675123;

///
/// @fn     rand_seed
/// @brief  set seed of random number
/// @param[in]  seed    seed of random number
///
void rand_seed(uint32_t seed)
{
    xorsft_w = seed;
}

///
/// @fn     rand_uint
/// @brief  generate random number by xorshift algorithm (128 bit)
/// @return pseudo random number
///
uint32_t rand_uint(void)
{
    uint32_t t = xorsft_x ^ (xorsft_x << 11);

    xorsft_x = xorsft_y;
    xorsft_y = xorsft_z;
    xorsft_z = xorsft_w;
    xorsft_w ^= (t ^ (t >> 8)) ^ (xorsft_w >> 19);

    return xorsft_w;
}

///
/// @fn     rand_uniform 
/// @brief  generate uniform random numbers
/// @return uniform random numbers [0, 1)
///
float rand_uniform(void)
{
    return  (rand_uint() + 0.5f) / (UINT32_MAX + 1.0f);
}

///
/// @fn     rand_normal
/// @brief  generate normal random numbers
/// @param[in]  mean    mean
/// @param[in]  std     standard deviation
/// @return normal random numbers
/// @note   use a part of box-muller algorithm
///
float rand_normal(float mean, float std)
{
    return mean + std * sqrtf(-2.0f * logf(rand_uniform())) * sinf(2.0f * MATH_PI * rand_uniform());
}

#endif
