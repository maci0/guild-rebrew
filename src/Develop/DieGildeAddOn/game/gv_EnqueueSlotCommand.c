

#include <string.h>

#pragma intrinsic(memcpy, memset)

void __cdecl cm_EnqueueClientPacket(void*);

/* ADDRESS: GOLDDE 0x004b4430 */
void __cdecl gv_EnqueueSlotCommand(char* data)
{
	char buf[0x9c];

	buf[0] = 0x60;
	memcpy(buf + 0x10, data, 0x1f);
	cm_EnqueueClientPacket(buf);
}
