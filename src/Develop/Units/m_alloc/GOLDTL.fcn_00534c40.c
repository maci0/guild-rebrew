#include <stdio.h>
#include <string.h>

#include "GOLDTL.fcn_00534c40_gconf.h"
extern int g_7747c4;
extern void *__cdecl m_alloc(unsigned int size, const char *tag);
extern void __cdecl m_FreeTracked(void *p);
extern int __cdecl fcn_00412eb0(int a0, int a1);
extern void __cdecl fcn_00442c00(int a0, int a1);
extern int __cdecl fcn_00442910(int a0, int a1, int a2, int a3);
extern int __cdecl fcn_00471170(int a0, int a1, int a2);
extern void __cdecl fcn_004713b0(int a0, char *a1, char *a2);
extern void __cdecl fcn_00471490(int a0);
extern void __cdecl fcn_00471a30(int a0, int a1);
extern void __cdecl fcn_00436f70(int a0);
extern void __cdecl fcn_004234e0(int a0, char *a1, int a2, int a3, int a4, int a5, int a6);

/* ADDRESS: GOLDTL 0x00534c40 */
int *__cdecl fcn_00534c40(unsigned int a0, int a1, char a2, ...)
{
    int *blk;
    int *v3;
    unsigned int *v2;
    int v4;
    int v5;
    int v7;
    int v11;
    int v12;
    char v8[96];
    char v9[96];
    char *v6;
    unsigned int *v10;
    unsigned int *v1;
    int i;
    int n;
    int arr;
    unsigned int ent;

    v3 = (int *)m_alloc(0x274, (char *)0x6a3180);
    if (v3 == 0)
        return 0;
    v4 = fcn_00412eb0(a0, 1);
    *v3 = v4;
    if (v4 == 0)
    {
        m_FreeTracked(v3);
        return 0;
    }
    if (a1 != 0)
    {
        fcn_00442c00(v4, 0);
        v4 = *v3;
        v3[1] = v4;
        v2 = *(unsigned int **)(v4 + 0x1fc);
        *v3 = fcn_00442910((int)v2, v4 + 0x4c, v4 + 0x84, a1);
    }
    else
        v3[1] = 0;
    v12 = 0;
    *(unsigned char *)(*v3 + 0x215) = *(unsigned char *)(*v3 + 0x215) & 0xf7;
    *(char *)((char *)v3 + 0x271) = a2;
    *(char *)((char *)v3 + 0x270) = 0;
    v3[0x9a] = -1;
    v3[0x9b] = -1;
    v5 = a2;
    if (v5 <= 0)
        goto finish;
    v6 = &a2;
    v10 = (unsigned int *)&v3[0x8a];
    for (;;)
    {
        v1 = (unsigned int *)(v6 + 4);
        v6 = v6 + 4;
        v4 = fcn_00471170(0, 0, *v1);
        *v10 = v4;
        if (v4 == 0)
            break;
        v4 = v12 + 1;
        sprintf(v8, (char *)0x6a3168, v4);
        sprintf(v9, (char *)0x6a314c, v4);
        fcn_004713b0(*v10, v8, v9);
        v11 = 0;
        v7 = *(int *)(*v3 + 0x1cc);
        n = *(int *)(*(int *)(v7 + 0x318) + 0x1e4);
        if (n >= 1)
        {
            arr = *(int *)(v7 + 0x31c);
            for (v11 = 0; v11 < n; v11++)
            {
                ent = *(unsigned int *)(arr + v11 * 4);
                if (strcmpi((char *)ent, v8) != 0)
                {
                    if (strcmpi((char *)ent, v9) == 0)
                        continue;
                    *(unsigned int *)(*v10 * 700 + 0x10383f8) =
                        *(unsigned int *)(ent + 0x50);
                    v7 = *(int *)(*v10 * 700 + 0x10382e8);
                }
                else
                {
                    *(unsigned int *)(*v10 * 700 + 0x10383f4) =
                        *(unsigned int *)(ent + 0x50);
                    v7 = *(int *)(*v10 * 700 + 0x10382e4);
                }
                ent = *(unsigned int *)(*(int *)(*(int *)(*v3 + 0x1cc) + 0x31c) + v11 * 4);
                *(unsigned int *)(ent + 0x50) = *(unsigned int *)(v7 + 0x20);
                v7 = *(int *)(*v3 + 0x1cc);
                arr = *(int *)(v7 + 0x31c);
                n = *(int *)(*(int *)(v7 + 0x318) + 0x1e4);
            }
        }
        fcn_00471490(*v10);
        if (v12 > 2)
            fcn_00471a30(*v10, 0);
        v10 = v10 + 1;
        if (v5 <= v4)
            goto finish;
        v12 = v4;
    }
    m_FreeTracked(v3);
    return 0;
finish:
    if (g_6b7ff9 != 0)
    {
        *(char *)((char *)v3 + 0x272) = g_6b7ff9;
        fcn_00436f70(0);
    }
    fcn_004234e0(g_7747c4, (char *)0x6a313c, 1, 0x3f, 0x7f, 0, 0);
    return v3;
}
