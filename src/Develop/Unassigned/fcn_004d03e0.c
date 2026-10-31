/* Partial reconstruction of the native body: resource allocation and the
 * g_774688 mode switch are recovered; the rest is listed in the row blocker. */

int __cdecl d2_GetResourceData(int size);
int __cdecl fcn_00451840(int a, int b, float c);

/* ADDRESS: GOLDTL 0x004d03e0 */
int __cdecl fcn_004d03e0(void)
{
    int mode;

    d2_GetResourceData(0x52c);
    mode = 0;
    if (*(int*) 0x774688 == -1) {
        if (fcn_00451840(*(int*) 0x6b8014 + 0xfc, 0x662d70, 0.2f) != 0)
            mode = 1;
        else
            mode = 2;
    } else if (*(int*) 0x774688 == 1) {
        if (fcn_00451840(*(int*) 0x6b8014 + 0xe4, 0x662d70, 0.2f) != 0)
            mode = 1;
        else
            mode = 2;
    } else if (*(int*) 0x774688 == 0) {
        if (fcn_00451840(*(int*) 0x6b8014 + 0xe4, 0x662d70, 0.2f) != 0)
            mode = 1;
    }
    return mode;
}
