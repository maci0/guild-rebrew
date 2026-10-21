extern int __cdecl sub_64d41a(void *, unsigned long, unsigned long, unsigned long, void *);
extern void *__cdecl sub_64e2f9(void *, unsigned long);
extern void __cdecl sub_64e48f(void *, int, int);
extern void __cdecl sub_64ed28(void *, int, int, void *);
extern void __cdecl sub_64e1fd(void *);
extern void __cdecl sub_41ddd0(unsigned long);

/* ADDRESS: GOLDTL 0x0042dac0 */
int __cdecl fcn_0042dac0(int a)
{
    char *p;
    char buf[0x200], l2[0x40];
    int *tabA, *tabC;
    int j, lim, v;

    p = (char *)0x149d180 + a * 116;
    tabA = (int *)0x14a5320;
    tabC = (int *)0x11bb000;

    sub_64d41a(buf, 0x679de4, 0x1052f00, 0x679888, p - 0x60);
    if (sub_64e2f9(l2, 0x6790b0) == 0) {
        sub_41ddd0(*(unsigned long *)0x6b7fa0);
        *(unsigned long *)0x6b7fa0 = 0;
        return 0;
    }
    l2[0] = 0; /* keep handle in l2[0] */

    sub_64e48f(l2, 0, 0);

    lim = *(int *)(p + 4) + 1;
    for (j = *(int *)(p + 0); j < lim; j++) {
        v = tabA[j] - *(int *)(p + 8);
        l2[4] = (char)v;
        sub_64ed28(l2 + 4, 4, 1, l2);
    }
    for (j = *(int *)(p + 0); j < lim; j++) {
        sub_64ed28((char *)0x1053000 + j * 80, 0x50, 1, l2);
    }
    for (j = *(int *)(p + 0); j < lim; j++) {
        sub_64ed28(tabC + j, 1, 1, l2);
    }

    sub_64ed28(p + 12, 4, 1, l2);
    sub_64ed28(p + 8, *(int *)(p + 12), 1, l2);
    sub_64e1fd(l2);
    return 1;
}
