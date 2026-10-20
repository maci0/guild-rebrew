/* ADDRESS: GOLDTL 0x004f5cc0 */
int __cdecl fcn_004f5cc0(unsigned char a0, int a1)
{
    int r;

    r = 0;
    switch (a1) {
    case 1:
        if ((a0 & 0xf0) < 0x30)
            r = 1;
        break;
    case 2:
        r = 0;
        break;
    case 3:
        r = 0;
        break;
    case 4:
        r = 0;
        break;
    case 5:
        r = 0;
        break;
    case 6:
        r = 0;
        break;
    case 7:
        r = 0;
        break;
    }
    return r;
}
