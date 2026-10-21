extern int __cdecl sub_526010(void *, int, unsigned char);
extern void * __cdecl sub_470820(int, int, int);
extern int __cdecl sub_519190(int, unsigned char);
extern void * __cdecl sub_472250(void *, int, int);
extern int __cdecl sub_50d2a0(void *);
extern int __cdecl sub_472380(void *, int, int, int);
extern int __cdecl sub_471b60(void *);
extern int __cdecl sub_5373e0(int, int);
extern int __cdecl sub_526120(int, int);
extern int __cdecl sub_471f80(void *);
extern int __cdecl sub_471e30(void *);

/* ADDRESS: GOLDTL 0x005b8760 */
int __cdecl fcn_005b8760(void)
{
    int x = *(int *)0x7e46ac;
    int v;
    int keep;
    int ebp = 0;
    void *edi, *esi;

    if (!sub_526010((int *)0x7f4ca0 + *(unsigned short *)0x774970 * 135,
                    0x140, *(unsigned char *)0x773d75))
        return 0;

    edi = sub_470820(0, 0, 0x68d704);
    v = sub_519190(0x4141, *(unsigned char *)0x773d75);
    esi = sub_472250(edi, 0, v);
    v = sub_50d2a0((int *)0x7f4ca0 + *(unsigned short *)0x774970 * 135);
    if (v > 0x12c0)
        v = 0x12c0;
    v = v / 32;
    sub_472380(esi, 0xa, v, 0xa);
    sub_471b60(edi);

    if (sub_5373e0(0x5b8760, x) == 0)
        goto done;

    for (;;) {
        x = 1;
        switch (*(int *)0x100f1dc) {
        case 2:
            sub_526120(*(int *)0x14b5828, 4);
            *(int *)0x774654 = x;
            ebp = sub_471f80(esi);
            break;
        case 1:
            goto c1;
        default:
            if (*(unsigned char *)0x14cf950 == 1)
                goto c1;
            break;
        }
        goto after;
    c1:
        *(int *)0x774654 = x;
        ebp = 0;
    after:
        if (*(int *)0x14ce8e0)
            *(int *)0x774654 = x;
        if (!sub_5373e0(0x5b8760, keep))
            break;
    }

done:
    sub_471e30(edi);
    return ebp;
}
