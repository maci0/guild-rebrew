


#include <stdlib.h>
#include <windows.h>

// SIZE 0x21c
#include "Develop/DieGildeAddOn/game/entity_record.h"







// SIZE 0x2f4
typedef struct {
	char pad0[0x48];
	signed char count;
	char pad49[0x2f4 - 0x49];
} Variant;

#pragma pack(push, 1)
// SIZE 0x6
typedef struct {
	char pad0[2];
	int id;
} Unit;

// SIZE 0x61
typedef struct {
	char pad0[0x5d];
	int home;
} Player;
#pragma pack(pop)

#include "Develop/DieGildeAddOn/game/game_data.h"
extern int g_7747e8;

extern char gm_TownTable[];
extern unsigned char gm_PlayerCount;
extern unsigned char gm_ClientModeFlags;
extern unsigned char gm_ActiveTownIndex;

void __cdecl gm_InitCityOfficialsAndCitizens(int);
void __cdecl gm_InitCivicBuildings(int);
void __cdecl cm_DistributeStartingWares(int, int, int*);
void __cdecl gm_InitStartingEntitiesAndRelations(void);
Player* __cdecl gm_GetGuildHall(int);
Unit* __cdecl gm_QueryEntities(int, int, int, int, int);
void __cdecl cm_RequestTransferCurrencyNoKill(int, int, char, int);

/* ADDRESS: GOLDDE 0x004ff5f0 */
int __cdecl gm_InitCityAndTradeState(int variant)
{
	int wares[8];
	int* p;
	int i;
	int j;
	int k;
	Player* pl;
	Unit* u;

	if (nt_ClientSocket == -1) {
		srand(timeGetTime());
	}
	gm_InitCityOfficialsAndCitizens(0);
	if (g_7747e8 != 0) {
		for (i = 0; i < 768; i++) {
			if (((ENTITY_RECORD*)gm_EntitySlotTable)[i].entity_state == 6) {
				gm_InitCivicBuildings(i);
				break;
			}
		}
	}
	k = variant;
	if (((Variant*)gm_TownTable)[k].count - gm_PlayerCount > 0) {
		wares[0] = 0x18;
		wares[1] = 0x27;
		wares[2] = 0x33;
		wares[3] = 0x3f;
		wares[4] = 0x45;
		wares[5] = 0x4b;
		wares[6] = 0x12;
		wares[7] = 6;
		if ((*(signed char*)&gm_ClientModeFlags) & 0x80) {
			p = wares;
			variant = sizeof(wares);
			/*
			 * The reference zero-fills with the hand-written block-fill
			 * prelude no msvc6 C spelling emits (docs/codegen-walls.md 6b).
			 */
			__asm {
				mov edi, p
				mov ebx, variant
				xor eax, eax
				lea ecx, [edi+edi*2]
				and ecx, 3
				sub ebx, ecx
				jle short L1
				rep stosb
				mov ecx, ebx
				and ebx, 3
				shr ecx, 2
				rep stosd
			L1:
				add ecx, ebx
				rep stosb
			}
			wares[0] = 0x12;
		} else {
			for (i = 0; i < 768; i++) {
				if (((ENTITY_RECORD*)gm_EntitySlotTable)[i].entity_state == 6 || ((ENTITY_RECORD*)gm_EntitySlotTable)[i].entity_state == 7) {
					for (j = 0; j < 8; j++) {
						if (((ENTITY_RECORD*)gm_EntitySlotTable)[i].unk_164 == wares[j]) {
							wares[j] = 0;
							break;
						}
					}
				}
			}
		}
		cm_DistributeStartingWares(((Variant*)gm_TownTable)[k].count - gm_PlayerCount, 8, wares);
	}
	gm_InitStartingEntitiesAndRelations();
	pl = gm_GetGuildHall(1);
	if (pl != 0) {
		u = gm_QueryEntities(pl->home, 2, 6, 0, 0x115);
		if (u != 0) {
			cm_RequestTransferCurrencyNoKill(u->id, -1, (*(char*)&gm_ActiveTownIndex), 0x75300);
		}
	}
	return 1;
}
