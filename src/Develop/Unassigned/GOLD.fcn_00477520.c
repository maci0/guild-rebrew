
/* ADDRESS: GOLD 0x00477520 */
void __cdecl fcn_00477520(void)
{
    int idx;
    int p;
    int neg;
    int a;
    int b;
    char *base;

    if (*(int *)0x6ed9dc == 0)
        return;
    idx = *(int *)(*(int *)0x6ed9dc + 0x134);
    base = *(char **)0xf8f080;
    *(int *)(base + idx * 187 * 4 + 0x2c) = 0;
    neg = -1;
    p = *(int *)0x5febc4;
    *(int *)0x6ed9dc = 0;
    if (p != neg) {
        a = *(int *)0xf8a664;
        b = *(int *)0xf8a66c;
        *(int *)0x5febc4 = neg;
        *(int *)0x5f323c = a;
        *(int *)0x6310b4 = b;
    }
}
