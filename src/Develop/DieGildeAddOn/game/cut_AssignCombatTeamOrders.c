#include "Develop/DieGildeAddOn/game/game_data.h"
extern unsigned short* cut_CombatDefenderEntity;

float* __cdecl cut_GetCombatActionWeights(char*);
char* __cdecl gm_LookupEntityRecordIn32SlotTable(int);
float __cdecl cut_ScoreCombatUnitMode(void*, unsigned int);
float __cdecl cut_RandFloat(void);
double __cdecl gm_RandomFloat01(void);
void __cdecl cut_AssignCombatUnitOrder(char*, char*);

/* ADDRESS: GOLDTL 0x004d3fe0 */
void __cdecl cut_AssignCombatTeamOrders(char* teamActor)
{
	char* rec;
	char* base;
	char* e;
	float* w;
	float best;
	float rnd;
	int n;
	float f;
	char* ent[16];
	int i;
	int k;
	int auswahl;
	int chosen;

	chosen = 0;
	n = 0;
	auswahl = 0;
	rec = 0;
	w = cut_GetCombatActionWeights(teamActor);
	for (i = 0; i < ((unsigned char*) g_772eb4)[0x30]; i++) {
		if (*(int*) (g_772eb4 + 0x34 + i * 4) == *(int*) (teamActor + 4)) {
			rec = cut_ParticipantSlots + i * 0x35c;
			break;
		}
	}
	if (teamActor == (char*) cut_CombatDefenderEntity) {
		base = g_772eb4 + 0xc0;
	} else {
		base = g_772eb4 + 0x80;
	}
	for (i = 0; i < 16; i++) {
		if (*(int*) (base + i * 4) != -1) {
			ent[i] = gm_LookupEntityRecordIn32SlotTable(*(int*) (base + i * 4));
			n++;
		} else {
			ent[i] = 0;
		}
	}
	if (n > 0) {
		k = n;
		do {
			rnd = gm_RandomFloat01();
			for (i = 0; i < 6; i++) {
				if (rnd <= w[i]) {
					auswahl = i;
					break;
				}
			}
			best = -1.0f;
			for (i = 0; i < 16; i++) {
				if (ent[i] != 0) {
					f = cut_ScoreCombatUnitMode(ent[i], auswahl);
					if (f > best) {
						best = f;
						chosen = i;
					}
				}
			}
			e = ent[chosen];
			if (e[0x1c4] == 0 || cut_RandFloat() > 0.25) {
				e[0x1c4] = (char) auswahl;
				ent[chosen] = 0;
			}
			k--;
		} while (k != 0);
	}
	for (i = 0; i < 16; i++) {
		if (*(int*) (base + i * 4) != -1) {
			cut_AssignCombatUnitOrder(rec, gm_LookupEntityRecordIn32SlotTable(*(int*) (base + i * 4)));
		}
	}
}
