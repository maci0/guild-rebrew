


#include <string.h>

#include "Develop/client_types.h"
extern pos14_7f4c00 gm_GameTime;
extern unsigned short gm_GameTimeHour;
extern int gm_GameTimeSliceDword;
extern short gm_GameTimeTailWord;
extern unsigned char gm_ActiveTownIndex;
extern float g_66414c;
extern char g_67eb20[];

char* __cdecl gm_FindPublicTreasury(int k);
void __cdecl cm_SendLogAction(char* s);
void __cdecl cm_SendTraceEnd(char* s);
int __cdecl gm_GetTypeProductValue(int k);
void __cdecl cm_RequestMoveCredits(int a, int b, char c, int n);
void __cdecl cm_SendCopyEntityData(char* msg);

int __cdecl ai_RunBuergermeisterKerker(char* actor, char* a2, char* target)
{
	char msg[0xf8];
	char* p;

	p = gm_FindPublicTreasury(1);
	if (p == 0) {
		return 0;
	}
	if (actor[0x166] != 0xf) {
		return 0;
	}
	if (*target != 4 && *(int*) (a2 + 0x10) != 0) {
		return 0;
	}
	memset(msg, 0, sizeof(msg));
	msg[4] = 0x1e;
	*(int*) (msg + 8) = *(int*) (actor + 4);
	*(int*) (msg + 0xc) = *(int*) (target + 4);
	msg[0x36] = 1;
	*(int*) (msg + 0x28) = (*(int*)&gm_GameTime);
	*(int*) (msg + 0x2c) = (*(int*)&gm_GameTimeHour);
	*(int*) (msg + 0x30) = gm_GameTimeSliceDword;
	*(short*) (msg + 0x34) = gm_GameTimeTailWord;
	*(int*) (msg + 0x58) = *(int*) (target + 4);
	cm_SendLogAction(g_67eb20);
	cm_RequestMoveCredits(-1, *(int*) (p + 2), (*(char*)&gm_ActiveTownIndex), (int) (gm_GetTypeProductValue(*(int*) (a2 + 4)) * 0.3f));
	cm_SendCopyEntityData(msg);
	cm_SendTraceEnd(g_67eb20);
	return 0x3c;
}
