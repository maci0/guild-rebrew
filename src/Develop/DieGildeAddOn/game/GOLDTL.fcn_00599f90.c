


#include <string.h>

typedef struct
{
	int x0;
	int x4;
	int x8;
	int xc;
	int x10;
	char pad14[0x38];
	int x4c;
} Query;
// SIZE 0x50

extern char g_14cf950;
#include "Develop/DieGildeAddOn/game/game_data.h"
extern char g_7746f4;
extern unsigned char* g_7746c8;
extern char* g_7746c4;
#include "Develop/DieGildeAddOn/game/game_player.h"

unsigned char* __cdecl fcn_005bdc30(int, Query*, int, int, int);
int __cdecl gm_CheckEntityType(unsigned char*);
void __cdecl d2_EnterBuildingObjekt(unsigned char*, int, char*);
unsigned char __cdecl fcn_00506380(int, unsigned char*, int, int);
void __cdecl d3_FocusCameraOnEntity(unsigned char*);

void __cdecl d2_HandleEntityChooser(void)
{
	Query q;
	unsigned char* e;

	if (g_14cf950 != 0x32) {
		if (g_14ce8d8 == 0) {
			return;
		}
		if (d2_CurrentElementId != g_6a2590 && d2_CurrentElementId != g_6a2594) {
			return;
		}
	}
	memset(&q, 0, sizeof(q));
	q.x10 = 0;
	q.x8 = 0;
	q.x4c = 0x71f;
	e = fcn_005bdc30(1, &q, 0, 0, 0);
	if (e == 0 || g_7746f4 != 0) {
		return;
	}
	if ((*(int*)&g_7746c8) != 0) {
		if (gm_CheckEntityType(e) && *e == 0x47) {
			d2_EnterBuildingObjekt(e, 0xfd, "");
			return;
		}
		d2_EnterBuildingObjekt(e, -1, "");
		return;
	}
	if (gm_CheckEntityType(e) && *e == 0x47) {
		if (fcn_00506380(g_774970, e, 0, 0) & 1) {
			d2_EnterBuildingObjekt(e, 0xfd, "");
		}
		return;
	}
	if ((*(int*)&g_7746c8) == 0 && (*(int*)&g_7746c4) == 0) {
		d3_FocusCameraOnEntity(e);
		return;
	}
	d2_EnterBuildingObjekt(e, *(unsigned short*) (e + 0x29), "");
}
