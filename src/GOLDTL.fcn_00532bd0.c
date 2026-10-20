extern char g_7e46ac;
extern int g_7746c4;
extern int g_7746c8;
extern int g_7746cc;
extern int g_7746d8;
extern int g_7746dc;
extern int g_774688;
extern int g_77468c;
extern unsigned short g_774970;
extern char *g_6b8014;
extern int g_77250c;
extern int g_1015eac;
extern int g_1015ea8;
extern int g_1040490;
extern int g_1040494;

extern int __cdecl fcn_00506380(int a0, int a1, int a2, int a3);
extern int __cdecl fcn_00466190(int a0);
extern int __cdecl fcn_00451840(char *p, int a1, float a2);
extern void __cdecl fcn_0047a040(int a0, int a1, int a2, int a3);
extern void __cdecl fcn_0047cba0(int a0, int a1, int a2, int a3, int a4);

/* ADDRESS: GOLDTL 0x00532bd0 */
void __cdecl fcn_00532bd0(void)
{
    int v3 = 0;
    int v4 = 0;
    int v5 = 0;
    int v7 = 0;
    int v1;
    int v2;

    if (!(g_7e46ac & 8))
        return;
    if (g_7746c4 != 0 || g_7746c8 != 0)
    {
        v2 = g_7746c4 ? g_7746c4 : g_7746c8;
        if (v2 != 0)
        {
            if (g_7746cc != 0 || g_7746c8 != 0)
            {
                g_7746dc = fcn_00506380(g_774970, v2, g_7746cc, 0);
                if (!(g_7746dc & 0x1000))
                    return;
            }
        }
    }
    if (!(g_7746d8 & 0x1000))
        return;
    v1 = fcn_00466190(0x52c);
    if (g_774688 == -1)
    {
        v3 = 1;
        if (!fcn_00451840(g_6b8014 + 0xfc, 0x662d70, 0.2f))
            v3 = 2;
    }
    else if (g_774688 == 1)
    {
        v4 = 1;
        if (!fcn_00451840(g_6b8014 + 0xe4, 0x662d70, 0.2f))
            v4 = 2;
    }
    else if (g_774688 == 0)
    {
        if (!fcn_00451840(g_6b8014 + 0xe4, 0x662d70, 0.2f))
            v4 = 1;
        if (!fcn_00451840(g_6b8014 + 0xfc, 0x662d70, 0.2f))
            v3 = 1;
    }
    if (g_77468c == -1)
    {
        v5 = 1;
        if (!fcn_00451840(g_6b8014 + 0xb4, 0x662d70, 0.2f))
            v5 = 2;
    }
    else if (g_77468c == 1)
    {
        v7 = 1;
        if (!fcn_00451840(g_6b8014 + 0xcc, 0x662d70, 0.2f))
            v7 = 2;
    }
    else if (g_77468c == 0)
    {
        if (!fcn_00451840(g_6b8014 + 0xb4, 0x662d70, 0.2f))
            v5 = 1;
        if (!fcn_00451840(g_6b8014 + 0xcc, 0x662d70, 0.2f))
            v7 = 1;
    }
    fcn_0047a040(0, 0, *(int *)(g_77250c + 4), *(int *)(g_77250c + 8));
    if (v5 == 2)
        fcn_0047cba0(g_1015eac - 0x10, g_1040490 - 0x20, g_77250c, v1, 0);
    else if (v5 == 1)
        fcn_0047cba0(g_1015eac - 0x10, g_1040490 - 0x20, g_77250c, v1, v5);
    if (v4 == 2)
        fcn_0047cba0(4, g_1015ea8, g_77250c, v1, v4);
    else if (v4 == 1)
        fcn_0047cba0(4, g_1015ea8, g_77250c, v1, 3);
    if (v3 == 2)
        fcn_0047cba0(g_1040494 - 0x96, g_1015ea8, g_77250c, v1, 4);
    else if (v3 == 1)
        fcn_0047cba0(g_1040494 - 0x96, g_1015ea8, g_77250c, v1, 5);
    if (v7 == 2)
        fcn_0047cba0(g_1015eac - 0x10, 0x38, g_77250c, v1, 6);
    else if (v7 == 1)
        fcn_0047cba0(g_1015eac - 0x10, 0x38, g_77250c, v1, 7);
}
