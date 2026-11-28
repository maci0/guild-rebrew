#include <string.h>

// SIZE 0x3cc
#include "Develop/Units/d2.v1/d2_win.h"








// SIZE 0x2f4
typedef struct {
	char pad0[0x5c];
	int used;
	char pad60[0x290];
	void* ent;
} Ctl_5b4c80;

// SIZE 0x21c
typedef struct {
	unsigned short slot;
	char pad2[0x21a];
} Ent_5b4c80;

#include "client_types.h"
extern Win_1015f40 g_1015f40[0x60];
extern char* g_1015ea0;
extern char g_7f4ca0[];
#include "Develop/DieGildeAddOn/game/game_data.h"
#include "Develop/Units/d2.v1/client_dialog_state.h"

int __cdecl d2_CreateWindow(int x, int y, int w, int h, int a5);
int __cdecl d2_CreateChildWindow(int x, int y, int cx, int cy, int a5, int win);
void __cdecl d2_SetElementFont(int, int);
int __cdecl main_RunFrameLoop(void*, int);
void __cdecl d2_RunCharacterDebugDialog(void*);
char* __cdecl io_AppendText(int, ...);
int __cdecl he_CountActiveHandlungen(Ent_5b4c80*);
int __cdecl d2_GetWindowListItem(int, int, char*);
void __cdecl d2_UpdateWindowDrag(D2_WIN*);
int __cdecl d2_CloseWindow(int);

#include "Develop/Units/d2.v1/d2_gui.h"
/* Modal two-column entity list: fills it once, then pumps the UI and opens
 * the entry the player picks. */
/* ADDRESS: GOLDTL 0x005b4c80 */
void __cdecl d2_ShowCharacterActionDebug(void)
{
	int ids[0x300];
	D2_WIN* rp;
	int left;
	int win;
	int right;
	int fill;
	int saved;
	int n;
	int i;

	memset(ids, 0xff, sizeof(ids));
	fill = 1;
	left = d2_CreateChildWindow(0, 0, 0x140, 0x190, 0x10, win = d2_CreateWindow(0x20, 0x60, 0x280, 0x190, 0x414));
	right = d2_CreateChildWindow(0x140, 0, 0x140, 0x190, 0x10, win);
	d2_SetElementFont(((D2_WIN*)g_1015f40)[win].slot, 0x54);
	d2_SetElementFont(((D2_WIN*)g_1015f40)[left].slot, 0x54);
	d2_SetElementFont(((D2_WIN*)g_1015f40)[right].slot, 0x54);
	if (main_RunFrameLoop((void*) d2_ShowCharacterActionDebug, 0x657c7)) {
		rp = &((D2_WIN*)g_1015f40)[right];
		do {
			if (g_14ce8e0 != 0) {
				g_774654 = 1;
			}
			if (g_100f1dc != -1) {
				for (i = 0; i < 0x300; i++) {
					if (ids[i] != -1 && d2_CurrentElementId == ids[i]) {
						if (((D2_CONTROL_TL*) g_1015ea0)[d2_CurrentElementId].associated_object != 0) {
							d2_RunCharacterDebugDialog(((D2_CONTROL_TL*) g_1015ea0)[d2_CurrentElementId].associated_object);
						}
						break;
					}
				}
			}
			if (fill) {
				d2_CurrentWindowId = left;
				saved = *(int*) &((D2_WIN*)g_1015f40)[left].pad3c[0x21c];
				io_AppendText((int) "$C");
				ids[0] = d2_GetWindowListItem(-1, d2_CurrentWindowId, io_AppendText((int) "%ib[NIEMAND]$6THeCnt:%i$A", 2, he_CountActiveHandlungen(0)));
				((D2_CONTROL_TL*) g_1015ea0)[ids[0]].associated_object = 0;
				((D2_CONTROL_TL*) g_1015ea0)[ids[0]].value_05c = 1;
				n = 1;
				for (i = 0; i < 0x300; i++) {
					if (n >= 0x40) {
						break;
					}
					ids[i] = -1;
					if (((Ent_5b4c80*)g_7f4ca0)[i].slot != 0xffff) {
						ids[i] = d2_GetWindowListItem(-1, d2_CurrentWindowId, io_AppendText((int) "%it[%1N4]$6THeCnt:%i$A", ((Ent_5b4c80*)g_7f4ca0)[i].slot, he_CountActiveHandlungen(&((Ent_5b4c80*)g_7f4ca0)[i])));
						((D2_CONTROL_TL*) g_1015ea0)[ids[i]].associated_object = &((Ent_5b4c80*)g_7f4ca0)[i];
						n++;
						((D2_CONTROL_TL*) g_1015ea0)[ids[i]].value_05c = 1;
					}
					if (n >= 0x3f) {
						if (d2_CurrentWindowId == right) {
							break;
						}
						d2_CurrentWindowId = right;
						io_AppendText((int) "$C");
						n = 0;
					}
				}
				*(int*) &((D2_WIN*)g_1015f40)[left].pad3c[0x21c] = saved;
				fill = 0;
			}
			d2_UpdateWindowDrag(&((D2_WIN*)g_1015f40)[left]);
			d2_UpdateWindowDrag(rp);
		} while (main_RunFrameLoop((void*) d2_ShowCharacterActionDebug, 0x657c7));
	}
	d2_CloseWindow(win);
	d2_CloseWindow(left);
	d2_CloseWindow(right);
}
