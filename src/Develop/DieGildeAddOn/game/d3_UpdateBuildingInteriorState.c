#include "Develop/DieGildeAddOn/game/object_prototype.h"
#include "Develop/DieGildeAddOn/game/building_prototype.h"


extern unsigned short* g_7e431c;
typedef struct
{
	char type;
	char pad1[64];
} Rec65;
// SIZE 0x41

extern char* lpObjektePROT;
extern unsigned char* d2_InteriorBuilding;
#include "Develop/DieGildeAddOn/game/game_player.h"
#include "Develop/DieGildeAddOn/game/game_data.h"
extern int d2_EnteredBuildingObjekt;
extern unsigned char* d2_EnteredBuildingEntity;
extern int g_7746b8;
extern unsigned char* lpGebaeudePROT;

int __cdecl gm_GetEntityUiFlags(int, unsigned char*, unsigned short*, int);
int __cdecl gm_QueryEntities(int, int, int, int, int);
void __cdecl d2_EnterObjektInterior(int);
void __cdecl d3_UpdateBuildingView(unsigned char*, int);
void __cdecl d3_SetupInteriorScene(unsigned char*, int);
void __cdecl d2_OpenContactEinkaufPanel(unsigned char*);

void __cdecl d3_UpdateBuildingInteriorState(void)
{
	int x;
	unsigned char* e;
	char* r;

	if (g_7e431c != 0) {
		r = (char *)&((OBJECT_PROTOTYPE *)lpObjektePROT)[*g_7e431c].kind;
		if ((*r == 6 || *r == 2) && (gm_GetEntityUiFlags(gm_LocalPlayerSlot, d2_InteriorBuilding, g_7e431c, 0) & 0x4000)) {
			x = gm_QueryEntities(*(int*) (d2_InteriorBuilding + 0x5d), 2, 6, 0, 0xfd);
			d2_EnterObjektInterior((int) g_7e431c);
			d3_UpdateBuildingView(d2_InteriorBuilding, 0xfd);
			d3_SetupInteriorScene(d2_InteriorBuilding, x);
			g_774658 = g_774650;
		}
	}
	if (d2_InsideBuildingActive != 0 && d2_EnteredBuildingObjekt != 0 && d2_EnteredBuildingEntity == d2_InteriorBuilding) {
		x = gm_QueryEntities(*(int*) (d2_InteriorBuilding + 0x5d), 2, 6, 0, 0xfd);
		if (d2_EnteredBuildingObjekt != x) {
			d2_EnterObjektInterior(d2_EnteredBuildingObjekt);
			d3_UpdateBuildingView(d2_InteriorBuilding, 0xfd);
			d3_SetupInteriorScene(d2_InteriorBuilding, x);
		} else {
			d2_InsideBuildingActive = 0;
			d2_EnteredBuildingObjekt = 0;
			d2_EnteredBuildingEntity = 0;
		}
	}
	if (g_7746b8 != 0 && g_7746f0 == 0) {
		x = gm_QueryEntities(*(int*) (d2_InteriorBuilding + 0x5d), 2, 6, 0, 0xfd);
		d2_EnterObjektInterior(g_7746b8);
		d3_UpdateBuildingView(d2_InteriorBuilding, 0xfd);
		d3_SetupInteriorScene(d2_InteriorBuilding, x);
	}
	e = d2_InteriorBuilding;
	r = (char*)&((BUILDING_PROTOTYPE*)lpGebaeudePROT)[*e];
	if (*e == 0x20 || *e == 0x1f || *e == 0x1e || ((char)((BUILDING_PROTOTYPE*)r)->category) == 0x1f || ((char)((BUILDING_PROTOTYPE*)r)->category) == 0x1d) {
		d2_OpenContactEinkaufPanel(e);
	}
}
