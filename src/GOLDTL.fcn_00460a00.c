

#include <string.h>

#pragma intrinsic(memcpy, memset)

void __cdecl fcn_00460a00(char* a1, void* a2, int a3)
{
	char* dst;

	dst = *(char**) (a1 + 0x28);
	memcpy(dst, a2, a3);
	*(int*) (a1 + 0x34) = (int) *(char**) (a1 + 0x28) + a3;
	*(int*) (a1 + 0x30) = (int) *(char**) (a1 + 0x28) + a3;
}
