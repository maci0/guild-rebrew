typedef int (__cdecl *pfn_v)(void);
typedef int (__cdecl *pfn_1)(int);
typedef int (__cdecl *pfn_2)(int, int);
typedef int (__cdecl *pfn_3)(int, int, int);
typedef int (__cdecl *pfn_c3)(int, int, int);
typedef int (__cdecl *pfn_6)(int, int, int, int, int, int);
typedef int (__cdecl *pfn_5)(int, int, int, int, int);
typedef int (__cdecl *pfn_4)(int, int, int, int);

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

    s10 = 1;
    s14 = 1;

    if (a1 == 0)
        goto done;

    for (i = 0; i < 9; i++)
    {
        arr[i][0] = -1;
        arr[i][1] = -1;
        arr[i][2] = 0;
    }

    edi = ((pfn_1)0x50dac0)(*a1);
    r = ((pfn_1)0x50d2a0)((int)a1);
    esi = ((pfn_c3)0x470820)(0x6aad0c, 0, 0);
    ((pfn_2)0x4727a0)(0, esi);

    g = *(int *)0x772514;
    p = (int *)0x10162e8 + g * 243;
    p[0] = 0xc;
    p[1] = 0x14;
    p[2] = 0xc;
    p[3] = 0xc;

    ((pfn_2)0x4727a0)(1, esi);
    ((pfn_1)0x519190)(0x18ed);
    ((pfn_2)0x4727a0)(4, esi);
    ((pfn_2)0x519190)(0x18ee, *a1);
    ((pfn_3)0x519190)(0x18ef, edi, r);

    ((pfn_2)0x4727a0)(3, esi);
    q1 = ((pfn_3)0x472250)(esi, 3, ((pfn_v)0x519190)());
    ((pfn_2)0x4727a0)(5, esi);
    q2 = ((pfn_3)0x472250)(esi, 5, ((pfn_v)0x519190)());
    ((pfn_2)0x4727a0)(0, esi);

    r = ((pfn_6)0x472830)(esi, 2, 0x100, (int)&s20, (int)&s24, (int)&s1c);
    ((pfn_4)0x533f40)(0x206, 0x167, g, r);
    ((pfn_1)0x471b60)(esi);

    *(int *)0x100f1dc = -1;
    *(int *)0x67d370 = -1;

    while (s14 != 0)
    {
        int k;
        s14 = 0;

        for (k = 0; k < 9; k++)
        {
            if (s10 == 1)
            {
                p = &arr[k][0];
                if (*p != -1)
                {
                    ((pfn_1)0x46f280)(*p);
                    ((pfn_1)0x46b2b0)(p[1]);
                    p[0] = -1;
                    p[1] = -1;
                    p[2] = 0;
                }
            }
        }

        ((pfn_2)0x4727a0)(2, esi);
        ((pfn_v)0x472e50)();
        ((pfn_2)0x46f2c0)(*(int *)0x772514, 1);

        edi = s20;
        if (edi == 1)
        {
            if (((pfn_3)0x5c9450)(0, 0, (int)a1) <= 0)
                ((pfn_2)0x519190)(0x18f2, *a1);
        }
        else if (edi == 2)
        {
            r = ((pfn_5)0x5c9310)((int)a1, 9, (int)&s20, esi, edi);
            if (r == 0)
                ((pfn_2)0x519190)(0x18f3, *a1);
        }

        if (*(int *)0x100f1dc != -1)
        {
            int eax = *(int *)0x67d370;
            if (eax == s1c)
            {
                if (edi != 1)
                {
                    s10 = 1;
                    s14 = 1;
                }
            }
            else if (eax == s18)
            {
                if (edi != 2)
                {
                    s10 = 2;
                    s14 = 1;
                }
            }
        }

        if (*(int *)0x14ce8e0 != 0)
            *(int *)0x774654 = 1;

        if (((pfn_2)0x5373e0)(0x5a6e90, 0x677c7) != 0)
            continue;

        for (i = 0; i < 9; i++)
        {
            p = &arr[i][0];
            if (*p != -1)
            {
                ((pfn_1)0x46f280)(*p);
                ((pfn_1)0x46b2b0)(p[1]);
                p[0] = -1;
                p[1] = -1;
                p[2] = 0;
            }
        }

        ((pfn_1)0x471e30)(esi);
        break;
    }

done:
    return 0;
}
