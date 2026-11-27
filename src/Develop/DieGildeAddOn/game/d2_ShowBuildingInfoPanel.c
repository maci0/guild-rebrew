#include "Develop/DieGildeAddOn/game/spiel.h"
#include "client_types.h"
// SIZE 0x3cc
#include "Develop/Units/d2.v1/d2_window_view.h"





// SIZE 0x2f4
typedef struct {
	char pad0[0x5c];
	int shown;
	char pad60[0x2f0 - 0x60];
	void* link;
} D2_CTRL_VIEW;

// SIZE 0x21c
typedef struct {
	char pad0[0x21c];
} ENTITY_REC_VIEW;

// SIZE 0x2f4
typedef struct {
	char pad0[0x2f4];
} DYNASTY_REC_VIEW;

extern int g_6a25b8;
extern int g_6a25bc;
extern int d2_CurrentValueBar;
extern int g_6a25c4[4];
extern int g_6a25e4;
extern int g_6a25ec;
extern int g_1040494;
extern char g_6a2f40[];
extern char g_6a2f30[];
extern char g_6a2f24[];
extern char g_6a2f18[];
extern int d2_CurrentWindowId;
#include "Develop/DieGildeAddOn/game/building_prototype.h"

extern ENTITY_REC_VIEW g_7f4ca0[];
extern DYNASTY_REC_VIEW g_868060[];
extern char* gm_CityEntity;
extern unsigned char* lpGebaeudePROT;
#include "Develop/DieGildeAddOn/game/game_player.h"
extern unsigned char* g_7746c8;
extern int g_14ad0cc;
extern int g_14ad0d4;

int __cdecl gm_GetEntityMood(unsigned char* s);
int __cdecl d2_LoadForm(int a, int b, char* s);
void __cdecl d2_SetForm(int h, int mode);
void __cdecl io_FormatEntityNameMarkup(int id, int a, int b, char* out);
void __cdecl io_AppendText(char* fmt, ...);
int __cdecl d2_AddElementToWindow(int x, int y, int kind, int owner);
int __cdecl d2_AddWindowValueGauge(int, int, int, int, int, int, int, int);
#include "Develop/Units/d2.v1/d2_gui.h"

unsigned char __cdecl gm_GetEntityUiFlags(int, unsigned char*, int, int);
int __cdecl d2_CreateWindowTextButton(int x, int y, int z);

/* ADDRESS: GOLDTL 0x0052df40 */
void __cdecl d2_ShowBuildingInfoPanel(unsigned char* building)
{
	char name[128];
	int pct;
	int kind;
	unsigned char* t;
	unsigned char r;

	pct = gm_GetEntityMood(building);
	if (g_6a25b8 != -1) {
		return;
	}
	g_6a25b8 = d2_LoadForm(g_1040494 - 0x68, 0x106, g_6a2f40);
	d2_SetForm(g_6a25b8, 1);
	if (*building != 0x47) {
		io_FormatEntityNameMarkup(*(unsigned short*) (building + 0x27), 2, 1, name);
		if (building[5] != 0) {
			io_AppendText(g_6a2f30, name, *building * 14 + 0x48e, building + 5);
		} else {
			io_AppendText(g_6a2f24, name, *building * 14 + 0x48e);
		}
	} else {
		io_AppendText(g_6a2f24, 0x870, &g_868060[*(int*) (building + 0x65)]);
	}
	d2_SetForm(g_6a25b8, 0);
	g_6a25bc = d2_AddElementToWindow((((D2_WIN*) g_1015f40)[d2_CurrentWindowId].width - 0x30) >> 1, 0x48, *building + 0x427, d2_CurrentWindowId);
	((D2_CTRL_VIEW*)g_1015ea0)[g_6a25bc].shown = 1;
	if (*(unsigned short*) (building + 0x27) != 0xffff && *(unsigned short*) (building + 0x27) != *(unsigned short*) gm_CityEntity) {
		((D2_CTRL_VIEW*)g_1015ea0)[g_6a25bc].link = &g_7f4ca0[*(unsigned short*) (building + 0x27)];
	}
	if (*building == 0x47 || *building == 0x1d || *building == 0x57) {
		d2_CurrentValueBar = -1;
	} else {
		d2_CurrentValueBar = d2_AddWindowValueGauge(0x15, 0x7b, 0x38, 0, 0x64, 0x75, 0x442, d2_CurrentWindowId);
		d2_SetElementValue(d2_CurrentValueBar, 0, 0x64, pct);
	}
	if ((building[0x5a] & 1) != 0 || *building == 0x47 || *building == 0x1d || *building == 0x57) {
		g_6a25ec = -1;
		g_6a25e4 = -1;
		g_6a25c4[0] = -1;
		return;
	}
	kind = gm_GetBuildingTypeCategory(*building);
	t = (unsigned char*) &((BUILDING_PROTOTYPE*) lpGebaeudePROT)[*building];
	r = gm_GetEntityUiFlags(g_774970, building, 0, 0);
	if (*(unsigned short*) (building + 0x27) == g_774970 || *(unsigned short*) (building + 0x25) == g_774970 || (r & 0x10) != 0) {
		g_6a25ec = d2_CreateWindowTextButton(0, 0x8c, g_14ad0cc);
	} else {
		g_6a25ec = d2_CreateWindowTextButton(0, 0x8c, g_14ad0d4);
	}
	if ((kind == 1 || kind == 2 || kind == 4 || kind == 7 || kind == 8 || *t == 0x10 || *t == 0x1e || *t == 0x1f || *t == 0x1d) && *t != 5) {
		if (g_7746c8 == 0) {
			g_6a25e4 = d2_CreateWindowTextButton(0, 0xa6, (int) g_6a2f18);
		}
		g_6a25c4[0] = -1;
		return;
	}
	g_6a25c4[0] = -1;
	g_6a25e4 = -1;
}
