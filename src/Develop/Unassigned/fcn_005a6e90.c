extern int d2_CurrentWindowId;
extern int g_100f1dc;
extern int d2_CurrentElementId;
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
int __cdecl d2_CenterDialogWindows(int);
int __cdecl fcn_0046f280(int);
int __cdecl fcn_0046b2b0(int);
void __cdecl d2_ClearPaintbox(void);
int __cdecl d2_ClearWindowChildren(int, int);
int __cdecl fcn_005c9450(int, int, int);
int __cdecl fcn_005c9310(int, int, int, int, int);
int __cdecl fcn_005373e0(int, int);
int __cdecl fcn_00471e30(int);

/* ADDRESS: GOLDTL 0x005a6e90 */
int __cdecl fcn_005a6e90(unsigned short *subjectRecord)
{
    int activeTab, refreshNeeded;
    int s18, s1c, s20, s24;
    int arr[9][3];
    int i;
    int edi, ebx, dialogWindow, r;
    int q1, q2;
    int g;
    int *p;

    refreshNeeded = 1;
    activeTab = 1;

    if (subjectRecord == 0)
        return 1;

    for (i = 0; i < 9; i++)
    {
        arr[i][0] = -1;
        arr[i][1] = -1;
        arr[i][2] = 0;
    }

    edi = gm_WalkEntityChain(*subjectRecord);
    r = gm_AccumulateTyped2((int)subjectRecord);
    dialogWindow = fcn_00470820(0, 0, 0x6aad0c);
    d2_SetForm(dialogWindow, 0);

    g = d2_CurrentWindowId;
    *(int *)(0x10162e8 + g * 0x3cc) = 0xc;
    *(int *)(0x10162ec + g * 0x3cc) = 0x14;
    *(int *)(0x10162f0 + g * 0x3cc) = 0xc;
    *(int *)(0x10162f4 + g * 0x3cc) = 0xc;

    d2_SetForm(dialogWindow, 1);
    io_AppendText(0x18ed);
    d2_SetForm(dialogWindow, 4);
    io_AppendText(0x18ee, *subjectRecord);
    io_AppendText(0x18ef, edi, r);

    d2_SetForm(dialogWindow, 3);
    q1 = fcn_00472250(dialogWindow, 3, io_AppendText(0x18f0));
    d2_SetForm(dialogWindow, 5);
    q2 = fcn_00472250(dialogWindow, 5, io_AppendText(0x18f1));
    d2_SetForm(dialogWindow, 0);

    r = fcn_00472830(dialogWindow, 2, 0x100, (int)&s20, (int)&s24, (int)&s1c);
    fcn_00533f40(0x206, 0x167, d2_CurrentWindowId, r);
    d2_CenterDialogWindows(dialogWindow);

    g_100f1dc = -1;
    d2_CurrentElementId = -1;

    while (1)
    {
        int k;
        if (refreshNeeded != 0) {
        refreshNeeded = 0;

        for (k = 0; k < 9; k++)
        {
            if (activeTab == 1)
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

        d2_SetForm(dialogWindow, 2);
        d2_ClearPaintbox();
        d2_ClearWindowChildren(d2_CurrentWindowId, 1);

        edi = activeTab;
        if (edi == 1)
        {
            if (fcn_005c9450((int)subjectRecord, 0, 0) <= 0)
                io_AppendText(0x18f2, *subjectRecord);
        }
        else if (edi == 2)
        {
            r = fcn_005c9310((int)subjectRecord, 9, (int)arr, dialogWindow, edi);
            if (r == 0)
                io_AppendText(0x18f3, *subjectRecord);
        }

        }
        edi = activeTab;
        if (g_100f1dc != -1)
        {
            int eax = d2_CurrentElementId;
            if (eax == q1)
            {
                if (edi != 1)
                {
                    activeTab = 1;
                    refreshNeeded = 1;
                }
            }
            else if (eax == q2)
            {
                if (edi != 2)
                {
                    activeTab = 2;
                    refreshNeeded = 1;
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

        return fcn_00471e30(dialogWindow);
    }

done:
    return 0;
}
