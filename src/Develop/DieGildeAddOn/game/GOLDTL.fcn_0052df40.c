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
} Ctl_52df40;

// SIZE 0x21c
typedef struct {
	char pad0[0x21c];
} House_52df40;

// SIZE 0x2f4
typedef struct {
	char pad0[0x2f4];
} Dyn_52df40;

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

extern House_52df40 g_7f4ca0[];
extern Dyn_52df40 g_868060[];
extern char* gm_CityEntity;
extern unsigned char* lpGebaeudePROT;
#include "Develop/DieGildeAddOn/game/game_player.h"
extern unsigned char* g_7746c8;
extern int g_14ad0cc;
extern int g_14ad0d4;

int __cdecl fcn_00508da0(unsigned char* s);
int __cdecl fcn_00470820(int a, int b, char* s);
void __cdecl d2_SetForm(int h, int mode);
void __cdecl io_FormatEntityNameMarkup(int id, int a, int b, char* out);
void __cdecl io_AppendText(char* fmt, ...);
int __cdecl fcn_0046f740(int x, int y, int kind, int owner);
int __cdecl fcn_004677e0(int, int, int, int, int, int, int, int);
#include "Develop/Units/d2.v1/d2_gui.h"

unsigned char __cdecl fcn_00506380(int, unsigned char*, int, int);
int __cdecl fcn_0052dee0(int x, int y, int z);

/* ADDRESS: GOLDTL 0x0052df40 */
void __cdecl fcn_0052df40(unsigned char* s)
{
	char name[128];
	int pct;
	int kind;
	unsigned char* t;
	unsigned char r;

	pct = fcn_00508da0(s);
	if (g_6a25b8 != -1) {
		return;
	}
	g_6a25b8 = fcn_00470820(g_1040494 - 0x68, 0x106, g_6a2f40);
	d2_SetForm(g_6a25b8, 1);
	if (*s != 0x47) {
		io_FormatEntityNameMarkup(*(unsigned short*) (s + 0x27), 2, 1, name);
		if (s[5] != 0) {
			io_AppendText(g_6a2f30, name, *s * 14 + 0x48e, s + 5);
		} else {
			io_AppendText(g_6a2f24, name, *s * 14 + 0x48e);
		}
	} else {
		io_AppendText(g_6a2f24, 0x870, &g_868060[*(int*) (s + 0x65)]);
	}
	d2_SetForm(g_6a25b8, 0);
	g_6a25bc = fcn_0046f740((((D2_WIN*) g_1015f40)[d2_CurrentWindowId].width - 0x30) >> 1, 0x48, *s + 0x427, d2_CurrentWindowId);
	((Ctl_52df40*)g_1015ea0)[g_6a25bc].shown = 1;
	if (*(unsigned short*) (s + 0x27) != 0xffff && *(unsigned short*) (s + 0x27) != *(unsigned short*) gm_CityEntity) {
		((Ctl_52df40*)g_1015ea0)[g_6a25bc].link = &g_7f4ca0[*(unsigned short*) (s + 0x27)];
	}
	if (*s == 0x47 || *s == 0x1d || *s == 0x57) {
		d2_CurrentValueBar = -1;
	} else {
		d2_CurrentValueBar = fcn_004677e0(0x15, 0x7b, 0x38, 0, 0x64, 0x75, 0x442, d2_CurrentWindowId);
		d2_SetElementValue(d2_CurrentValueBar, 0, 0x64, pct);
	}
	if ((s[0x5a] & 1) != 0 || *s == 0x47 || *s == 0x1d || *s == 0x57) {
		g_6a25ec = -1;
		g_6a25e4 = -1;
		g_6a25c4[0] = -1;
		return;
	}
	kind = gm_GetBuildingTypeCategory(*s);
	t = (unsigned char*) &((BUILDING_PROTOTYPE*) lpGebaeudePROT)[*s];
	r = fcn_00506380(g_774970, s, 0, 0);
	if (*(unsigned short*) (s + 0x27) == g_774970 || *(unsigned short*) (s + 0x25) == g_774970 || (r & 0x10) != 0) {
		g_6a25ec = fcn_0052dee0(0, 0x8c, g_14ad0cc);
	} else {
		g_6a25ec = fcn_0052dee0(0, 0x8c, g_14ad0d4);
	}
	if ((kind == 1 || kind == 2 || kind == 4 || kind == 7 || kind == 8 || *t == 0x10 || *t == 0x1e || *t == 0x1f || *t == 0x1d) && *t != 5) {
		if (g_7746c8 == 0) {
			g_6a25e4 = fcn_0052dee0(0, 0xa6, (int) g_6a2f18);
		}
		g_6a25c4[0] = -1;
		return;
	}
	g_6a25c4[0] = -1;
	g_6a25e4 = -1;
}
