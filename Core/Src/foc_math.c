#include "foc_math.h"

float Normalize_Angle(float angle) {
    while (angle >= _2PI) angle -= _2PI;
    while (angle < 0.0f) angle += _2PI;
    return angle;
}

void RevPark_Transform(float vd, float vq, float theta, float *valpha, float *vbeta) {
    float s = sinf(theta);
    float c = cosf(theta);
    *valpha = vd * c - vq * s;
    *vbeta  = vd * s + vq * c;
}