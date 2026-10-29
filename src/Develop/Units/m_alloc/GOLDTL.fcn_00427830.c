#include <string.h>

extern int g_6b7e98;
extern void __cdecl fcn_00426680(int stream, void *out);
extern int __cdecl fcn_004260f0(int a0, char *text);
extern int __cdecl fcn_00427740(int a0, unsigned int a1, int a2);
extern void __cdecl fcn_00425bf0(int a0, int a1, char *text);
extern int __cdecl fcn_00427600(int a0, void *rec);
extern int __cdecl fcn_0064e790(int a0, int a1);

/* ADDRESS: GOLDTL 0x00427830 */
unsigned int __cdecl fcn_00427830(int a0, unsigned int a1)
{
    struct {
        char text[36];
        int status;
    } msg;
    int v8[24];
    int v2;
    int v3;
    unsigned int v4;
    unsigned int v5;
    char *v6;
    char *v10;
    char v1;
    char *q;

    fcn_00426680(*(unsigned int *)(g_6b7e98 + 0x118), &msg.status);
    if (msg.status)
        return 1;
    v2 = 0;
    do
    {
        v1 = ((char *) v8)[v2];
        msg.text[v2] = v1;
        v2++;
    } while (v1);
    fcn_00426680(*(unsigned int *)(g_6b7e98 + 0x118), &msg.status);
    v2 = a0;
    if (msg.status != 1)
        return 1;
    if (v8[0] == 10)
    {
        v3 = fcn_004260f0(a0, msg.text);
        if (v3)
            return 1;
        q = (char *)(fcn_00427740(v2, a1, 1) + 4);
        v10 = msg.text;
        do
        {
            v1 = *v10;
            *q = v1;
            v10++;
            q++;
        } while (v1);
        return 1;
    }
    if (v8[0] == 2)
    {
        v3 = fcn_004260f0(a0, msg.text);
        if (v3)
        {
            __asm { int 3 }
        }
        q = (char *)(fcn_00427740(v2, a1, 1) + 4);
        v10 = msg.text;
        do
        {
            v1 = *v10;
            *q = v1;
            v10++;
            q++;
        } while (v1);
        fcn_00426680(*(unsigned int *)(g_6b7e98 + 0x118), &msg.status);
        if (msg.status != 5)
            return 1;
        **(int **)(v2 + 0x2c) = v8[0];
        return 1;
    }
    if (v8[0] == 0xc)
    {
        v4 = *(unsigned int *)(g_6b7e98 + 0x118);
        v3 = fcn_00427600(a0, v8);
        if (v3)
        {
            v5 = fcn_0064e790(v4, 0x7b);
            *(unsigned int *)(*(int *)(v2 + 0x10c) - 300 + *(int *)(v2 + 0x110) * 0x14c) = v5;
            v6 = (char *)(*(int *)(v2 + 0x10c) - 0x14c + *(int *)(v2 + 0x110) * 0x14c);
            v10 = msg.text;
            do
            {
                v1 = *v10;
                v10++;
                *v6 = v1;
                v6++;
            } while (v1);
            *(unsigned int *)(g_6b7e98 + 0x118) = v4;
            return 1;
        }
        return 0;
    }
    if (v8[0] != 0x1b)
        return 1;
    fcn_00426680(*(unsigned int *)(g_6b7e98 + 0x118), &msg.status);
    v2 = a0;
    if (msg.status != 5)
    {
        v3 = 1;
        fcn_00425bf0(a0, *(unsigned int *)(a0 + 0x118), (char *)0x6794a0);
    }
    else
        v3 = v8[0];
    if (!fcn_004260f0(v2, msg.text))
    {
        v3 = fcn_00427740(v2, a1, v3);
        q = (char *)(v3 + 4);
        v10 = msg.text;
        do
        {
            v1 = *v10;
            *q = v1;
            v10++;
            q++;
        } while (v1);
    }
    fcn_00426680(*(unsigned int *)(g_6b7e98 + 0x118), &msg.status);
    if (v8[0] != 0x1c)
        fcn_00425bf0(v2, *(unsigned int *)(v2 + 0x118), (char *)0x679490);
    fcn_00426680(*(unsigned int *)(g_6b7e98 + 0x118), &msg.status);
    if (v8[0] == 10)
        return 1;
    fcn_00425bf0(v2, *(unsigned int *)(v2 + 0x118), (char *)0x679480);
    return 1;
}
