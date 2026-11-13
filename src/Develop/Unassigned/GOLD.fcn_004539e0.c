#include <math.h>

void __cdecl fcn_004518a0(float*);
int __cdecl CompareVector3WithinTolerance(float*, float*, float);

/* ADDRESS: GOLD 0x004539e0 */
float __cdecl fcn_004539e0(const float* a, const float* b)
{
    float first[4];
    float second[4];
    float opposite[4];
    float orientation;

    second[1] = 0.0f;
    first[1] = 0.0f;
    first[0] = a[0];
    first[2] = a[2];
    second[0] = b[0];
    second[2] = b[2];
    fcn_004518a0(first);
    fcn_004518a0(second);
    if (CompareVector3WithinTolerance(first, second, 1.0e-7f))
        return 0.0f;
    opposite[0] = -second[0];
    opposite[1] = -second[1];
    opposite[2] = -second[2];
    if (CompareVector3WithinTolerance(first, opposite, 1.0e-7f))
        return -3.1415927410125732f;
    orientation = *(float*) 0x5ebb94 * (second[2] * first[1] - second[1] * first[2])
        + (*(float*) 0x5ebb98 * (second[0] * first[2] - second[2] * first[0])
        + *(float*) 0x5ebb9c * (second[1] * first[0] - second[0] * first[1]));
    if (orientation > 0.0f)
        return (float) -acos(second[2] * first[2] + second[1] * first[1] + second[0] * first[0]);
    return (float) (acos(second[2] * first[2] + second[1] * first[1] + second[0] * first[0]) - 6.2831854820251465);
}
