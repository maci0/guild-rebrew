// FUNCTION: GOLDTL 0x421050
// SIZE: 68

void __cdecl fcn_00421050(void)
{
	if (*(int*) 0x14cbca0 != -1) {
		((void (__stdcall*)(int, int)) *(void**) 0x662374)(*(int*) 0x14cbca0, 2);
		((void (__stdcall*)(int)) *(void**) 0x66234c)(*(int*) 0x14cbca0);
		*(int*) 0x14cbca0 = -1;
		*(int*) 0x14cbcb0 = 1;
	}
	((void (__stdcall*)(void)) *(void**) 0x662360)();
	*(int*) 0x6b7d40 = 0;
}
