// FUNCTION: GOLDTL 0x41fd30
// SIZE: 59

int __cdecl fcn_0042a0e0(int, int);

void __cdecl fcn_004c3140(void* a)
{
	if (*(int*) 0x6b71a8 != 0) {
		((void (__stdcall*)(int)) *(void**) 0x662074)(0x14cc5a0);
		fcn_0042a0e0(*(int*) 0x6b71a8, (int) a);
		*(int*) 0x678164 = (int) a;
		((void (__stdcall*)(int)) *(void**) 0x662070)(0x14cc5a0);
	}
}
