#include "Develop/DieGildeAddOn/game/spiel.h"



#include <string.h>

#include "Develop/client_types.h"
extern pos14_7f4c00 gm_GameTime;
extern unsigned short g_7f4c04;
extern int g_7f4c08;
extern short g_7f4c0c;
extern unsigned char g_773d75;
extern float g_66414c;
extern char g_67eb84[];


void __cdecl cm_SendLogAction(char* s);
void __cdecl cm_SendTraceEnd(char* s);
int __cdecl gm_GetTypeProductValue(int k);
void __cdecl cm_RequestMoveCredits(int a, int b, char c, int n);
void __cdecl cm_SendCopyEntityData(char* msg);

int __cdecl ai_RunUpgradeZunft(char* a1, char* a2, char* a3)
{
	char* resolved;
	char* other;
	char msg[0xf8];

	if (*a2 == 1 && *a3 == 0x12 && *(unsigned int*) (a3 + 8) > 0) {
		gm_ResolveEntityById(0, (void**) (&resolved), 0, *(int*) (a2 + 4));
		if (resolved == 0) {
			return 0;
		}
		cm_RequestMoveCredits(*(int*) (resolved + 2), *(int*) (a1 + 4), (*(char*)&g_773d75), *(int*) (a3 + 8));
		return 0x39;
	}
	if (*a2 == 4 && *a3 == 1) {
		gm_ResolveEntityById((void**) (&other), 0, 0, *(int*) (a2 + 0xc));
		if (other == 0) {
			return 0;
		}
		gm_ResolveEntityById(0, (void**) (&resolved), 0, *(int*) (a3 + 4));
		if (resolved == 0) {
			return 0;
		}
		memset(msg, 0, sizeof(msg));
		msg[4] = 0x1e;
		*(int*) (msg + 8) = *(int*) (a1 + 4);
		*(int*) (msg + 0xc) = *(int*) (a2 + 0xc);
		*(int*) (msg + 0x28) = (*(int*)&gm_GameTime);
		*(int*) (msg + 0x2c) = (*(int*)&g_7f4c04);
		msg[0x36] = 1;
		*(int*) (msg + 0x30) = g_7f4c08;
		*(short*) (msg + 0x34) = g_7f4c0c;
		*(int*) (msg + 0x58) = *(int*) (a2 + 0xc);
		cm_SendLogAction(g_67eb84);
		cm_RequestMoveCredits(-1, *(int*) (resolved + 2), (*(char*)&g_773d75), (int) (gm_GetTypeProductValue(*(int*) (a2 + 4)) * 0.3f));
		cm_SendCopyEntityData(msg);
		cm_SendTraceEnd(g_67eb84);
		return 0x39;
	}
	return 0;
}
