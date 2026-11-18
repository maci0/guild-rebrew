

#include <string.h>

#pragma intrinsic(memcpy, memset)

void __cdecl fcn_00460a00(char* buffer, void* src, int size)
{
	char* dst;

	dst = *(char**) (buffer + 0x28);
	memcpy(dst, src, size);
	*(int*) (buffer + 0x34) = (int) *(char**) (buffer + 0x28) + size;
	*(int*) (buffer + 0x30) = (int) *(char**) (buffer + 0x28) + size;
}
