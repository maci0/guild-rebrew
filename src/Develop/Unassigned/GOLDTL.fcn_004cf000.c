#include <math.h>

extern int g_67a370;

char __cdecl d3_GridPointToWorld(int g, int x, int z, float *out);

/* ADDRESS: GOLDTL 0x004cf000 */
float __cdecl gm_GetEntityGridDistance(void *a0, int gridX, int gridZ)
{
    float p[8];
    struct { float z, x; } b;
    char *position;

    d3_GridPointToWorld(*(int *)((char *)g_67a370 + 0xb0), gridX, gridZ, p);
    p[1] = 0.0f;
    position = (char *)*(int *)((char *)*(int *)((char *)a0 + 0x184) + 0x34);
    b.x = *(float *)(position + 0x4c);
    b.z = *(float *)(position + 0x54);
    p[4] = p[0] - b.x;
    return (float)sqrt((p[2] - b.z) * (p[2] - b.z) + p[4] * p[4]);
}
