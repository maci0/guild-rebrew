


#include <string.h>

void __cdecl cm_EnqueueClientPacket(void*);

/* ADDRESS: GOLDDE 0x004b3b80 */
void __cdecl cm_RequestUpdateEconomyStats(void* src)
{
	char buf[0x9c];

	buf[0] = 0x41;
	memcpy(buf + 0x10, src, 0x3a);
	cm_EnqueueClientPacket(buf);
}
