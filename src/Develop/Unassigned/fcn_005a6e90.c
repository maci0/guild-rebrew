extern int g_772514;
extern int g_100f1dc;
extern int g_67d370;
extern int g_14ce8e0;
extern int g_774654;
int __cdecl gm_WalkEntityChain(unsigned short);
int __cdecl gm_AccumulateTyped2(int);
int __cdecl fcn_00470820(int, int, int);
void __cdecl d2_SetForm(int, int);
int __cdecl io_AppendText(int, ...);
int __cdecl fcn_00472250(int, int, int);
int __cdecl fcn_00472830(int, int, ...);
int __cdecl fcn_00533f40(int, int, int, int);
int __cdecl fcn_00471b60(int);
int __cdecl fcn_0046f280(int);
int __cdecl fcn_0046b2b0(int);
void __cdecl fcn_00472e50(void);
int __cdecl fcn_0046f2c0(int, int);
int __cdecl fcn_005c9450(int, int, int);
int __cdecl fcn_005c9310(int, int, int, int, int);
int __cdecl fcn_005373e0(int, int);
int __cdecl fcn_00471e30(int);

/* ADDRESS: GOLDTL 0x005a6e90 */
int __cdecl fcn_005a6e90(unsigned short *a1)
{
    int s10, s14;
    int s18, s1c, s20, s24;
    int arr[9][3];
    int i;
    int edi, ebx, esi, r;
    int q1, q2;
    int g;
    int *p;

    s14 = 1;
    s10 = 1;

    if (a1 == 0)
        return 1;

    for (i = 0; i < 9; i++)
    {
        arr[i][0] = -1;
        arr[i][1] = -1;
        arr[i][2] = 0;
    }

    edi = gm_WalkEntityChain(*a1);
    r = gm_AccumulateTyped2((int)a1);
    esi = fcn_00470820(0, 0, 0x6aad0c);
    d2_SetForm(esi, 0);

    g = g_772514;
    p = (int *)0x10162e8 + g * 243;
    p[0] = 0xc;
    p[1] = 0x14;
    p[2] = 0xc;
    p[3] = 0xc;

    d2_SetForm(esi, 1);
    io_AppendText(0x18ed);
    d2_SetForm(esi, 4);
    io_AppendText(0x18ee, *a1);
    io_AppendText(0x18ef, edi, r);

    d2_SetForm(esi, 3);
    q1 = fcn_00472250(esi, 3, io_AppendText(0x18f0));
    d2_SetForm(esi, 5);
    q2 = fcn_00472250(esi, 5, io_AppendText(0x18f1));
    d2_SetForm(esi, 0);

    r = fcn_00472830(esi, 2, 0x100, (int)&s20, (int)&s24, (int)&s1c);
    fcn_00533f40(0x206, 0x167, g_772514, r);
    fcn_00471b60(esi);

    g_100f1dc = -1;
    g_67d370 = -1;

    while (1)
    {
        int k;
        if (s14 != 0) {
        s14 = 0;

        for (k = 0; k < 9; k++)
        {
            if (s10 == 1)
            {
                p = &arr[k][0];
                if (*p != -1)
                {
                    fcn_0046f280(*p);
                    fcn_0046b2b0(p[1]);
                    p[0] = -1;
                    p[1] = -1;
                    p[2] = 0;
                }
            }
        }

        d2_SetForm(esi, 2);
        fcn_00472e50();
        fcn_0046f2c0(g_772514, 1);

        edi = s10;
        if (edi == 1)
        {
            if (fcn_005c9450((int)a1, 0, 0) <= 0)
                io_AppendText(0x18f2, *a1);
        }
        else if (edi == 2)
        {
            r = fcn_005c9310((int)a1, 9, (int)arr, esi, edi);
            if (r == 0)
                io_AppendText(0x18f3, *a1);
        }

        }
        edi = s10;
        if (g_100f1dc != -1)
        {
            int eax = g_67d370;
            if (eax == q1)
            {
                if (edi != 1)
                {
                    s10 = 1;
                    s14 = 1;
                }
            }
            else if (eax == q2)
            {
                if (edi != 2)
                {
                    s10 = 2;
                    s14 = 1;
                }
            }
        }

        if (g_14ce8e0 != 0)
            g_774654 = 1;

        if (fcn_005373e0(0x5a6e90, 0x677c7) != 0)
            continue;

        for (i = 0; i < 9; i++)
        {
            p = &arr[i][0];
            if (*p != -1)
            {
                fcn_0046f280(*p);
                fcn_0046b2b0(p[1]);
                p[0] = -1;
                p[1] = -1;
                p[2] = 0;
            }
        }

        return fcn_00471e30(esi);
    }

done:
    return 0;
}
