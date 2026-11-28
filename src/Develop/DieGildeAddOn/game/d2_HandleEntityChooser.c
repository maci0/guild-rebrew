


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

extern char io_LastKeyScancode;
#include "Develop/DieGildeAddOn/game/game_data.h"
extern char g_7746f4;
extern unsigned char* d2_InteriorBuilding;
extern char* d2_VisitedBuilding;
#include "Develop/DieGildeAddOn/game/game_player.h"

unsigned char* __cdecl d2_RunCityScrollMapDialog(int, Query*, int, int, int);
int __cdecl gm_CheckEntityType(unsigned char*);
void __cdecl d2_EnterBuildingObjekt(unsigned char*, int, char*);
unsigned char __cdecl gm_GetEntityUiFlags(int, unsigned char*, int, int);
void __cdecl d3_FocusCameraOnEntity(unsigned char*);

/* ADDRESS: GOLDDE 0x0057f2b0 */
void __cdecl d2_HandleEntityChooser(void)
{
	Query q;
	unsigned char* e;

	if (io_LastKeyScancode != 0x32) {
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
	e = d2_RunCityScrollMapDialog(1, &q, 0, 0, 0);
	if (e == 0 || g_7746f4 != 0) {
		return;
	}
	if ((*(int*)&d2_InteriorBuilding) != 0) {
		if (gm_CheckEntityType(e) && *e == 0x47) {
			d2_EnterBuildingObjekt(e, 0xfd, "");
			return;
		}
		d2_EnterBuildingObjekt(e, -1, "");
		return;
	}
	if (gm_CheckEntityType(e) && *e == 0x47) {
		if (gm_GetEntityUiFlags(gm_LocalPlayerSlot, e, 0, 0) & 1) {
			d2_EnterBuildingObjekt(e, 0xfd, "");
		}
		return;
	}
	if ((*(int*)&d2_InteriorBuilding) == 0 && (*(int*)&d2_VisitedBuilding) == 0) {
		d3_FocusCameraOnEntity(e);
		return;
	}
	d2_EnterBuildingObjekt(e, *(unsigned short*) (e + 0x29), "");
}
