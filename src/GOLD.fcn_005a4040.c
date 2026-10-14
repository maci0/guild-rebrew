
// fcn_005a4040 — repeat fcn_005309d0 until nonzero result then exit loop.

int __cdecl fcn_0052e1c0(void);
int __cdecl fcn_005309d0(void*, int);

void __cdecl fcn_005a4040(void)
{
	do {
		fcn_0052e1c0();
	} while (fcn_005309d0((void*) 0x005a4040, 0x67fff) == 0);
}
