


#include "Develop/DieGildeAddOn/game/game_player.h"
#include "Develop/DieGildeAddOn/game/entity_record.h"
extern char* g_7746cc;

char* __cdecl he_StartHandlungSearch(int, int, int);
char* __cdecl he_fn_Handlung(void);
char* __cdecl gm_StartFilteredEntitySearch(int, int, int);
char* __cdecl gm_AddObjekt(void);
char* __cdecl gm_FindNextFilteredEntity(void);
#include "Develop/Units/Error/error_message.h"
char* __cdecl fcn_00502cd0(int, int, int, int);
void __cdecl fcn_00526920(char*, int, char*);

void __cdecl lc_PlayerInJail(void)
{
	char* p;
	char* e;
	char* d;

	for (p = he_StartHandlungSearch(1, 0, 0x3d); p != 0; p = he_fn_Handlung()) {
		if (*(int*) (p + 0xac) == ((ENTITY_RECORD_VIEW *)&((ENTITY_RECORD_VIEW *)g_7f4ca0)[g_774970])->entity_id) {
			for (e = gm_StartFilteredEntitySearch(1, 5, 4); e != 0; e = gm_FindNextFilteredEntity()) {
				if (*(int*) (e + 0x65) == ((ENTITY_RECORD_VIEW *)&((ENTITY_RECORD_VIEW *)g_7f4ca0)[g_774970])->entity_id) {
					d = fcn_00502cd0(*(int*) (e + 0x5d), 1, 0, 0x65);
					if (d != 0 && g_7746cc != d) {
						fcn_00526920(e, *(int*) (d + 2), "");
					}
					return;
				}
			}
			ReportClientMessage("lc_PlayerInJail(): Could not find ob_DIEBESGILDE_GEFAENGNIS...");
			return;
		}
	}
	e = gm_StartFilteredEntitySearch(1, 5, 6);
	if (e == 0) {
		ReportClientMessage("lc_PlayerInJail(): Could not find a jail...");
		return;
	}
	d = fcn_00502cd0(*(int*) (e + 0x5d), 1, 0, 0xba);
	if (d != 0 && g_7746cc != d) {
		fcn_00526920(e, *(int*) (d + 2), "");
	}
}
