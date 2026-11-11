
// fcn_00476b60 — [0xf8a668]=-1; fcn_00410620(); [0x1468410]=0.

void __cdecl fcn_004116d0(void);

void __cdecl fcn_00476b60(void)
{
	*(int*) 0xf8a668 = 0xffffffff;
	fcn_004116d0();
	*(char*) 0x1468410 = 0;
}
