


#include <string.h>

#include "Develop/client_types.h"
extern pos14_7f4c00 gm_GameTime;
extern unsigned short g_7f4c04;
extern int g_7f4c08;
extern short g_7f4c0c;
extern unsigned char g_773d75;
extern float g_66414c;
extern char g_67e968[];

void __cdecl cm_SendLogAction(char* s);
void __cdecl cm_SendTraceEnd(char* s);
int __cdecl gm_GetTypeProductValue(int k);
void __cdecl cm_RequestMoveCredits(int a, int b, char c, int n);
void __cdecl cm_SendCopyEntityData(char* msg);
int __cdecl amt_ExecGebaeudeBauen(char* a1, char* a2, char* a3);

int __cdecl ai_RunWohnsitzBauen(char* kontext, char* ziel, char* aktion)
{
	char msg[0xf8];

	if (*aktion == 4) {
		memset(msg, 0, sizeof(msg));
		msg[4] = 0x1e;
		*(int*) (msg + 8) = *(int*) (kontext + 4);
		*(int*) (msg + 0xc) = *(int*) (aktion + 4);
		msg[0x36] = 1;
		*(int*) (msg + 0x28) = (*(int*)&gm_GameTime);
		*(int*) (msg + 0x2c) = (*(int*)&g_7f4c04);
		*(int*) (msg + 0x30) = g_7f4c08;
		*(short*) (msg + 0x34) = g_7f4c0c;
		*(int*) (msg + 0x58) = *(int*) (aktion + 4);
		cm_SendLogAction(g_67e968);
		cm_RequestMoveCredits(-1, *(int*) (kontext + 4), (*(char*)&g_773d75), (int) (gm_GetTypeProductValue(*(int*) (ziel + 4)) * 0.3f));
		cm_SendCopyEntityData(msg);
		cm_SendTraceEnd(g_67e968);
		return 0x11;
	}
	return amt_ExecGebaeudeBauen(kontext, ziel, aktion) ? 0x11 : 0;
}
