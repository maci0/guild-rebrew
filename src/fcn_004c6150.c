// FUNCTION: GOLDTL 0x4c6150
// SIZE: 62

#include <string.h>

#pragma intrinsic(strlen, strcpy, strcat)

void __cdecl fcn_004c4330(void*);

void __cdecl fcn_004c6150(int a1, char* a2)
{
	char buf[0x9c];

	*(int*) (buf + 0x10) = a1;
	buf[0] = 0x3e;
	strcpy(buf + 0x14, a2);
	fcn_004c4330(buf);
}
