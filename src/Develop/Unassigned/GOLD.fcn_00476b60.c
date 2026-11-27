
/* fcn_00476b60: [0xf8a668]=-1; fcn_004116d0(); *(char*)0x1468410=0. */

void __cdecl io_ClearInputState(void);

void __cdecl d2_ResetSelectionAndInput(void)
{
	*(int*) 0xf8a668 = 0xffffffff;
	io_ClearInputState();
	*(char*) 0x1468410 = 0;
}
