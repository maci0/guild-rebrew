


#include <string.h>

void __cdecl cm_EnqueueClientPacket(void*);

void __cdecl cm_RequestUpdateEconomyStats(void* src)
{
	char buf[0x9c];

	buf[0] = 0x41;
	memcpy(buf + 0x10, src, 0x3a);
	cm_EnqueueClientPacket(buf);
}
