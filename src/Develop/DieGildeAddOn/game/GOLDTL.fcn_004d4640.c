extern int g_772ea4;
#include "client_dialog_state.h"

int __cdecl main_RunFrameLoop(void*, int);
void __cdecl d3_UpdateCameraAtScreenEdges(void);
char* __cdecl gm_LookupEntityRecordIn32SlotTable(int);
int __cdecl fcn_004cf180(void);
int __cdecl d3_UpdateMineExplosions(void);
void __cdecl cut_UpdateCombatEffects(void);

struct BATTLE_UNIT_SLOT {
	int id;
	int active;
	char pad8[0x24];
};
// SIZE 0x2c


/* ADDRESS: GOLDTL 0x004d4640 */
void __cdecl cut_RunBattleFrameLoop(char* context)
{
	struct BATTLE_UNIT_SLOT* s;
	char* r;
	int busy;
	int i;

	while (g_772ea4 == 0 && main_RunFrameLoop(cut_RunBattleFrameLoop, 0x7d6c6) != 0) {
		d3_UpdateCameraAtScreenEdges();
		busy = 0;
		for (i = 0; i < 16; i++) {
			s = (struct BATTLE_UNIT_SLOT*) (context + 0x94) + i;
			if (s->active != 0 && s->id != -1) {
				r = gm_LookupEntityRecordIn32SlotTable(s->id);
				if (r != 0 && *(char**) (r + 0x184) != 0
				    && *(int*) (*(char**) (r + 0x184) + 0x128) != 0) {
					busy = 1;
					break;
				}
			}
		}
		if (fcn_004cf180() != 0)
			busy = 1;
		if (d3_UpdateMineExplosions() != 0)
			busy = 1;
		cut_UpdateCombatEffects();
		if (busy == 0)
			g_774654 = 1;
	}
}
