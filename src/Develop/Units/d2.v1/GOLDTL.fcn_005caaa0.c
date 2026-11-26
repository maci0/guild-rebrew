typedef struct
{
	char pad0[0x50];
	short w;
	short h;
} fcn_005caaa0_Def;
// SIZE 0x54

// SIZE 0x21c
#include "Develop/DieGildeAddOn/game/entity_record.h"






// SIZE 0x2f4
typedef struct
{
	char pad0[0x5c];
	int f5c;
	char pad60[0x1d0 - 0x60];
	int f1d0;
	char pad1d4[0x2f0 - 0x1d4];
	char* owner;
} fcn_005caaa0_Tile;

typedef struct
{
	char* e;
	int tile;
	int bar;
	char padc[0xc];
	int icon;
	int f1c;
	int f20;
	int f24;
	int f28;
	char pad2c[4];
	int f30;
} fcn_005caaa0_Sel;

extern char* g_772500;
extern int d2_CurrentWindowId;
extern char* g_1015ea0;

#include "Develop/DieGildeAddOn/game/game_player.h"

int __cdecl d2_AddElementToWindow(int x, int y, int a3, int win);
int __cdecl fcn_004677e0(int x, int y, int a3, int a4, int a5, int a6, int a7, int win);
#include "Develop/Units/d2.v1/d2_gui.h"
void __cdecl fcn_00472640(int i, int flag);
float __cdecl gm_CalcEntityFavor(unsigned int a0, unsigned int a1, unsigned int a2);

/* ADDRESS: GOLDTL 0x005caaa0 */
int __cdecl fcn_005caaa0(int x, int y, int win, fcn_005caaa0_Sel* selection)
{
	int cx;
	int b;

	cx = x + ((fcn_005caaa0_Def*)g_772500)[1498].w / 2;
	selection->tile = d2_AddElementToWindow(x, y, 0x5da, d2_CurrentWindowId);
	selection->bar = -1;
	if (selection->e != 0) {
		selection->icon = d2_AddElementToWindow(cx - ((fcn_005caaa0_Def*)g_772500)[*(int*) (selection->e + 0x18c)].w / 2 - 3, y + 1, *(int*) (selection->e + 0x18c), d2_CurrentWindowId);
		d2_AddElementToWindow(x + 3, y + 3, selection->f1c, d2_CurrentWindowId);
		if (selection->f20 != 0)
			d2_AddElementToWindow(x + 3, ((fcn_005caaa0_Def*)g_772500)[1498].h + y - 0x13, selection->f20, d2_CurrentWindowId);
		if (selection->f24 != 0)
			d2_AddElementToWindow(((fcn_005caaa0_Def*)g_772500)[1498].w + x - 0x10, y + 3, selection->f24, d2_CurrentWindowId);
		d2_AddElementToWindow(((fcn_005caaa0_Def*)g_772500)[1498].w + x - 0x10, ((fcn_005caaa0_Def*)g_772500)[1498].h + y - 0x13, selection->f28, d2_CurrentWindowId);
		if (selection->e[2] != 6) {
			b = fcn_004677e0(cx - 0x23, ((fcn_005caaa0_Def*)g_772500)[1498].h + y + 2, 0x40, 0, 0x64, 0x75, 0x442, d2_CurrentWindowId);
			selection->bar = b;
			if (selection->e[2] == 7)
				d2_SetElementValue(b, 0, 0x64, 0, 1);
			else
				d2_SetElementValue(selection->bar, 0, 0x64, (int) gm_CalcEntityFavor(g_774970, *(unsigned short*) selection->e, 1));
			fcn_00472640(selection->bar, 0);
		}
		if (*(int*) (selection->e + 0x210) == ((ENTITY_RECORD*)g_7f4ca0)[g_774970].entity_id)
			d2_AddElementToWindow(((fcn_005caaa0_Def*)g_772500)[1498].w + x, y, 0x6d3, d2_CurrentWindowId);
		if (selection->f30 != 0) {
			((D2_CONTROL_TL*) g_1015ea0)[selection->tile].value_05c = 1;
			((D2_CONTROL_TL*) g_1015ea0)[selection->tile].flags_1d0 = 3;
			((D2_CONTROL_TL*) g_1015ea0)[selection->tile].associated_object = selection->e;
		}
		if (selection->e[2] == 5 || selection->e[2] == 6 || selection->e[2] == 7)
			d2_AddElementToWindow(x - 0x20, y, *(int*) (selection->e + 0x54), d2_CurrentWindowId);
	} else {
		d2_AddElementToWindow(cx - ((fcn_005caaa0_Def*)g_772500)[1275].w / 2 - 3, y + 1, 0x4fb, d2_CurrentWindowId);
	}
	return 0;
}
