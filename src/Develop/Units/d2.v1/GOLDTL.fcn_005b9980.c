extern int g_772514;
extern int g_774970;
extern unsigned char g_773d75;
extern int g_14ce8e0;
extern int g_774654;
extern int g_100f1dc;
extern int g_67d370;

extern int __cdecl fcn_0050c490(int a0, int a1);
extern int __cdecl io_FormatTextBuffer(char *a0, char *a1, ...);
extern int __cdecl fcn_00526120(char *a0, int a1);
extern int __cdecl fcn_00470820(int a0, int a1, char *a2);
extern void __cdecl fcn_00471b60(int a0);
extern void __cdecl d2_SetForm(int a0, int a1);
extern int __cdecl io_AppendText(int a0);
extern int __cdecl fcn_00472250(int a0, int a1, int a2);
extern void __cdecl fcn_00533dc0(int a0, int a1, int a2);
extern int __cdecl d2_CreateRadioGroup(int a0, int a1, int a2, int a3);
extern int __cdecl fcn_004695a0(int a0, int a1);
extern int __cdecl _ftol(void);
extern int __cdecl fcn_005373e0(void *a0, int a1);
extern void __cdecl fcn_00471e30(int a0);
extern int __cdecl fcn_00469510(int a0);
extern void __cdecl eval_ObjektPreis2Credits(int a0, int a1);
extern int __cdecl fcn_00526010(char *a0, int a1, int a2);
extern int __cdecl fcn_0051e070(void);
extern int __cdecl fcn_00526120(char *a0, int a1);
extern void __cdecl fcn_0046f9b0(int a0, char *a1);
extern void __cdecl fcn_00469090(int a0);
extern void __cdecl fcn_004c51a0(int a0, int a1, char a2, int a3);
extern int __cdecl gm_GetEntityTableEntry(int a0);
extern void __cdecl fcn_004c51f0(int a0, int a1, int a2, int a3, char a4, int a5);

/* ADDRESS: GOLDTL 0x005b9980 */
void __cdecl fcn_005b9980(int a0)
{
    int v17;
    int v5;
    int v1;
    int v16;
    int v14[3];
    char v13[512];
    char v15[1024];
    int h;
    int i;
    int v7;
    int v;

    v17 = 0;
    if (fcn_0050c490(a0, 0) >= 3)
    {
        io_FormatTextBuffer(v13, (char *)0xf1, 3);
        fcn_00526120(v13, 0);
        return;
    }
    h = fcn_00470820(0, 0, (char *)0x6ac354);
    fcn_00471b60(h);
    d2_SetForm(h, 2);
    io_AppendText(0xd8);
    v14[0] = fcn_00472250(h, 1, 0);
    v14[1] = fcn_00472250(h, 1, 1);
    v14[2] = fcn_00472250(h, 1, 2);
    d2_SetForm(h, 0);
    fcn_00533dc0(g_772514, 0x70b, 0x741);
    d2_SetForm(h, 3);
    v5 = fcn_00472250(h, 3, io_AppendText(0xdb));
    v1 = d2_CreateRadioGroup(3, v14[0], v14[1], v14[2]);
    fcn_004695a0(v1, 0);
    v16 = 35 * v1;
    do
    {
        if (g_100f1dc >= 0x5e2 && g_100f1dc <= 0x5e4)
        {
            for (i = 0; i < 3; i++)
            {
                if (g_67d370 == v14[i])
                    v17 = i;
            }
        }
        else if (g_100f1dc == 2)
        {
            if (g_67d370 == v5)
            {
                eval_ObjektPreis2Credits(v17 + 0x134, 100);
                v7 = _ftol();
                if (fcn_00526010((char *)(g_774970 * 0x21c + 0x7f4ca0), v7,
                        (v7 & 0xffffff00) | g_773d75))
                {
                    switch (fcn_0051e070())
                    {
                    case 1:
                        io_FormatTextBuffer(v15, (char *)0xd9, v17 * 2 + 0xc10, v7);
                        break;
                    case 0:
                        io_FormatTextBuffer(v15, (char *)0xd9, v7, v17 * 2 + 0xc10);
                        break;
                    }
                    if (fcn_00526120(v15, 0x101))
                    {
                        fcn_004c51a0(-1, *(int *)(g_774970 * 0x21c + 0x7f4ca4),
                            g_773d75, v7);
                        v = gm_GetEntityTableEntry(g_774970 * 0x21c + 0x7f4ca0);
                        if (v != 0)
                            *(int *)(v + 0x50) = *(int *)(v + 0x50) + v7;
                        fcn_004c51f0(*(int *)(a0 + 1), -1, v17 + 0x134, 1,
                            g_773d75, 0);
                        g_774654 = 1;
                    }
                }
            }
        }
        if (*(int *)(0x102cbc8 + v16 * 4) != -1)
        {
            eval_ObjektPreis2Credits(v17 + 0x134, 100);
            io_FormatTextBuffer(v13, (char *)0xda, v17 * 2 + 0xc10, _ftol());
            fcn_0046f9b0(v5, v13);
            fcn_00469090(v5);
        }
        if (g_14ce8e0 != 0)
            g_774654 = 1;
    } while (fcn_005373e0((void *)0x5b9980, 0x677c7) != 0);
    fcn_00471e30(h);
    fcn_00469510(v1);
}
