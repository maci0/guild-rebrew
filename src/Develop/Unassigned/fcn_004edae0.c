extern void *__cdecl sub_42ff50(unsigned long, unsigned long, unsigned long);
extern int __cdecl sub_430910(void *, int, int, void *);
extern void __cdecl sub_430580(void *);

/* ADDRESS: GOLDTL 0x004edae0 */
int __cdecl fcn_004edae0(void)
{
    void *esi;
    int l;
    int i;
    char *b;

    esi = sub_42ff50(0x68dfec, 0x6790b0, *(unsigned long *)0x6b7fdc);
    if (esi == 0)
        return 0;
    if (sub_430910(&l, 4, 1, esi) <= 0)
        goto fail;
    for (i = 0; i < *(int *)0x772fd8; i++) {
        b = *(char *)0x772fdc + i * 12;
        if (sub_430910(b, 1, 1, esi) <= 0)
            goto fail;
        if (sub_430910(b + 1, 1, 1, esi) <= 0)
            goto fail;
        if (sub_430910(b + 2, 1, 1, esi) <= 0)
            goto fail;
        if (sub_430910(b + 3, 1, 1, esi) <= 0)
            goto fail;
        if (sub_430910(b + 4, 1, 1, esi) <= 0)
            goto fail;
        if (sub_430910(b + 8, 4, 1, esi) <= 0)
            goto fail;
    }
    for (i = 0; i < *(int *)0x772fe0; i++) {
        b = *(char *)0x772fe4 + i * 12;
        if (sub_430910(b, 4, 1, esi) <= 0)
            goto fail;
        if (sub_430910(b + 4, 4, 1, esi) <= 0)
            goto fail;
        if (sub_430910(b + 8, 4, 1, esi) <= 0)
            goto fail;
    }
    sub_430580(esi);
    return 1;
fail:
    sub_430580(esi);
    return 0;
}
