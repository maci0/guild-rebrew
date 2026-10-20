extern int __cdecl fcn_006508ff(int);
extern int __fastcall fcn_00615e12(void *self);
extern int __fastcall fcn_00614703(void *self, int d1, int a0, int a1, int a2,
                                   int a3, int a4, int a5);
extern void __fastcall fcn_005ef238(void *self, int d1, int flag);

/* ADDRESS: GOLDTL 0x005ef94b */
int __cdecl fcn_005ef94b(int a0, unsigned int a1, unsigned int a2,
                         unsigned int a3, unsigned int a4, int *a5)
{
    int *v1;
    void *v2;
    int v3;
    int rc;

    v1 = a5;
    if (!a0)
        return 0x8876086c;
    if (!a5)
        return 0x8876086c;
    rc = fcn_006508ff(0x494);
    if (rc)
        v2 = (void *)fcn_00615e12((void *)rc);
    else
        v2 = 0;
    if (!v2)
        return 0x8007000e;
    v3 = fcn_00614703(v2, 0, a0, (int)a1, 1, (int)a2, (int)a3, (int)a4);
    if (v3 < 0) {
        fcn_005ef238(v2, 0, 1);
        return v3;
    }
    *v1 = (int)v2;
    return 0;
}
