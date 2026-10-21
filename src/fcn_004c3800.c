typedef int (__cdecl *pfn_v)(void);
typedef int (__cdecl *pfn_3)(int, int, int);
typedef int (__cdecl *pfn_4)(int, int, int, int);

/* ADDRESS: GOLDTL 0x004c3800 */
int __cdecl fcn_004c3800(void *arg1)
{
    unsigned int bp;
    int edi, ebx;
    unsigned char *esi;
    int flag;
    int slot;
    int r;
    unsigned int w;
    int x;
    int ret;

    flag = 0;

    bp = ((pfn_v)0x42e410)();
    bp &= 0xffff;

    edi = *(int *)(*(int *)((char *)arg1 + 0x34) + 0x204);
    if (!edi)
        return 0;

    esi = *(unsigned char **)(edi + 0x16c);
    w = *(unsigned short *)(esi + 0x27);
    x = *(unsigned short *)0x774970;
    ((pfn_3)0x50f980)(w, x, 1);

    r = ((pfn_v)0x64d228)();
    ebx = r / 33;

    if (*esi != 0x20 && *esi != 0x1f && *esi != 0x1e)
        ret = ((pfn_3)0x50cce0)((int)esi, (int)&slot, 0);
    else
        ret = ((pfn_3)0x50ce20)((int)esi, (int)&slot, 0);

    if (ret && *(int *)(&slot + 1) == 0)
        flag = 1;

    if (ebx == 0)
    {
        if (flag)
            ((pfn_4)0x4c3030)(
                *(unsigned short *)edi,
                *(int *)0x772e7c,
                0x68a994,
                3);
        else
            ((pfn_4)0x4c3030)(
                *(unsigned short *)edi,
                *(int *)0x772e7c,
                0x68a994,
                bp);
        return 0;
    }

    if (ebx == 1)
    {
        if (flag)
            ((pfn_4)0x4c3030)(
                *(unsigned short *)edi,
                *(int *)0x772e7c,
                0x68a984,
                3);
        else
            ((pfn_4)0x4c3030)(
                *(unsigned short *)edi,
                *(int *)0x772e7c,
                0x68a984,
                bp);
        return 0;
    }

    if (ebx < 2)
        return 0;

    if (flag)
        ((pfn_4)0x4c3030)(
            *(unsigned short *)edi,
            *(int *)0x772e7c,
            0x68a978,
            3);
    else
        ((pfn_4)0x4c3030)(
            *(unsigned short *)edi,
            *(int *)0x772e7c,
            0x68a978,
            bp);

    return 0;
}
