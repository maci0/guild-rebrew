// FUNCTION: GOLD 0x00596140
// SIZE: 28
// fcn_00596140 — repeat fcn_005309d0 until non-zero.

int __cdecl fcn_0052e1c0(void);
int __cdecl fcn_005309d0(void*, int);

void __cdecl fcn_00596140(void)
{
	int r;
	do {
		fcn_0052e1c0();
		r = fcn_005309d0((void*) 0x00596140, 0x67fff);
	} while (r != 0);
}
