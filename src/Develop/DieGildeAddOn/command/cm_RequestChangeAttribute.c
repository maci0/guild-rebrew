extern char g_aed220[];
extern char g_aed220[];



#include <string.h>

#pragma intrinsic(memcpy, memset)

void __cdecl cm_EnqueueClientPacket(void*);

void __cdecl cm_RequestChangeAttribute(void)
{
	char buf[0x9c];

	buf[0] = 0x16;
	memcpy(buf + 0x10, g_aed220, 0x7c);
	cm_EnqueueClientPacket(buf);
}
