

#include <string.h>

#include "Develop/Units/d2.v1/d2_window_view.h"





// SIZE 0x3cc

#include "client_types.h"

extern int g_67a370;
extern int g_775280;
extern char* g_778b20[];
#include "Develop/DieGildeAddOn/game/game_data.h"
#include "client_dialog_state.h"
extern char s_6ab5f8[];
extern char s_6ab5cc[];
extern char s_6ab588[];

int __cdecl fcn_0046e940(int, int, int, int, int);
void __cdecl d2_SetElementFont(int, int);
void __cdecl d3_VisitSceneObjects(char*, int, int, void*, int);
int __cdecl io_AppendText(char*, ...);
void __cdecl d3_TransformPoint(char*, char*, float*);
char __cdecl fcn_0045b990(char*, float*, int*, int*, int*);
int __cdecl fcn_005373e0(void*, int);
int __cdecl d2_UpdateWindowDrag(char*);
void __cdecl fcn_0046f280(int);
void __cdecl d2_CollectDebugObject(void);

void __cdecl d2_ShowSmapDiagnostics(void)
{
	int w;
	int x;
	int y;
	int z;
	float v[4];
	char buf[0x80];
	int i;
	char* map;
	char* e;
	int c;
	D2_WIN* win;

	w = fcn_0046e940(0x20, 0x60, 0x280, 0x190, 0x414);
	d2_SetElementFont(((D2_WIN*)g_1015f40)[w].slot, 0x54);
	g_775280 = 0;
	d3_VisitSceneObjects(((char*)g_67a370), 0, 0x100, (void*) d2_CollectDebugObject, 0);
	io_AppendText(s_6ab5f8);
	io_AppendText(s_6ab5cc);
	for (i = 0; i < g_775280; i++) {
		memset(buf, 0, sizeof(buf));
		d2_CurrentWindowId = w;
		map = *(char**) (((char*)g_67a370) + 0xb0);
		e = g_778b20[i];
		d3_TransformPoint(e, e + 0x4c, v);
		if (map != 0 && fcn_0045b990(map, v, &x, &y, &z)) {
			c = *(int*) (*(char**) (map + 0x24) + (*(int*) (map + 0x20) * y + x) * 28);
			if (c == 0 || c == 10) {
				strcat(buf, "smap-pos is blocked  ");
			}
		}
		else {
			strcat(buf, "No smap or pos out of range  ");
		}
		io_AppendText(s_6ab588, g_778b20[i], buf);
	}
	if (fcn_005373e0((void*) d2_ShowSmapDiagnostics, 0x657c7) != 0) {
		win = &((D2_WIN*)g_1015f40)[w];
		do {
			if (g_14ce8e0 != 0) {
				g_774654 = 1;
			}
			d2_UpdateWindowDrag((char*)win);
		} while (fcn_005373e0((void*) d2_ShowSmapDiagnostics, 0x657c7) != 0);
	}
	fcn_0046f280(w);
}
