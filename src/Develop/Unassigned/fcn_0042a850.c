extern int g_6b7f90;
int __cdecl fcn_0042b1c0(int a);

/* ADDRESS: GOLDTL 0x0042a850 */
int __cdecl fcn_0042a850(int a)
{
    int r = 0;

    if (g_6b7f90 != 0) {
        if (fcn_0042b1c0(a) >= 0) {
            (*(void (__stdcall **)(int)) 0x6623cc)(a);
        } else {
            r = -1;
        }
    } else {
        r = -1;
    }
    return r;
}
