


#include <string.h>

#pragma intrinsic(memcpy, memset)

void __cdecl cm_EnqueueClientPacket(void*);

void __cdecl cm_SendUpdateSlot80(char* data, char a2)
{
	char buf[0x9c];

	buf[0] = 0x3f;
	*(char*) (buf + 0x10) = a2;
	memcpy(buf + 0x11, data, 0x80);
	cm_EnqueueClientPacket(buf);
}
