


#include <string.h>

#pragma intrinsic(memcpy, memset)

void __cdecl cm_EnqueueClientPacket(void*);

void __cdecl cm_RequestPreloadSceneEntry(int entryId)
{
	char buf[0x9c];

	memset(buf + 0x10, 0, 0x80);
	buf[0] = 0x5f;
	*(int*) (buf + 0x10) = 5;
	*(int*) (buf + 0x14) = entryId;
	cm_EnqueueClientPacket(buf);
}
