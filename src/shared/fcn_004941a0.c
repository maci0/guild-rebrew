// FUNCTION: GOLD 0x004941a0
// SIZE: 18
// fcn_004941a0 — lowword of fcn_0042ec00(2) non-zero.

int __cdecl fcn_0042ec00(int);

int __cdecl fcn_004941a0(void)
{
	int r;
	r = fcn_0042ec00(2) & 0xffff;
	return r != 0;
}
