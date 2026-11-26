


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
void __cdecl fcn_004c4eb0(char* s);
void __cdecl fcn_004c4ef0(char* s);
int __cdecl fcn_0050d170(int k);
void __cdecl fcn_004c5150(int a, int b, char c, int n);
void __cdecl fcn_004c5530(char* msg);

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
	fcn_004c4eb0(g_67eb20);
	fcn_004c5150(-1, *(int*) (p + 2), (*(char*)&g_773d75), (int) (fcn_0050d170(*(int*) (a2 + 4)) * 0.3f));
	fcn_004c5530(msg);
	fcn_004c4ef0(g_67eb20);
	return 0x3c;
}
