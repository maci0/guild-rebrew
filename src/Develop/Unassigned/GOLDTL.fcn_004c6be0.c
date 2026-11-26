


#include <string.h>

#pragma intrinsic(memcpy, memset)

void __cdecl cm_EnqueueClientPacket(void*);

void __cdecl fcn_004c6be0(char* a1, char* src)
{
	char buf[0x9c];

	buf[0] = 0x5e;
	*(int*) (buf + 0x14) = *(int*) (a1 + 1);
	memcpy(buf + 0x18, src, 0x1c);
	cm_EnqueueClientPacket(buf);
}
