int __cdecl fcn_00546190(int a);

typedef struct {
    char pad70[0x70];
    int f70;
    char pad74[0x38];
    unsigned char b_ac;
} Obj5504c0;

/* ADDRESS: GOLDTL 0x005504c0 */
unsigned char __cdecl fcn_005504c0(Obj5504c0 *a)
{
    int v;

    v = a->f70;
    if (v == -2 || (v == 0 && a->b_ac <= 0)) {
        return fcn_00546190((int) a);
    }
    if (v == 0) {
        return --a->b_ac;
    }
    return v;
}
