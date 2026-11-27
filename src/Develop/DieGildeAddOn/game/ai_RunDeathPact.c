#include <string.h>

#include "client_types.h"
extern pos14_7f4c00 gm_GameTime;
extern unsigned short g_7f4c04;
extern int g_7f4c08;
extern short g_7f4c0c;

void __cdecl cm_SendCopyEntityData(char* msg);

/* ADDRESS: GOLDTL 0x0048fba0 */
int __cdecl ai_RunDeathPact(char* actor, char* home, int req, char* out)
{
	char msg[0xf8];

	memset(msg, 0, sizeof(msg));
	msg[4] = (char) 0x8a;
	msg[0x36] = 1;
	*(int*) (msg + 8) = *(int*) (actor + 4);
	*(int*) (msg + 0xc) = *(int*) (home + 1);
	*(int*) (msg + 0x28) = (*(int*)&gm_GameTime);
	*(int*) (msg + 0x2c) = (*(int*)&g_7f4c04);
	*(int*) (msg + 0x30) = g_7f4c08;
	*(short*) (msg + 0x34) = g_7f4c0c;
	*(int*) (msg + 0x58) = *(int*) (out + 4);
	*(int*) (msg + 0x38) = *(int*) (out + 4);
	cm_SendCopyEntityData(msg);
	return 0x3d;
}
