

#include "Develop/Units/d2.v1/d2_window_view.h"





// SIZE 0x3cc

#include "client_types.h"

#include "Develop/DieGildeAddOn/game/game_data.h"
#include "client_dialog_state.h"
extern int g_67a370;
extern int g_6b8300;
extern int g_773d8c;
extern char s_6ab7e4[];
extern char s_6ab7cc[];
extern char s_6ab7ac[];
extern char s_6ab790[];
extern char s_6ab778[];
extern char s_6ab764[];
extern char s_6ab748[];
extern char s_6ab728[];
extern char s_6ab710[];
extern char s_6ab6f8[];
extern char s_6ab6e4[];
extern char s_6ab6d0[];

int __cdecl fcn_0046e940(int, int, int, int, int);
void __cdecl d2_SetElementFont(int, int);
int __cdecl fcn_005373e0(void*, int);
int __cdecl io_AppendText(int, ...);
int __cdecl fcn_0045a230(int, int, int);
int __cdecl fcn_00459d50(int);
int __cdecl fcn_00459d90(int, int);
int __cdecl d3_GetAnimSize(char*);
int __cdecl ch_CountCharacters(int, int);
int __cdecl d2_UpdateWindowDrag(char*);
void __cdecl fcn_0046f280(int);

void __cdecl fcn_005b37d0(void)
{
	D2_WIN* w;
	int h;
	int total;
	int n;
	int v;
	char* p;

	h = fcn_0046e940(0x20, 0x60, 0x280, 0x190, 0x414);
	d2_SetElementFont(((D2_WIN*)g_1015f40)[h].slot, 0x54);
	while (fcn_005373e0((void*) fcn_005b37d0, 0x657c7) != 0) {
		w = &((D2_WIN*)g_1015f40)[h];
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
		}
		d2_CurrentWindowId = h;
		io_AppendText((int) "$C");
		io_AppendText((int) s_6ab7e4);
		total = fcn_0045a230(0x1ff, 0x80, 0);
		io_AppendText((int) s_6ab7cc, total);
		v = fcn_0045a230(0x1ff, 1, 0);
		total += v;
		io_AppendText((int) s_6ab7ac, v);
		v = fcn_0045a230(0x1ff, 2, 0);
		total += v;
		io_AppendText((int) s_6ab790, v);
		v = fcn_00459d50(*(int*) (((char*)g_67a370) + 0xb0));
		total += v;
		io_AppendText((int) s_6ab778, v);
		v = fcn_00459d90(g_6b8300, 1);
		total += v;
		io_AppendText((int) s_6ab764, v);
		v = fcn_0045a230(0x1ff, 0x28, 0);
		total += v;
		io_AppendText((int) s_6ab748, v);
		n = 0;
		for (p = g_1042320; p != g_1052a40; p = *(char**) (p + 0x160)) {
			n += d3_GetAnimSize(p);
		}
		io_AppendText((int) s_6ab728, n);
		io_AppendText((int) s_6ab710, total);
		io_AppendText((int) s_6ab6f8, ch_CountCharacters(-1, 1));
		io_AppendText((int) s_6ab6e4, gm_EntityCount);
		io_AppendText((int) s_6ab6d0, g_773d8c);
		d2_UpdateWindowDrag((char*)w);
	}
	fcn_0046f280(h);
}
