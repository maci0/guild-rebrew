#include "Develop/DieGildeAddOn/game/spiel.h"
#include "Develop/DieGildeAddOn/game/building_prototype.h"

#include <stdio.h>

#pragma pack(push, 1)
// SIZE 0x29
typedef struct {
	unsigned char office;
	char pad1[4];
	char name[0x22];
	unsigned short owner;
} Bld47de;

// SIZE 0x24d
typedef struct {
	unsigned char kind;
	char pad1[0x24c];
} Office47de;
#pragma pack(pop)

// SIZE 0x21c
typedef struct {
	char pad0[0x21c];
} Ent47de;

// SIZE 0x1bc
typedef struct {
	unsigned short id;
	char pad2[0x2e];
	char name[0x13c];
	Bld47de* bld;
	char pad170[0x44];
	unsigned char flags;
	char pad1b5[3];
	int budget;
} Master47de;

#include "Develop/DieGildeAddOn/game/game_timestamp.h"
// SIZE 0xe








#include "client_types.h"
extern pos14_7f4c00 gm_GameTime;
extern char* g_100e748;
extern char g_7f4ca0[];
extern char* g_7746c4;
extern unsigned char* g_7746c8;
extern LightState g_100dc20;
extern Master47de* g_100dc28;
extern Ent47de* g_100dc2c;
extern int g_100dc30;
extern unsigned char* lpGebaeudePROT;

int __cdecl gm_CanEvaluateMaster(char*);
int __cdecl gm_AccumulateTyped2(void*);

void __cdecl ai_RunResourceMaster(Master47de*);
void __cdecl ai_CalcMeisterWache(Master47de*);
void __cdecl ai_CalcMeisterDiebe(Master47de*);
void __cdecl ai_CalcMeisterRaeuber(Master47de*);
void __cdecl ai_CalcMeisterBank(Master47de*);
void __cdecl ai_CalcMeisterLager(Master47de*);
void __cdecl ai_PlanMasterProduction(Master47de*);
void __cdecl ai_RunWorkshopMaster(Master47de*);
void __cdecl ai_UpdateMeisterBuilding(Master47de*);
void __cdecl ai_StartMeisterProduction(Master47de*);

void __cdecl ai_EvaluateMeister(Master47de* m)
{
	char buf[0x100];
	unsigned char k;

	if ((*(GAME_TIMESTAMP*)&gm_GameTime).hour < 6 || ((*(GAME_TIMESTAMP*)&gm_GameTime).hour == 6 && (*(GAME_TIMESTAMP*)&gm_GameTime).minute < 30)) {
		return;
	}
	if (gm_CanEvaluateMaster((char*) m) == 0) {
		return;
	}
	if (!(m->flags & 1)) {
		return;
	}
	if (m == (Master47de*)g_100e748) {
		sprintf(buf, "Evaluation von Meister %s in %s beginnt...", ((Master47de*)g_100e748)->name, ((Master47de*)g_100e748)->bld->name);
		sprintf(buf, "Aktuelles Budget: %li", ((Master47de*)g_100e748)->budget);
		sprintf(buf, "Tats\xe4" "chlich verf\xfcgbares Budget: %li", gm_AccumulateTyped2(&((Ent47de*)g_7f4ca0)[m->bld->owner]));
	}
	if (m->bld->owner == m->id) {
		m->budget = gm_AccumulateTyped2(m);
	}
	if (m->bld == ((Bld47de*)g_7746c4) || m->bld == ((Bld47de*)g_7746c8)) {
		g_100dc20.owner = (char*) m->bld;
		g_100dc28 = m;
		g_100dc2c = &((Ent47de*)g_7f4ca0)[m->bld->owner];
		g_100dc30 = m->budget;
	}
	if (gm_GetBuildingTypeCategory(m->bld->office) == 1 || gm_GetBuildingTypeCategory(m->bld->office) == 4) {
		k = ((BUILDING_PROTOTYPE*)lpGebaeudePROT)[m->bld->office].category;
		if (k == 0xe || k == 8 || k == 0x20) {
			ai_StartMeisterProduction(m);
		} else if (k == 0x1d) {
			ai_PlanMasterProduction(m);
		} else if (k == 0x1f) {
			ai_RunWorkshopMaster(m);
		} else {
			ai_UpdateMeisterBuilding(m);
		}
	} else if (gm_GetBuildingTypeCategory(m->bld->office) == 2) {
		ai_RunResourceMaster(m);
	} else {
		k = ((BUILDING_PROTOTYPE*)lpGebaeudePROT)[m->bld->office].category;
		if (k == 0x13) {
			ai_CalcMeisterWache(m);
		} else if (k == 4) {
			ai_CalcMeisterDiebe(m);
		} else if (k == 0x10) {
			ai_CalcMeisterRaeuber(m);
		} else if (k == 5) {
			ai_CalcMeisterBank(m);
		} else if (k == 9) {
			ai_CalcMeisterLager(m);
		}
	}
}
