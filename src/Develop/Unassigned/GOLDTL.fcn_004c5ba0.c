


#include <string.h>

void __cdecl cm_EnqueueClientPacket(void*);

void __cdecl cm_RequestChrWalkToDummy(int charId, int gebId, int objId, char* text)
{
	char buf[0x9c];

	buf[0] = 0x2f;
	*(int*) (buf + 0x10) = charId;
	*(int*) (buf + 0x14) = gebId;
	*(int*) (buf + 0x18) = objId;
	strcpy(buf + 0x1c, text);
	cm_EnqueueClientPacket(buf);
}
