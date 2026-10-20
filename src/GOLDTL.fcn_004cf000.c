#include <math.h>

extern int g_67a370;

char __cdecl fcn_0045b920(int g, int x, int z, float *out);

/* ADDRESS: GOLDTL 0x004cf000 */
float __cdecl fcn_004cf000(void *a0, int a1, int a2)
{
    float p[8];
    int v;
    int w;
    float x;
    float z;
    float sum;

    fcn_0045b920(*(int *)((char *)g_67a370 + 0xb0), a1, a2, p);
    p[1] = 0.0f;
    v = *(int *)((char *)a0 + 0x184);
    w = *(int *)((char *)v + 0x34);
    x = *(float *)((char *)w + 0x4c);
    z = *(float *)((char *)w + 0x54);
    sum = (p[0] - x) * (p[0] - x);
    sum = sum + (p[2] - z) * (p[2] - z);
    return (float)sqrt(sum);
}
