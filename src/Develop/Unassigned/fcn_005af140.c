extern void *__cdecl sub_508e40(int);
extern void *__cdecl sub_4fe2e0(void *, void *, int, int, int, unsigned long);
extern void __cdecl sub_4c5c00(void *, int, int, unsigned long);
extern void __cdecl sub_5338a0(void);
extern int __cdecl sub_5373e0(unsigned long, int);
extern void *__cdecl sub_5338d0(unsigned long, long, int);
extern void __cdecl sub_5ae960(long);
extern void __cdecl sub_5aeab0(long);
extern void __cdecl sub_5aee90(long);
extern void __cdecl sub_4030e0(void *);

/* ADDRESS: GOLDTL 0x005af140 */
int __cdecl fcn_005af140(void *a0, void *a1)
{
    void *esi, *edi, *ebx, *ebp;
    long made, cur;
    int v, w;

    esi = 0;
    edi = 0;
    ebx = 0;
    ebp = 0;
    made = 0;

    v = *(char *)((char *)a0 + 0x65);
    if (v != -1) {
        esi = sub_508e40(v);
        if (esi != 0) {
            if (*(void **)((char *)esi + 0x184) == 0) {
                if ((unsigned char)*(char *)((char *)esi + 2) != 6 &&
                    (unsigned char)*(char *)((char *)esi + 2) != 7) {
                    made = (long)sub_4fe2e0(esi, *(void **)0x6b8010,
                                             0, 0, 0, 0x6a69a8);
                }
            }
            if (*(void **)((char *)esi + 0x184) != 0) {
                v = *(int *)((char *)a1 + 2);
                w = *(int *)(*(char **)((char *)esi + 0x184) + 0x30);
                if (w != v) {
                    sub_4c5c00(*(void **)((char *)esi + 4),
                                *(int *)((char *)a0 + 1), v, 0x6a69a8);
                }
            }
        }
    }

    sub_5338a0();
    while (sub_5373e0(0x5af140, 0x67fff)) {
        if (*(unsigned short *)0x7746d8 & 0x200) {
            edi = sub_5338d0(0x6ab334, *(long *)0x14ab9fc, 0x16);
            ebx = sub_5338d0(0x6ab320, *(long *)0x14aba2c, 0x16);
        }
        if (esi != 0) {
            if (*(int *)(0x7f4ca4 +
                         (unsigned long)(*(unsigned short *)0x774970) * 540) ==
                *(int *)((char *)esi + 4)) {
                if ((unsigned char)*(char *)((char *)esi + 0x1b1) > 0) {
                    ebp = sub_5338d0(0x6ab30c, *(long *)0x14b52dc, 0x16);
                }
            }
        }
        cur = *(long *)0x7746a0;
        if (cur != 0) {
            if (cur == (long)edi)
                sub_5ae960(made);
            else if (cur == (long)ebx)
                sub_5aeab0(made);
            else if (cur == (long)ebp)
                sub_5aee90(made);
        }
    }

    if (made != 0 && esi != 0) {
        sub_4030e0((void *)made);
        *(void **)((char *)esi + 0x184) = 0;
    }
    return 0;
}
