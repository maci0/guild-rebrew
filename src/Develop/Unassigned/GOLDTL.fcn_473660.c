

/* fcn_00476b60: [0x100f1dc]=-1; fcn_004116d0(); *(char*)0x14cf950=0. */

void __cdecl io_ClearInputState(void);

void __cdecl fcn_00476b60(void)
{
	*(int*) 0x100f1dc = 0xffffffff;
	io_ClearInputState();
	*(char*) 0x14cf950 = 0;
}
