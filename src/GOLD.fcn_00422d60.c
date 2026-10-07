// FUNCTION: GOLD 0x00422d60
// fcn_00422d60 — call [0x5eb370](0); set 2 fields; return 1.

int __cdecl fcn_00422d60(void)
{
	((void* (__stdcall*)(int)) *(void**) 0x5eb370)(0);
	*(int*) 0x14613fc = 0x29a;
	*(short*) 0x14613f8 = 0;
	return 1;
}
