#include <math.h>

extern int g_67a370;

char __cdecl fcn_0045b920(int g, int x, int z, float *out);

/* ADDRESS: GOLDTL 0x004cf000 */
float __cdecl fcn_004cf000(void *a0, int a1, int a2)
{
    float p[8];
    float x;
    float z;

    fcn_0045b920(*(int *)((char *)g_67a370 + 0xb0), a1, a2, p);
    p[1] = 0.0f;
    x = *(float *)((char *)*(int *)((char *)*(int *)((char *)a0 + 0x184) + 0x34) + 0x4c);
    z = *(float *)((char *)*(int *)((char *)*(int *)((char *)a0 + 0x184) + 0x34) + 0x54);
    return (float)sqrt((p[0] - x) * (p[0] - x) + (p[2] - z) * (p[2] - z));
}
