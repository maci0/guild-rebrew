


#include <string.h>

#include "Develop/client_types.h"
extern pos14_7f4c00 gm_GameTime;
extern unsigned short gm_GameTimeHour;
extern int gm_GameTimeSliceDword;
extern short gm_GameTimeTailWord;
extern unsigned char gm_ActiveTownIndex;
extern float g_66414c;
extern char g_67e968[];

char* __cdecl he_StartHandlungSearch(int, int, int);
void __cdecl gm_BuyBuilding(int, int, int, char*, int);
void __cdecl cm_SendLogAction(char* s);
void __cdecl cm_SendTraceEnd(char* s);
int __cdecl gm_GetTypeProductValue(int k);
void __cdecl cm_RequestMoveCredits(int a, int b, char c, int n);
void __cdecl cm_SendCopyEntityData(char* msg);
int __cdecl amt_ExecGebaeudeBauen(char* actor, char* building_spec, char* target_arg);
void __cdecl cm_RequestChangeBits(int, int, int, int, int);

int __cdecl ai_RunBetriebBauen(char* actor, char* building_spec, char* target_arg)
{
	char msg[0xf8];
	char* owner_building;

	if (*building_spec == 4 && *target_arg == 8) {
		owner_building = he_StartHandlungSearch(1, 1, *(int*) (target_arg + 4));
		if (owner_building == 0) {
			return 0;
		}
		gm_BuyBuilding(*(int*) (building_spec + 4), *(int*) (actor + 4), *(int*) (owner_building + 0xb0), owner_building, 1);
		return 0x13;
	}
	if (*target_arg == 4) {
		memset(msg, 0, sizeof(msg));
		msg[4] = 0x1e;
		*(int*) (msg + 8) = *(int*) (actor + 4);
		*(int*) (msg + 0xc) = *(int*) (target_arg + 4);
		msg[0x36] = 1;
		*(int*) (msg + 0x28) = (*(int*)&gm_GameTime);
		*(int*) (msg + 0x2c) = (*(int*)&gm_GameTimeHour);
		*(int*) (msg + 0x30) = gm_GameTimeSliceDword;
		*(short*) (msg + 0x34) = gm_GameTimeTailWord;
		*(int*) (msg + 0x58) = *(int*) (target_arg + 4);
		cm_SendLogAction(g_67e968);
		cm_RequestMoveCredits(-1, *(int*) (actor + 4), (*(char*)&gm_ActiveTownIndex), (int) (gm_GetTypeProductValue(*(int*) (building_spec + 4)) * 0.3f));
		cm_SendCopyEntityData(msg);
		cm_SendTraceEnd(g_67e968);
		return 0x13;
	}
	if (amt_ExecGebaeudeBauen(actor, building_spec, target_arg) != 0) {
		cm_RequestChangeBits(*(int*) (actor + 4), 0x1c8, 4, 0x1000000, 0);
		return 0x13;
	}
	return 0;
}
