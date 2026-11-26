


#include <string.h>

#pragma intrinsic(memcpy, memset)

void __cdecl cm_EnqueueClientPacket(void*);

void __cdecl fcn_004ce1d0(void)
{
	char buf[0x9c];

	memset(buf + 0x10, 0, 0x80);
	*(int*) (buf + 0x10) = 0;
	buf[0] = 0x5f;
	cm_EnqueueClientPacket(buf);
}
