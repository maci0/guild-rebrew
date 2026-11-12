extern int g_68da68[40][6];

/* ADDRESS: GOLD 0x004e6f10 */
int __cdecl fcn_004e6f10(int index)
{
    if (index >= 0x28) {
        return 0;
    }
    return g_68da68[index][1];
}
