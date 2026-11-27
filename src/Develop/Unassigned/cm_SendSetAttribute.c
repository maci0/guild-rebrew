


#include <string.h>

#pragma intrinsic(memcpy, memset)

extern char g_aed220[];
void __cdecl cm_EnqueueClientPacket(void*);

void __cdecl cm_SendSetAttribute(void)
{
	char buf[0x9c];

	buf[0] = 0x17;
	memcpy(buf + 0x10, g_aed220, 0x7c);
	cm_EnqueueClientPacket(buf);
}
