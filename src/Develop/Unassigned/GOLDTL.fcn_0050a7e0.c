typedef unsigned char u8;

/* Partial reconstruction: the type-table scans and the first slot probe are
 * recovered from the native body; the remaining action-table paths are
 * listed in the row blocker. */

/* ADDRESS: GOLDTL 0x0050a7e0 */
int __cdecl fcn_0050a7e0(void)
{
    char* p;
    int i;

    i = 0;
    p = (char*) 0x7f4ca0;
    while (*(unsigned short*) p != 0xffff) {
        p += 0x21c;
        i++;
        if (p >= (char*) 0x85a0a0)
            break;
    }
    if (i == 0x300) {
        i = 0;
        p = (char*) 0x7f4ca2;
        while (*p != 0x0f) {
            p += 0x21c;
            i++;
            if (p >= (char*) 0x85a0a2)
                break;
        }
    }
    p = (char*) 0x7f4ca0 + i * 540;
    if (*(u8*) (p + 2) == 0x0f)
        *(int*) 0x773d70 = *(int*) 0x773d70 - 1;
    return 0;
}
