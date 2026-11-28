


#include <string.h>

#pragma intrinsic(memcpy, memset)

extern char cm_AttributePacketData[];
void __cdecl cm_EnqueueClientPacket(void*);

void __cdecl cm_SendSetAttribute(void)
{
	char buf[0x9c];

	buf[0] = 0x17;
	memcpy(buf + 0x10, cm_AttributePacketData, 0x7c);
	cm_EnqueueClientPacket(buf);
}
