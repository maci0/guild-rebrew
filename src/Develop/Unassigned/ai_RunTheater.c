#include <string.h>

#include "client_types.h"
extern pos14_7f4c00 gm_GameTime;
extern unsigned short g_7f4c04;
extern int g_7f4c08;
extern short g_7f4c0c;

void __cdecl gm_ModifyHealth(int id, int amount);
void __cdecl cm_SendCopyEntityData(char* msg);

/* ADDRESS: GOLDTL 0x004abd80 */
int __cdecl ai_RunTheater(char* actor, char* x)
{
	char msg[0xf8];

	gm_ModifyHealth(*(int*) (actor + 4), -*(int*) (x + 0x10));
	memset(msg, 0, sizeof(msg));
	msg[4] = (char) 0xa0;
	*(int*) (msg + 8) = *(int*) (actor + 4);
	*(int*) (msg + 0xc) = *(int*) (x + 4);
	*(int*) (msg + 0x28) = (*(int*)&gm_GameTime);
	*(int*) (msg + 0x2c) = (*(int*)&g_7f4c04);
	*(int*) (msg + 0x30) = g_7f4c08;
	*(short*) (msg + 0x34) = g_7f4c0c;
	msg[0x36] = 2;
	*(int*) (msg + 0x58) = *(int*) (x + 0xc);
	cm_SendCopyEntityData(msg);
	return 0x46;
}
