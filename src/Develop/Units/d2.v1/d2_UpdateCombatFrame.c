


typedef struct {
	int id;
	int f4;
	int f8;
	char fc;
	char padd[3];
	char name[0x10];
	int f20;
	int f24;
	int f28;
} ent2c;
// SIZE 0x2c

#include "Develop/DieGildeAddOn/game/cutscene_clock.h"
extern int g_68bfbc;
extern int g_68b7a4;
extern int g_772ea4;
extern int g_100f1dc;
#include "Develop/DieGildeAddOn/game/game_data.h"
extern int g_68b7a8;
extern unsigned short* g_772f24;
#include "Develop/Units/d2.v1/client_dialog_state.h"

#include "Develop/Units/d2.v1/d2_gui.h"
void __cdecl d3_UpdateCameraAtScreenEdges(void);
void __cdecl d2_UpdateCombatUnitHud(void);
void __cdecl cut_UpdateCombatHoverTarget(void);
void __cdecl d2_SelectClickedCombatWorker(void);
void __cdecl cut_UpdateCombatSelectionBox(char*);
void __cdecl cut_UpdateCombatEffects(void);
void __cdecl d2_UpdateEntityOverlays(char*);
void __cdecl cut_UpdateActiveBombs(void);
void __cdecl d3_UpdateMineExplosions(void);
ent2c* __cdecl gm_FindOrCreateEntitySlot(char*, char*);
int __cdecl cm_SendUpdateCutsceneEntitySlot(int, ent2c*);

void __cdecl d2_UpdateCombatFrame(char* rec)
{
	ent2c l;

	d2_SetElementValue(g_68b7a4, 0, g_68bfbc, cut_ClockDeadline - cut_CurrentTick + 1);
	d3_UpdateCameraAtScreenEdges();
	d2_UpdateCombatUnitHud();
	cut_UpdateCombatHoverTarget();
	d2_SelectClickedCombatWorker();
	cut_UpdateCombatSelectionBox(rec);
	cut_UpdateCombatEffects();
	d2_UpdateEntityOverlays(rec);
	cut_UpdateActiveBombs();
	d3_UpdateMineExplosions();
	if (cut_ClockExpired != 0 || g_772ea4 != 0) {
		g_774654 = 1;
		return;
	}
	if (g_100f1dc == -1 || d2_CurrentElementId != g_68b7a8)
		return;
	l = *gm_FindOrCreateEntitySlot(rec, ((char*)g_772f24));
	l.id = *(int*) (((char*)g_772f24) + 4);
	l.f4 = 5;
	cm_SendUpdateCutsceneEntitySlot(*(int*) (rec + 0x10), &l);
}
