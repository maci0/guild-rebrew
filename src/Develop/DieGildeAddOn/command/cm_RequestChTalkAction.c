


#include <string.h>

int __cdecl cm_EnqueueClientPacket(char*);

/* ADDRESS: GOLDDE 0x004b3f40 */
int __cdecl cm_RequestChTalkAction(char* actorName, int arg1, int arg2, char* targetName)
{
	char buf[0x9c];

	buf[0] = 0x4e;
	strcpy(buf + 0x10, actorName);
	*(int*) (buf + 0x28) = arg1;
	*(int*) (buf + 0x2c) = arg2;
	if (targetName != 0)
		strcpy(buf + 0x30, targetName);
	else
		buf[0x30] = 0;
	return cm_EnqueueClientPacket(buf);
}
