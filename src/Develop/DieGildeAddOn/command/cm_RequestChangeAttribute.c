extern char cm_AttributePacketData[];
extern char cm_AttributePacketData[];



#include <string.h>

#pragma intrinsic(memcpy, memset)

void __cdecl cm_EnqueueClientPacket(void*);

void __cdecl cm_RequestChangeAttribute(void)
{
	char buf[0x9c];

	buf[0] = 0x16;
	memcpy(buf + 0x10, cm_AttributePacketData, 0x7c);
	cm_EnqueueClientPacket(buf);
}
