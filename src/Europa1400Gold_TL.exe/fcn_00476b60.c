// FUNCTION: GOLDTL 0x473660
// SIZE: 23

// fcn_00476b60 — [0x100f1dc]=-1; fcn_00410620(); [0x14cf950]=0.

void __cdecl fcn_00410620(void);

void __cdecl fcn_00476b60(void)
{
	*(int*) 0x100f1dc = 0xffffffff;
	fcn_00410620();
	*(char*) 0x14cf950 = 0;
}
