


#include <string.h>

#pragma intrinsic(memcpy, memset)

extern char cm_SecondaryPacketDelta[];
void __cdecl cm_EnqueueClientPacket(void*);

/* ADDRESS: GOLDDE 0x004b2da0 */
void __cdecl cm_SendChangeDesire(void)
{
	char buf[0x9c];

	buf[0] = 0x18;
	memcpy(buf + 0x10, cm_SecondaryPacketDelta, 0x7c);
	cm_EnqueueClientPacket(buf);
}
