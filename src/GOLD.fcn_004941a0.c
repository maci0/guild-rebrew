// FUNCTION: GOLD 0x004941a0
// fcn_004941a0 — lowword of fcn_0042ec00(2) non-zero.

int __cdecl gm_RandomMod(int);

int __cdecl fcn_004941a0(void)
{
	int r;
	r = gm_RandomMod(2) & 0xffff;
	return r != 0;
}
