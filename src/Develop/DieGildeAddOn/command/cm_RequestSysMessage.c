


#include <string.h>

#pragma intrinsic(memcpy, memset)

void __cdecl cm_EnqueueClientPacket(void*);

/* ADDRESS: GOLDDE 0x004b3130 */
void __cdecl cm_RequestSysMessage(char kind, char* data)
{
	char buf[0x9c];

	buf[0] = 0x20;
	*(char*) (buf + 0x10) = kind;
	if (data != 0) {
		memcpy(buf + 0x11, data, 0x7c);
	}
	cm_EnqueueClientPacket(buf);
}
