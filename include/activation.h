#ifndef ACTIVATION_H
#define ACTIVATION_H

#include <math.h>
#include <float.h>

static float sigmoid(const float x)
{
    return 1.0 / (1 + expf(-x));
}

#endif
