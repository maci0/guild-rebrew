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
extern unsigned char* g_7746c8;
#include "Develop/DieGildeAddOn/game/game_player.h"
#include "Develop/DieGildeAddOn/game/game_data.h"
extern int g_7e2708;
extern unsigned char* g_7e2704;
extern int g_7746b8;
extern unsigned char* lpGebaeudePROT;

int __cdecl fcn_00506380(int, unsigned char*, unsigned short*, int);
int __cdecl fcn_00502cd0(int, int, int, int, int);
void __cdecl d2_EnterObjektInterior(int);
void __cdecl d3_UpdateBuildingView(unsigned char*, int);
void __cdecl d3_SetupInteriorScene(unsigned char*, int);
void __cdecl fcn_00597ec0(unsigned char*);

void __cdecl d3_UpdateBuildingInteriorState(void)
{
	int x;
	unsigned char* e;
	char* r;

	if (g_7e431c != 0) {
		r = (char *)&((OBJECT_PROTOTYPE *)lpObjektePROT)[*g_7e431c].kind;
		if ((*r == 6 || *r == 2) && (fcn_00506380(g_774970, g_7746c8, g_7e431c, 0) & 0x4000)) {
			x = fcn_00502cd0(*(int*) (g_7746c8 + 0x5d), 2, 6, 0, 0xfd);
			d2_EnterObjektInterior((int) g_7e431c);
			d3_UpdateBuildingView(g_7746c8, 0xfd);
			d3_SetupInteriorScene(g_7746c8, x);
			g_774658 = g_774650;
		}
	}
	if (g_7e2700 != 0 && g_7e2708 != 0 && g_7e2704 == g_7746c8) {
		x = fcn_00502cd0(*(int*) (g_7746c8 + 0x5d), 2, 6, 0, 0xfd);
		if (g_7e2708 != x) {
			d2_EnterObjektInterior(g_7e2708);
			d3_UpdateBuildingView(g_7746c8, 0xfd);
			d3_SetupInteriorScene(g_7746c8, x);
		} else {
			g_7e2700 = 0;
			g_7e2708 = 0;
			g_7e2704 = 0;
		}
	}
	if (g_7746b8 != 0 && g_7746f0 == 0) {
		x = fcn_00502cd0(*(int*) (g_7746c8 + 0x5d), 2, 6, 0, 0xfd);
		d2_EnterObjektInterior(g_7746b8);
		d3_UpdateBuildingView(g_7746c8, 0xfd);
		d3_SetupInteriorScene(g_7746c8, x);
	}
	e = g_7746c8;
	r = (char*)&((BUILDING_PROTOTYPE*)lpGebaeudePROT)[*e];
	if (*e == 0x20 || *e == 0x1f || *e == 0x1e || ((char)((BUILDING_PROTOTYPE*)r)->category) == 0x1f || ((char)((BUILDING_PROTOTYPE*)r)->category) == 0x1d) {
		fcn_00597ec0(e);
	}
}
