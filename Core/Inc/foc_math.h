#ifndef FOC_MATH_H
#define FOC_MATH_H

#include <math.h>

#define PI 3.1415926535f
#define _2PI 6.283185307f

float Normalize_Angle(float angle);
void RevPark_Transform(float vd, float vq, float theta, float *valpha, float *vbeta);

#endif
