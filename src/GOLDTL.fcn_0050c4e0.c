extern unsigned char* g_868050;

/* ADDRESS: GOLDTL 0x0050c4e0 */
int __cdecl fcn_0050c4e0(unsigned char* arg)
{
    unsigned char* p;

    p = g_868050 + (unsigned int) *arg * 0x24d;
    switch (p[0]) {
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
    case 10:
    case 11:
    case 12:
    case 13:
    case 14:
    case 15:
    case 16:
    case 17:
    case 18:
    case 19:
        return p[0x247];
    }
    return p[0x247];
}
