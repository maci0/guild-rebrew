// FUNCTION: GOLDTL 0x57ddc0

#include <string.h>

#pragma intrinsic(strcpy)

typedef int (__stdcall* fcn_0057ddc0_fn)(int, int, int, char*);

void __cdecl fcn_0057ddc0(char* a1)
{
	strcpy((char*) 0x77df20, a1);
	*(int*) 0x7749f4 = (*(fcn_0057ddc0_fn*) 0x6620b0)(0x6a81bc, 0x6a81c4, 0, (char*) 0x77df20);
}
