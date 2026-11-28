


#include "Develop/DieGildeAddOn/game/game_player.h"
#include "Develop/DieGildeAddOn/game/entity_record.h"
extern char* sv_SelectedBuilding;

char* __cdecl he_StartHandlungSearch(int, int, int);
char* __cdecl he_fn_Handlung(void);
char* __cdecl gm_StartFilteredEntitySearch(int, int, int);
char* __cdecl gm_AddObjekt(void);
char* __cdecl gm_FindNextFilteredEntity(void);
#include "Develop/Units/Error/error_message.h"
char* __cdecl gm_QueryEntities(int, int, int, int);
void __cdecl d2_EnterBuildingObjekt(char*, int, char*);

/* ADDRESS: GOLDDE 0x0057fc10 */
void __cdecl lc_PlayerInJail(void)
{
	char* p;
	char* e;
	char* d;

	for (p = he_StartHandlungSearch(1, 0, 0x3d); p != 0; p = he_fn_Handlung()) {
		if (*(int*) (p + 0xac) == ((ENTITY_RECORD_VIEW *)&((ENTITY_RECORD_VIEW *)gm_EntitySlotTable)[gm_LocalPlayerSlot])->entity_id) {
			for (e = gm_StartFilteredEntitySearch(1, 5, 4); e != 0; e = gm_FindNextFilteredEntity()) {
				if (*(int*) (e + 0x65) == ((ENTITY_RECORD_VIEW *)&((ENTITY_RECORD_VIEW *)gm_EntitySlotTable)[gm_LocalPlayerSlot])->entity_id) {
					d = gm_QueryEntities(*(int*) (e + 0x5d), 1, 0, 0x65);
					if (d != 0 && sv_SelectedBuilding != d) {
						d2_EnterBuildingObjekt(e, *(int*) (d + 2), "");
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
	d = gm_QueryEntities(*(int*) (e + 0x5d), 1, 0, 0xba);
	if (d != 0 && sv_SelectedBuilding != d) {
		d2_EnterBuildingObjekt(e, *(int*) (d + 2), "");
	}
}
