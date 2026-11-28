


#include <string.h>

#pragma intrinsic(memcpy, memset)

void __cdecl cm_EnqueueClientPacket(void*);

/* ADDRESS: GOLDDE 0x004b3e20 */
void __cdecl cm_RequestSendChat(char* src)
{
	char buf[0x9c];
	char* p;

	p = buf;
	*(char*) p = 0x4b;
	memcpy(p + 0x10, src, 0x80);
	cm_EnqueueClientPacket(p);
}
