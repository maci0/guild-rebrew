#include <string.h>

extern unsigned char g_773d75;
extern float g_66436c;
extern float g_664368;
extern float g_6628d8;

/* SIZE 0x18 */
typedef struct {
    unsigned char type;
    char pad1[3];
    int a;
    int b;
    int c;
    int d;
    float value;
} Msg_49dd90;

extern int __cdecl fcn_00507ab0(int a0);
extern int __cdecl fcn_004a5e60(unsigned short *a0, int a1, int a2, int a3, int a4, float a5, int *a6);
extern int __cdecl gm_ResolveEntityById(void **a0, void **a1, void **a2, int a3);
extern int __cdecl fcn_0050b810(int a0, unsigned char a1);
extern unsigned short __cdecl gm_RandomMod(int a0);
extern int __cdecl fcn_00495400(int a0, int a1, int a2, void *a3, void *a4);
extern int __cdecl fcn_004a4fb0(void *a0, void *a1, char *a2, int a3);
extern float __cdecl fcn_004fc460(float *a0);
extern int __cdecl fcn_0050d170(int a0);

/* ADDRESS: GOLDTL 0x0049dd90 */
int __cdecl ai_StartBuergermeisterKerker(int a0, unsigned short *a1, int a2, Msg_49dd90 *a3, Msg_49dd90 *a4)
{
    char *v10;
    float v15[10];
    Msg_49dd90 v11;
    Msg_49dd90 v12;
    int v9;
    int v13;
    int v14;
    int v6;
    int v7;
    int v19;
    int rv;
    char *v6p;

    fcn_00507ab0(1);
    if (a2 != 0 || *(unsigned char *)((char *)a1 + 0x166) != 0xf || a3->type != 0 ||
        (a0 != 0 && *((char *)a1 + 0x130) != 7 && *((char *)a1 + 0x130) != 6))
        return 0;
    if (fcn_004a5e60(a1, 2, 0x40, 0, 0, 100.0f, &v9) == 0)
        return 0;
    gm_ResolveEntityById((void **)&v10, 0, 0, v9);
    if (v10 == 0)
        return 0;
    v6p = (char *)fcn_00507ab0(1);
    if (v6p == 0)
        return 0;
    v7 = fcn_0050b810(*(int *)(v6p + 0x14), g_773d75);
    if ((v10[0x5a] & 4) == 0)
    {
        if ((int)v10[0x5c] < (int)(gm_RandomMod(0x40) + 0x25))
        {
            v12.type = 4;
            v12.a = *(int *)(v10 + 1);
            v12.b = 1;
            if (v10[0x5c] >= '!')
                v12.d = ((v10[0x5c] >= 'B') - 1 & 0x14) + 10;
            else
                v12.d = 0x32;
            v11.type = 1;
            v11.a = *(int *)(v6p + 2);
            v11.b = v7;
            v11.d = 1;
            v6 = fcn_00495400(0xf, *a1, 0, &v12, &v11);
            if (v6 != 0)
                goto label_49df97;
        }
    }
    v6 = fcn_004a4fb0(&v14, &v13, v10, 0);
    if (v6 != 0)
    {
        v12.type = 2;
        v12.a = v14;
        v12.b = 1;
        if (v13 != -1)
            v11.type = 1;
        else
        {
            v11.type = 4;
            v13 = *(int *)(v10 + 1);
        }
        v11.a = v13;
        v11.b = 1;
        v11.value = 0.44f;
        v6 = fcn_00495400(0x15, *a1, 1, &v12, &v11);
        if (v6 != 0)
        {
label_49df97:
            memcpy(a3, &v12, sizeof(v12));
            memcpy(a4, &v11, sizeof(v11));
            return v6;
        }
    }
    if ((v10[0x5a] & 0x41) == 0)
    {
        fcn_004fc460(v15);
        if (*v10 == 0x11)
        {
            v19 = 0x12;
            rv = gm_RandomMod(0x200);
            if ((float)rv + v15[6] < g_66436c)
                return 0;
        }
        else
        {
            if (*v10 != 0x12)
                return 0;
            v19 = 0x13;
            rv = gm_RandomMod(0x400);
            if ((float)rv + v15[6] < g_664368)
                return 0;
        }
        if ((float)fcn_0050d170(v19) * g_6628d8 <= (float)v7)
        {
            a3->type = 4;
            a3->a = v19;
            a3->b = 1;
            a3->d = 0;
            a4->type = 4;
            a4->a = *(int *)(v10 + 1);
            a4->b = 1;
            a4->d = 0;
            return 0x3c;
        }
    }
    return 0;
}
