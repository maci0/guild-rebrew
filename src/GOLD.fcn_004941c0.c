// FUNCTION: GOLD 0x004941c0
/* Calls fcn_0042ec00(7), masks result to 16 bits. */
int __cdecl gm_RandomMod(int n);

int __cdecl fcn_004941c0(void)
{
    return gm_RandomMod(7) & 0xffff;
}
