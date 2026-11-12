/* ADDRESS: GOLD 0x00454030 */
void __cdecl fcn_00454030(int* src, int* dst)
{
    int j;
    int i;
    int* p;

    for (i = 4; i != 0; i--) {
        p = src;
        for (j = 4; j != 0; j--) {
            *dst++ = *p;
            p += 4;
        }
        src++;
    }
}
