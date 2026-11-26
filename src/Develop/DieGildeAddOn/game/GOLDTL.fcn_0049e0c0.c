


#include <string.h>

#include "client_types.h"
extern pos14_7f4c00 gm_GameTime;
extern unsigned short g_7f4c04;
extern int g_7f4c08;
extern short g_7f4c0c;
extern unsigned char g_773d75;
extern float g_66414c;
extern char g_67eb20[];

char* __cdecl gm_FindPublicTreasury(int k);
void __cdecl cm_SendLogAction(char* s);
void __cdecl cm_SendTraceEnd(char* s);
int __cdecl fcn_0050d170(int k);
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
	*(int*) (msg + 0x2c) = (*(int*)&g_7f4c04);
	*(int*) (msg + 0x30) = g_7f4c08;
	*(short*) (msg + 0x34) = g_7f4c0c;
	*(int*) (msg + 0x58) = *(int*) (target + 4);
	cm_SendLogAction(g_67eb20);
	cm_RequestMoveCredits(-1, *(int*) (p + 2), (*(char*)&g_773d75), (int) (fcn_0050d170(*(int*) (a2 + 4)) * 0.3f));
	cm_SendCopyEntityData(msg);
	cm_SendTraceEnd(g_67eb20);
	return 0x3c;
}
