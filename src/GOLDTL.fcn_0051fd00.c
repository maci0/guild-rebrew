extern char* g_6b5c20;

/* ADDRESS: GOLDTL 0x0051fd00 */
int __cdecl fcn_0051fd00(void* action)
{
    unsigned int offset;

    if (action != 0) {
        offset = (unsigned int)action - (unsigned int)g_6b5c20;
        return offset / 0x194u;
    }
    return -1;
}
