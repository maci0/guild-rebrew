


#include <string.h>

#pragma intrinsic(strlen, strcpy, strcat)

void __cdecl cm_EnqueueClientPacket(void*);

void __cdecl cm_SendSwapEntityModel(int entityId, char* modelName)
{
	char buf[0x9c];

	*(int*) (buf + 0x10) = entityId;
	buf[0] = 0x3e;
	strcpy(buf + 0x14, modelName);
	cm_EnqueueClientPacket(buf);
}
