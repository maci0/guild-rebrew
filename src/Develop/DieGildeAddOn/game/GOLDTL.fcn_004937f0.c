
/* Calls gm_RandomMod(7), masks to 16 bits. */
int __cdecl gm_RandomMod(int n);

int __cdecl fcn_004937f0(void)
{
    return gm_RandomMod(7) & 0xffff;
}
