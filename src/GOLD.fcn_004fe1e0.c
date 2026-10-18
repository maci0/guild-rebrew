/* ADDRESS: GOLD 0x004fe1e0 */
void __cdecl fcn_004fe1e0(char *a, char b, int c, int d)
{
    *(int *)(a + 10) = d & 255;
    *(unsigned short *)(a + 4) = (unsigned char)b;
    *(int *)(a + 6) = c & 255;
}
