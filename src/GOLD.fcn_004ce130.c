extern char g_930600[];

/* ADDRESS: GOLD 0x004ce130 */
char* __cdecl fcn_004ce130(int key)
{
    int i;

    for (i = 0; i < 32; i++) {
        if (*(unsigned short*)(g_930600 + i * 0x21c) != 0xffff &&
            *(int*)(g_930600 + i * 0x21c + 4) == key) {
            return g_930600 + i * 0x21c;
        }
    }
    return 0;
}
