#include "Develop/DieGildeAddOn/game/game_data.h"
extern float g_662d40[3];
extern volatile int g_6b7fac;

extern int __cdecl gm_ResolveEntityById(void **a0, int a1, int a2, int a3);
extern void __cdecl d3_SelectSceneContext(int a0, int a1);
extern void __cdecl d3_TransformPoint(int a0, int a1, float *a2);
extern float __cdecl d3_WrapYawDelta(float *a0, float *a1);
extern int __cdecl d3_CreateSceneModelObject(int a0, float *a1, float *a2, char *a3);
extern void __cdecl d3_ApplyObjectAnimation(int a0, char *a1, int a2);

typedef struct
{
    float x;
    float y;
    float z;
    float w;
} VEC;

/* ADDRESS: GOLDTL 0x00558370 */
int __cdecl he_SpawnSensenmann(int action)
{
    int savedContext;
    int v3;
    int v5;
    int v6;
    void *out;
    int v1;
    VEC cur;
    VEC pos;
    VEC rot;
    VEC dir;

    savedContext = d3_CurrentContextIndex;
    d3_SelectSceneContext(0, 1);
    v3 = action;
    gm_ResolveEntityById(&out, 0, 0, *(int *)(v3 + 0xb0));
    v5 = (int)out;
    if (v5 == 0)
        goto fail;
    v1 = *(int *)(v5 + 0x61);
    if (!v1 || !(v1 = *(int *)(v1 + 0x1cc)) || !*(int *)(v1 + 0x318))
        goto fail;

    {
        v6 = v5;
        gm_ResolveEntityById(&out, 0, 0, *(int *)(v3 + 0xb4));
        v5 = (int)out;
        if (v5 == 0)
            goto fail;
        v1 = *(int *)(v5 + 0x61);
        if (!v1 || !(v1 = *(int *)(v1 + 0x1cc)) || !*(int *)(v1 + 0x318))
            goto fail;

        if (*(int *)(v3 + 0xc4) == 0)
        {
            d3_TransformPoint(*(int *)(v6 + 0x61), *(int *)(v6 + 0x61) + 0x4c,
                &cur.x);
            cur.y = cur.y + *(float *)(*(int *)(*(int *)(*(int *)(v6 + 0x61)
                + 0x1cc) + 0x318) + 0x1d4) + 80.0f;
            d3_TransformPoint(*(int *)(v5 + 0x61), *(int *)(v5 + 0x61) + 0x4c,
                &pos.x);
            pos.y = pos.y + *(float *)(*(int *)(*(int *)(*(int *)(v5 + 0x61)
                + 0x1cc) + 0x318) + 0x1d4) + 80.0f;
            rot.x = 0;
            rot.y = 0;
            rot.z = 0;
            dir.x = pos.x - cur.x;
            dir.y = pos.y - cur.y;
            dir.z = pos.z - cur.z;
            rot.y = d3_WrapYawDelta(g_662d40, &dir.x);
        }
        else
        {
            rot.x = *(float *)(v3 + 0xe0);
            rot.y = *(float *)(v3 + 0xe4);
            rot.z = *(float *)(v3 + 0xe8);
            cur.x = *(float *)(v3 + 0xd0);
            cur.y = *(float *)(v3 + 0xd4);
            cur.z = *(float *)(v3 + 0xd8);
            d3_TransformPoint(*(int *)(v5 + 0x61), *(int *)(v5 + 0x61) + 0x4c,
                &pos.x);
            pos.y = pos.y + *(float *)(*(int *)(*(int *)(*(int *)(v5 + 0x61)
                + 0x1cc) + 0x318) + 0x1d4) + 80.0f;
            dir.x = pos.x - cur.x;
            dir.y = pos.y - cur.y;
            dir.z = pos.z - cur.z;
        }
        v5 = d3_CreateSceneModelObject(0, &cur.x, &rot.x, (char *)0x6a5fc4);
        *(int *)(v3 + 0xc8) = v5;
        if (v5 == 0)
            goto fail;
        *(int *)(v3 + 0xc4) = 1;
        *(float *)(v3 + 0xe0) = *(float *)(v5 + 0x84);
        *(float *)(v3 + 0xe4) = *(float *)(v5 + 0x88);
        *(float *)(v3 + 0xe8) = *(float *)(v5 + 0x8c);
        *(float *)(v3 + 0xd0) = *(float *)(v5 + 0x4c);
        *(float *)(v3 + 0xd4) = *(float *)(v5 + 0x50);
        *(float *)(v3 + 0xd8) = *(float *)(v5 + 0x54);
        *(unsigned char *)(v5 + 0x214) = *(unsigned char *)(v5 + 0x214) & 0x7f;
        *(unsigned char *)(*(int *)(v3 + 0xc8) + 0x216) = *(unsigned char *)(*(int *)(v3 + 0xc8) + 0x216) | 3;
        *(unsigned char *)(*(int *)(v3 + 0xc8) + 0x217) = *(unsigned char *)(*(int *)(v3 + 0xc8) + 0x217) & 0xfe;
        d3_ApplyObjectAnimation(*(int *)(v3 + 0xc8), (char *)0x6a5fb4, 1);
        *(int *)(v3 + 0xec) = g_6b7fac;
        d3_SelectSceneContext(savedContext, 1);
        return 1;
    }
fail:
    d3_SelectSceneContext(savedContext, 1);
    return 0;
}
