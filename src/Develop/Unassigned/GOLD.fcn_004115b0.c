/* ADDRESS: GOLD 0x004115b0 */
void __cdecl fcn_004115b0(unsigned char a0)
{
    if (*(int*) 0x6310c4) {
        if (a0 & 1) {
            *(int*) 0x14673ac = 0;
            *(int*) 0x14683ec = 0;
        }
        if (a0 & 2) {
            *(int*) 0x14673a0 = 0;
            *(int*) 0x14683e0 = 0;
        }
        if (a0 & 4) {
            *(int*) 0x14673a4 = 0;
            *(int*) 0x14683e4 = 0;
        }
        if (a0 & 8) {
            *(int*) 0x1467398 = 0;
            *(int*) 0x14683d8 = 0;
        }
        if (a0 & 16) {
            *(int*) 0x146738c = 0;
            *(int*) 0x14683cc = 0;
        }
        if (a0 & 32) {
            *(int*) 0x1467390 = 0;
            *(int*) 0x14683d0 = 0;
        }
    } else {
        if (a0 & 1) {
            *(int*) 0x1467398 = 0;
            *(int*) 0x14683d8 = 0;
        }
        if (a0 & 2) {
            *(int*) 0x146738c = 0;
            *(int*) 0x14683cc = 0;
        }
        if (a0 & 4) {
            *(int*) 0x1467390 = 0;
            *(int*) 0x14683d0 = 0;
        }
        if (a0 & 8) {
            *(int*) 0x14673ac = 0;
            *(int*) 0x14683ec = 0;
        }
        if (a0 & 16) {
            *(int*) 0x14673a0 = 0;
            *(int*) 0x14683e0 = 0;
        }
        if (a0 & 32) {
            *(int*) 0x14673a4 = 0;
            *(int*) 0x14683e4 = 0;
        }
    }
}
