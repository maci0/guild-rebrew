#include "Develop/DieGildeAddOn/game/entity.h"

#include "Develop/DieGildeAddOn/game/game_player.h"
#include "Develop/DieGildeAddOn/game/game_data.h"
extern int g_775338;

int __cdecl d2_LoadForm(int, int, char*);
void __cdecl d2_CenterDialogWindows(int);
void __cdecl d2_SetForm(int, int);
void __cdecl d2_InitWindowBounds(int);
int __cdecl io_AppendText(int, ...);
int __cdecl d2_PopulateOwnerBuildingList(unsigned short*, int, int*);
int __cdecl d2_GetFormWindow(int, int);
void __cdecl d2_CreateWindowScrollbar(int, int, int, int, int, int*, int*, int*);

/* ADDRESS: GOLDTL 0x005c86b0 */
/* ADDRESS: GOLDDE 0x005aa510 */
int __cdecl d2_CreateGebaeudeListPanel(void)
{
	int a;
	int b;
	int c;
	int h;
	unsigned short* p;

	p = (unsigned short*) &((EntityStruct*) g_slot_table)[gm_LocalPlayerSlot];
	h = d2_LoadForm(0, 0, "panel\\geb_liste_2");
	d2_CenterDialogWindows(h);
	d2_SetForm(h, 0);
	d2_InitWindowBounds(d2_CurrentWindowId);
	d2_SetForm(h, 1);
	io_AppendText(0xb2);
	d2_SetForm(h, 2);
	g_775338 = d2_PopulateOwnerBuildingList(p, 0x80, (int*) ((int) &g_775338 + 0x35c8));
	d2_SetForm(h, 0);
	d2_CreateWindowScrollbar(0x206, 0x167, d2_CurrentWindowId,
				 d2_GetFormWindow(h, 2), 0x40, &c, &b, &a);
	return h;
}
