


#include <string.h>

#include "Develop/client_types.h"
extern pos14_7f4c00 gm_GameTime;
extern unsigned short gm_GameTimeHour;
extern int gm_GameTimeSliceDword;
extern short gm_GameTimeTailWord;
extern unsigned char gm_ActiveTownIndex;
extern float g_66414c;
extern char g_67eb38[];
extern char g_67eb2c[];
extern char* gm_CityEntity;
extern float g_100a0a0;
extern float g_100a0c0[];

char* __cdecl gm_FindPublicTreasury(int k);
void __cdecl cm_SendLogAction(char* s);
void __cdecl cm_SendTraceEnd(char* s);
int __cdecl gm_GetTypeProductValue(int k);
void __cdecl cm_RequestMoveCredits(int a, int b, char c, int n);
void __cdecl cm_SendCopyEntityData(char* msg);
int __cdecl amt_ExecGebaeudeBauen(char* a1, char* a2, char* a3);

/* ADDRESS: GOLDDE 0x0048cf00 */
int __cdecl ai_RunBaumeister(char* entity, char* a2, char* a3)
{
	char msg[0xf8];
	char* b;

	b = gm_FindPublicTreasury(1);
	if (b == 0 || (unsigned char) entity[0x166] != 0xa) {
		goto out0;
	}
	if (*a3 == 4) {
		memset(msg, 0, sizeof(msg));
		msg[4] = 0x1e;
		*(int*) (msg + 8) = *(int*) (entity + 4);
		*(int*) (msg + 0xc) = *(int*) (a3 + 4);
		msg[0x36] = 1;
		*(int*) (msg + 0x28) = (*(int*)&gm_GameTime);
		*(int*) (msg + 0x2c) = (*(int*)&gm_GameTimeHour);
		*(int*) (msg + 0x30) = gm_GameTimeSliceDword;
		*(short*) (msg + 0x34) = gm_GameTimeTailWord;
		*(int*) (msg + 0x58) = *(int*) (a3 + 4);
		cm_SendLogAction(g_67eb38);
		cm_RequestMoveCredits(-1, *(int*) (b + 2), (*(char*)&gm_ActiveTownIndex), (int) (gm_GetTypeProductValue(*(int*) (a2 + 4)) * 0.3f));
		cm_SendCopyEntityData(msg);
		cm_SendTraceEnd(g_67eb38);
		if (*(int*) (a2 + 0x10) > 0 && *(int*) (a2 + 0x10) < 4) {
			g_100a0c0[*(int*) (a2 + 0x10) * 2] = g_100a0a0 + g_100a0a0;
		}
		return 0x2f;
	} else {
		cm_SendLogAction(g_67eb2c);
		if (amt_ExecGebaeudeBauen(gm_CityEntity, a2, a3)) {
			cm_RequestMoveCredits(-1, *(int*) (b + 2), (*(char*)&gm_ActiveTownIndex), gm_GetTypeProductValue(*(int*) (a2 + 4)));
			cm_SendTraceEnd(g_67eb2c);
			if (*(int*) (a2 + 0x10) > 0 && *(int*) (a2 + 0x10) < 4) {
				g_100a0c0[*(int*) (a2 + 0x10) * 2] = g_100a0a0 + g_100a0a0;
			}
			return 0x2f;
		} else {
			cm_SendTraceEnd(g_67eb2c);
			return 0;
		}
	}
out0:
	return 0;
}
