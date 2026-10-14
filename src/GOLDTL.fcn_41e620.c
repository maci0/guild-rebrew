/* ADDRESS: GOLDTL 0x0041e620 */

// fcn_00422d60 — call [0x662470](0); set 2 fields; return 1.

int __cdecl fcn_00422d60(void)
{
	((void* (__stdcall*)(int)) *(void**) 0x662470)(0);
	*(int*) 0x14cc5bc = 0x29a;
	*(short*) 0x14cc5b8 = 0;
	return 1;
}
