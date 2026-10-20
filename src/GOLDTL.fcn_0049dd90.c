#include <string.h>

extern int g_773d75;
extern float g_66436c;
extern float g_664368;
extern float g_6628d8;

extern int __cdecl fcn_00507ab0(int a0);
extern int __cdecl fcn_004a5e60(unsigned short *a0, int a1, int a2, int a3, int a4, float a5, int *a6);
extern int __cdecl gm_ResolveEntityById(void **a0, void **a1, void **a2, int a3);
extern int __cdecl fcn_0050b810(int a0, unsigned char a1);
extern int __cdecl fcn_0042e410(int a0);
extern int __cdecl fcn_00495400(int a0, int a1, int a2, void *a3, void *a4);
extern int __cdecl fcn_004a4fb0(void *a0, void *a1, char *a2, int a3);
extern void __cdecl fcn_004fc460(void *a0);
extern int __cdecl fcn_0050d170(int a0);

/* ADDRESS: GOLDTL 0x0049dd90 */
int __cdecl fcn_0049dd90(int a0, unsigned short *a1, int a2, char *a3, int *a4)
{
    char *v10;
    char v15[0x1c];
    unsigned int v11[6];
    unsigned int v12[6];
    int v9;
    int v13;
    int v14;
    int v6;
    int v7;
    int v8;
    int v19;
    int v21;
    int v5;
    float *v24;
    char *v1;
    char *v16;

    fcn_00507ab0(1);
    if (a2 != 0 || *(char *)((char *)a1 + 0x166) != 0xf || *a3 != 0 ||
        (a0 != 0 && *(char *)((char *)a1 + 0x130) != 7 && *(char *)((char *)a1 + 0x130) != 6))
        return 0;
    v6 = fcn_004a5e60(a1, 2, 0x40, 0, 0, 100.0f, &v9);
    if (v6 == 0)
        return 0;
    gm_ResolveEntityById((void **)&v10, 0, 0, v9);
    if (v10 == 0)
        return 0;
    v6 = fcn_00507ab0(1);
    if (v6 == 0)
        return 0;
    v7 = fcn_0050b810(*(int *)(v6 + 0x14), (unsigned char)g_773d75);
    v16 = a1;
    if ((v10[0x5a] & 4) == 0)
    {
        v1 = v10 + 0x5c;
        v8 = fcn_0042e410(0x40);
        if ((int)*v1 < (int)((v8 & 0xffff) + 0x25))
        {
            v12[0] = 4;
            v12[1] = *(unsigned int *)(v10 + 1);
            v12[2] = 1;
            v5 = *v1;
            if (v5 >= '!')
                v21 = ((v5 >= 'B') - 1 & 0x14) + 10;
            else
                v21 = 0x32;
            v11[0] = 1;
            v11[1] = *(int *)(v6 + 2);
            v11[2] = v7;
            v6 = fcn_00495400(0xf, *a1, 0, v12, v11);
            if (v6 != 0)
                goto label_49df97;
        }
        v16 = a1;
    }
    v6 = fcn_004a4fb0(&v14, &v13, v10, 0);
    if (v6 != 0)
    {
        v12[0] = 2;
        v12[1] = v14;
        v12[2] = 1;
        if (v13 != -1)
            v11[0] = 1;
        else
        {
            v11[0] = 4;
            v13 = *(int *)(v10 + 1);
        }
        v11[2] = 1;
        v11[1] = v13;
        v6 = fcn_00495400(0x15, *v16, 1, v12, v11);
        if (v6 != 0)
        {
label_49df97:
            memcpy(a3, v12, 24);
            memcpy(a4, v11, 24);
            return v6;
        }
    }
    if ((v10[0x5a] & 0x41) == 0)
    {
        fcn_004fc460(v15);
        v24 = (float *)(v15 + 0x18);
        if (*v10 != 0x11)
        {
            if (*v10 != 0x12)
                return 0;
            v19 = 0x13;
            a1 = (unsigned short)(fcn_0042e410(0x400) & 0xffff);
            if ((float)(int)a1 + *v24 < g_664368)
                return 0;
        }
        else
        {
            v19 = 0x12;
            a1 = (unsigned short)(fcn_0042e410(0x200) & 0xffff);
            if ((float)(int)a1 + *v24 < g_66436c)
                return 0;
        }
        if ((float)fcn_0050d170(v19) * g_6628d8 <= (float)a2)
        {
            *a3 = 4;
            *(int *)(a3 + 4) = v19;
            *(int *)(a3 + 8) = 1;
            *(int *)(a3 + 0x10) = 0;
            *a4 = 4;
            *(int *)(a4 + 1) = *(int *)(v10 + 1);
            *(int *)(a4 + 2) = 1;
            *(int *)(a4 + 4) = 0;
            return 0x3c;
        }
    }
    return 0;
}
