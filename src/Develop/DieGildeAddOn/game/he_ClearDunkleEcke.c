


// SIZE 0x14
typedef struct {
	int tag;
	int a;
	int id;
	int b;
	int c;
} Msg;

#include "Develop/client_types.h"
extern pos14_7f4c00 gm_GameTime;
extern char g_6a58ac[];

char* __cdecl gm_StartFilteredEntitySearch(int, ...);
char* __cdecl gm_AddObjekt(void);
char* __cdecl gm_FindNextFilteredEntity(void);
char* __cdecl gm_QueryEntities(int, int, int, ...);
void __cdecl cm_SendLogAction(char* s);
void __cdecl cm_SendTraceEnd(char* s);
void __cdecl cm_RequestElectionOrTrade(Msg* msg);

void __cdecl he_ClearDunkleEcke(void)
{
	char* e;
	char* w;

	for (e = gm_StartFilteredEntitySearch(1, 5, 0x16); e != 0; e = gm_FindNextFilteredEntity()) {
		w = gm_QueryEntities(*(int*) (e + 0x5d), 1, 0, 0x120);
		if (w == 0) {
			continue;
		}
		w = gm_QueryEntities(*(int*) (w + 0x14), 1, 0, 0x12c);
		if (w == 0) {
			continue;
		}
		if ((*(int*)&gm_GameTime) - *(int*) (w + 0x28) > 1) {
			Msg msg;

			msg.tag = 0x636c6572;
			msg.id = *(int*) (e + 1);
			msg.a = -1;
			msg.b = -1;
			cm_SendLogAction(g_6a58ac);
			cm_RequestElectionOrTrade(&msg);
			cm_SendTraceEnd(g_6a58ac);
		}
	}
}
