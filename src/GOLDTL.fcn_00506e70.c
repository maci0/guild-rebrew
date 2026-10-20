extern unsigned char g_slot_table[];

/* ADDRESS: GOLDTL 0x00506e70 */
int __cdecl fcn_00506e70(unsigned int idx, int count, ...)
{
    unsigned char *t;
    int *p;
    int i;
    int found;

    t = g_slot_table + (idx & 0xffff) * 0x21c;
    found = 0;
    if (count >= 0) {
        p = &count;
        for (i = 0; i < count; i++) {
            if (found)
                break;
            if (t[0x166] == *++p || t[0x169] == *p)
                found = 1;
        }
    }
    return found;
}
