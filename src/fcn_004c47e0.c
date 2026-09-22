// FUNCTION: GOLDTL 0x4c47e0
// SIZE: 55

#include <string.h>

#pragma intrinsic(memcpy, memset)

void __cdecl fcn_004c47e0(int* p)
{
	int v;

	v = p[1];
	*(char*) 0xaed2a4 = 0;
	*(int*) 0xaed2a0 = v;
	memset((void*) 0xaed2a5, 0, 119);
	*(int*) 0xaed320 = 0;
	*(int*) 0xaed334 = (int) p;
}
