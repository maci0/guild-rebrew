


#include <string.h>

#pragma intrinsic(memcpy, memset)

extern char g_aed2a0[];
void __cdecl cm_EnqueueClientPacket(void*);

void __cdecl cm_SendChangeDesire(void)
{
	char buf[0x9c];

	buf[0] = 0x18;
	memcpy(buf + 0x10, g_aed2a0, 0x7c);
	cm_EnqueueClientPacket(buf);
}
