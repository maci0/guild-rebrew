extern double __cdecl gp_64dc80(double, double);
extern long __cdecl gp_64d228(double);

/* ADDRESS: GOLDTL 0x0041b870 */
int __cdecl fcn_0041b870(void)
{
    unsigned short t1[256], t2[256], t3[256];
    int i;
    float m;
    double lo, mid, hi, st;
    double c28, lim, c9;
    void **obj, **vt;
    void (__cdecl *mth)(void *, int, void *);

    lo = *(float *)0x6777bc / *(double *)0x6629c8;
    mid = *(float *)0x6777c0 / *(double *)0x6629c8;
    hi = *(float *)0x6777c4 / *(double *)0x6629c8;
    c28 = *(double *)0x662c28;
    lim = *(double *)0x662950;
    c9 = *(double *)0x6629c8;

    for (i = 0; i < 0x100; i++) {
        m = (float)((double)i * *(float *)0x662c30);

        st = gp_64dc80(lo, *(float *)0x6777b0 * m) + *(float *)0x6b5df8;
        if (st == lim)
            st = c9;
        else
            st = lim;
        t1[i] = (unsigned short)gp_64d228(st * c28);

        st = gp_64dc80(mid, *(float *)0x6777b4 * m) + *(float *)0x6b5dfc;
        if (st == lim)
            st = c9;
        else
            st = lim;
        t2[i] = (unsigned short)gp_64d228(st * c28);

        st = gp_64dc80(hi, *(float *)0x6777b8 * m) + *(float *)0x6b5e00;
        if (st == lim)
            st = c9;
        else
            st = lim;
        t3[i] = (unsigned short)gp_64d228(st * c28);
    }

    obj = *(void **)0x6b5de0;
    vt = *(void ***)obj;
    mth = (void (__cdecl *)(void *, int, void *))vt[0x12];
    mth(obj, 0, t3);
    return 0;
}
