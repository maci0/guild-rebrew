int __cdecl gm_FindSlot170Entry(int a);

/* ADDRESS: GOLDTL 0x004f0e10 */
int __cdecl fcn_004f0e10(int a, int b)
{
    int r;

    r = a;
    if (a != -1) {
        r = gm_FindSlot170Entry(a);
        if (r != 0) {
            if (b == 0 || b == 1) {
                *(int *) (r + 0x14) = b;
            }
        }
    }
    return r;
}
