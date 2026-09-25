// FUNCTION: GOLDTL 0x41daf0
// SIZE: 59

#include <windows.h>

void __cdecl DispatchLogOutput(int, int, int);

void __cdecl fcn_0041daf0(int a1)
{
	if (*(int*) 0x6b6f48 == 0) {
		MessageBoxA(0, (char*) 0x677d68, (char*) 0x677d90, 0x10030);
		return;
	}
	if (*(int*) 0x6b6f50 & 1) {
		DispatchLogOutput(a1, *(int*) 0x6b6f50, 1);
	}
}
