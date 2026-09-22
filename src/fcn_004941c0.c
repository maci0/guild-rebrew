// FUNCTION: GOLD 0x004941c0
// SIZE: 16
/* Calls fcn_0042ec00(7), masks result to 16 bits. */
int __cdecl fcn_0042ec00(int n);

int __cdecl fcn_004941c0(void)
{
    return fcn_0042ec00(7) & 0xffff;
}
