#include <string.h>

#include "Develop/client_types.h"
extern pos14_7f4c00 gm_GameTime;
extern unsigned short g_7f4c04;
extern int g_7f4c08;
extern short g_7f4c0c;
extern unsigned char g_773d75;

void __cdecl cm_RequestChangeBits(int, int, int, int, int);
void __cdecl cm_RequestTransferCurrencyNoKill(int, int, char, int);
void __cdecl cm_SendCopyEntityData(char* msg);

/* ADDRESS: GOLDTL 0x004abb10 */
int __cdecl ai_RunVerfluchen(char* actor, char* action)
{
	char msg[0xf8];

	cm_RequestChangeBits(*(int*) (actor + 4), 0x1cc, 4, 0x10, 0);
	cm_RequestTransferCurrencyNoKill(-1, *(int*) (actor + 4), (*(char*)&g_773d75), -*(int*) (action + 0x10));
	memset(msg, 0, sizeof(msg));
	msg[4] = (char) 0x9d;
	*(int*) (msg + 8) = *(int*) (actor + 4);
	*(int*) (msg + 0xc) = -1;
	*(int*) (msg + 0x28) = (*(int*)&gm_GameTime);
	*(int*) (msg + 0x2c) = (*(int*)&g_7f4c04);
	*(int*) (msg + 0x30) = g_7f4c08;
	*(short*) (msg + 0x34) = g_7f4c0c;
	msg[0x36] = 2;
	*(int*) (msg + 0x58) = *(int*) (action + 0xc);
	*(int*) (msg + 0x5c) = *(int*) (action + 4);
	cm_SendCopyEntityData(msg);
	return 0x45;
}
