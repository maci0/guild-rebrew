


#include <string.h>

#pragma intrinsic(memcpy, memset)

void __cdecl cm_EnqueueClientPacket(void*);

/* ADDRESS: GOLDDE 0x004b44b0 */
void __cdecl cm_SendAllocGraveyardWorker(char* source)
{
	char buf[0x9c];

	buf[0] = 0x62;
	memcpy(buf + 0x10, source, 0x19);
	cm_EnqueueClientPacket(buf);
}
