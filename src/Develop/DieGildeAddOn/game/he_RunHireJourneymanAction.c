#include "Develop/DieGildeAddOn/game/spiel.h"



#include "Develop/client_types.h"
extern pos14_7f4c00 gm_GameTime;

void __cdecl gm_AddTime(pos14_7f4c00*, int, int, int);

void __cdecl he_FreeAction(char*);
int __cdecl cm_GetCommandStatus(int);
char* __cdecl cm_GetCommandResult(int);
void __cdecl ch_StartMovement(int, int, int, int, int, char*);
void __cdecl io_FormatTextBuffer(char*, int, ...);
void __cdecl he_MessageBoxQuickjump(int, int, char*, int, int, int, int, int, char*);

void __cdecl he_RunHireJourneymanAction(char* action)
{
	int target_id;
	int caller_id;
	char buf[0x200];
	char* journeyman;
	int role_str;

	caller_id = 0;
	target_id = 0;
	*(pos14_7f4c00*) (action + 0x52) = gm_GameTime;
	gm_AddTime((pos14_7f4c00*) (action + 0x52), 0, 4, 0);
	gm_ResolveEntityById((void**) (&target_id), 0, 0, *(int*) (action + 0xb0));
	gm_ResolveEntityById(0, 0, (void**) (&caller_id), *(int*) (action + 0xac));
	if (*(int*) (action + 0x70) == -2 || target_id == 0) {
		he_FreeAction(action);
	}
	if (*(int*) (action + 0x70) == 0 && cm_GetCommandStatus(*(int*) (action + 0xbc)) != 0) {
		journeyman = cm_GetCommandResult(*(int*) (action + 0xbc));
		if (journeyman != 0) {
			role_str = (journeyman[9] != 0 ? 0x230 : 0x20d) + *(unsigned char*) (journeyman + 0x165);
			ch_StartMovement(*(int*) (journeyman + 4), *(int*) (action + 0xb0), *(int*) (action + 0xb4), 0, 0, "RndGeselle");
			io_FormatTextBuffer(buf, *(unsigned short*) (action + 0xb8), *(unsigned short*) journeyman, role_str, target_id);
			he_MessageBoxQuickjump(*(int*) (action + 0xac), *(int*) (action + 0xac), buf, 0, 0x5ec, *(int*) (action + 0xb0), *(int*) (action + 0xb4), 0,
			    "_NACHRICHTEN_HS_00");
		}
		he_FreeAction(action);
	}
}
