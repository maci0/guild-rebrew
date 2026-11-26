


#include <string.h>

void __cdecl cm_EnqueueClientPacket(void*);

void __cdecl cm_SendAllocCharacter(char entityType, int buildingId, int targetRecordId, char gender, char variant, char itemId, char* name)
{
	char buf[0x9c];

	buf[0] = 0x49;
	*(char*) (buf + 0x14) = entityType;
	*(int*) (buf + 0x17) = buildingId;
	*(int*) (buf + 0x1b) = targetRecordId;
	*(char*) (buf + 0x1f) = gender;
	*(char*) (buf + 0x20) = variant;
	*(char*) (buf + 0x21) = itemId;
	strcpy(buf + 0x26, name);
	cm_EnqueueClientPacket(buf);
}
