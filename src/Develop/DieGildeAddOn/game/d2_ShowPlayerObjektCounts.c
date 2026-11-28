

#include "Develop/Units/d2.v1/d2_window_view.h"





// SIZE 0x3cc

typedef struct
{
	unsigned short x0;
	char pad2[0x2e];
	char name[0x148];
	int x178;
	char pad17c[0xa0];
} Player;
// SIZE 0x21c

#include "client_types.h"

extern char g_7f4ca0[];
#include "Develop/DieGildeAddOn/game/game_data.h"
#include "Develop/Units/d2.v1/client_dialog_state.h"
extern char s_6811b0[];
extern char s_6ab848[];
extern char s_6ab834[];
extern char s_6ab8fc[];

int __cdecl d2_CreateWindow(int, int, int, int, int);
void __cdecl d2_SetElementFont(int, int);
int __cdecl main_RunFrameLoop(void*, int);
int __cdecl io_AppendText(char*, ...);
char* __cdecl fcn_00502cd0(int, int, int);
char* __cdecl gm_NextEntityQueryMatch(void);
int __cdecl gm_LookupSpecialObject(int);
int __cdecl d2_UpdateWindowDrag(char*);
void __cdecl d2_CloseWindow(int);

void __cdecl d2_ShowPlayerObjektCounts(void)
{
	int w;
	D2_WIN* win;
	int i;
	char* e;
	int n;

	w = d2_CreateWindow(0x20, 0x60, 0x280, 0x190, 0x414);
	d2_SetElementFont(((D2_WIN*)g_1015f40)[w].slot, 0x54);
	if (main_RunFrameLoop((void*) d2_ShowPlayerObjektCounts, 0x657c7) != 0) {
		win = &((D2_WIN*)g_1015f40)[w];
		do {
			if (g_14ce8e0 != 0) {
				g_774654 = 1;
			}
			d2_CurrentWindowId = w;
			io_AppendText(s_6811b0);
			for (i = 0; i < 768; i++) {
				if (((Player*)g_7f4ca0)[i].x0 != 0xffff) {
					n = 0;
					for (e = fcn_00502cd0(((Player*)g_7f4ca0)[i].x178, 1, 5); e != 0; e = gm_NextEntityQueryMatch()) {
						if (gm_LookupSpecialObject(*(unsigned short*) e) != 0 && *(int*) (e + 0x21) != 0) {
							if (n == 0) {
								io_AppendText(s_6ab848, ((Player*)g_7f4ca0)[i].name);
								io_AppendText(s_6ab834);
							}
							n++;
							io_AppendText(s_6ab8fc, *(unsigned short*) e * 2 + 0x9a8, *(int*) (e + 0x1c));
						}
					}
				}
			}
			d2_UpdateWindowDrag((char*)win);
		} while (main_RunFrameLoop((void*) d2_ShowPlayerObjektCounts, 0x657c7) != 0);
	}
	d2_CloseWindow(w);
}
