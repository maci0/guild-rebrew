

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

#include "Develop/DieGildeAddOn/game/game_data.h"
extern unsigned short* g_772e9c;

char* __cdecl gm_LookupEntityRecordIn32SlotTable(int);
ent2c* __cdecl gm_FindOrCreateEntitySlot(char*, char*);
int __cdecl cm_GetCommandStatus(int);
void __cdecl cut_AssignCombatUnitOrder(char*, char*);

void __cdecl cut_AssignIdleCombatOrders(char* team)
{
	char* teamSlot;
	int* base;
	int i;
	char* unit;
	ent2c* unitSlot;

	teamSlot = 0;
	for (i = 0; i < ((unsigned char*)g_772eb4)[0x30]; i++) {
		if (*(int*) (((unsigned char*)g_772eb4) + 0x34 + i * 4) == *(int*) (team + 4)) {
			teamSlot = g_9b0e20 + i * 0x35c;
			break;
		}
	}
	if (team == ((char*)g_772e9c))
		base = (int*) (((unsigned char*)g_772eb4) + 0xc0);
	else
		base = (int*) (((unsigned char*)g_772eb4) + 0x80);
	for (i = 0; i < 16; i++) {
		if (base[i] == -1)
			continue;
		unit = gm_LookupEntityRecordIn32SlotTable(base[i]);
		if (unit == 0)
			continue;
		unitSlot = gm_FindOrCreateEntitySlot(teamSlot, unit);
		if (unitSlot->f8 == 1 || cm_GetCommandStatus(unitSlot->f8) != 0) {
			unitSlot->f8 = -1;
			if (unitSlot->f4 == 0 && *(int*) (*(char**) (*(char**) (unit + 0x184) + 0x34) + 0x218) != 1)
				cut_AssignCombatUnitOrder(teamSlot, unit);
		}
	}
}
