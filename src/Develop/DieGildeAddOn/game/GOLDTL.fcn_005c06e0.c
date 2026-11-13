#include <string.h>
/* SIZE 0x21c */
typedef struct {
	char f0[4];
	int f4;
	char pad[0x214];
} Slot5c06;

extern Slot5c06 g_7f4ca0[];
#include "Develop/DieGildeAddOn/game/game_player.h"
extern float g_6628a0;
extern int g_100f1dc;
extern int g_14ce8e0;
#include "client_dialog_state.h"
extern int g_67d370;
extern char g_6ac494[];

double __cdecl gm_RandomFloat01(void);
int __cdecl fcn_00525f60(void*, int);
int __cdecl fcn_00579640(void*, void*);
int __cdecl CountMatchingStraftatEntries(int, unsigned short);
void __cdecl io_FormatTextBuffer(void*, int, ...);
void __cdecl fcn_00526120(char*, int);
int __cdecl fcn_00470820(int, int, void*);
void __cdecl fcn_00471b60(int);
void __cdecl d2_SetOverlayAnimation(int, int);
void __cdecl d2_SetForm(int, int);
int __cdecl io_AppendText(int, ...);
int __cdecl fcn_00472250(int, int, int);
int __cdecl fcn_005c9220(int*);
int __cdecl fcn_005373e0(void*, int);
void __cdecl fcn_004c5530(char* msg);
void __cdecl fcn_004c6ae0(int id, int k);
float __cdecl fcn_00507e70(void*, unsigned short*, int);
void __cdecl fcn_00471e30(int);

/* ADDRESS: GOLDTL 0x005c06e0 */
int __cdecl fcn_005c06e0(unsigned short* a0)
{
	int result;
	int h1;
	int h2;
	int dlg;
	int r;
	int t;
	int ids[6];
	char text[0x400];
	char ev[0xf8];
	float f;
	Slot5c06* me;

	result = 0;
	if (!a0)
		goto none;
	if (*a0 == 0xffff)
		goto none;
	if (*a0 == g_774970)
		goto none;
	if (!fcn_00525f60(&g_7f4ca0[g_774970], 2))
		return 0;
	if (!fcn_00579640(a0, &g_7f4ca0[g_774970])) {
		io_FormatTextBuffer(text, 0x409f, *a0);
		fcn_00526120(text, 0);
		return 0;
	}
	me = &g_7f4ca0[g_774970];
	r = CountMatchingStraftatEntries(*(int*) (a0 + 2), g_774970);
	if (r <= 0) {
		io_FormatTextBuffer(text, 0x1756, *a0);
		fcn_00526120(text, 0);
		return 0;
	}
	if (!fcn_00525f60(&g_7f4ca0[g_774970], 2))
		return 0;
	dlg = fcn_00470820(0, 0, g_6ac494);
	fcn_00471b60(dlg);
	d2_SetOverlayAnimation(0, 0);
	d2_SetForm(dlg, 1);
	t = io_AppendText(0x1759, r, (r != 1) + 0x1752, *a0, *a0);
	h1 = fcn_00472250(dlg, 1, t);
	h2 = fcn_00472250(dlg, 1, t + 1);
	memset(ids, 0xff, sizeof(ids));
	ids[0] = dlg;
	ids[1] = 2;
	ids[2] = 3;
	ids[3] = 4;
	ids[4] = 4;
	ids[5] = 0x13;
	fcn_005c9220(ids);
	g_100f1dc = -1;
	do {
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
		} else if (g_100f1dc != -1) {
			if (g_67d370 == h1) {
				fcn_004c6ae0(me->f4, -2);
				f = fcn_00507e70(me, a0, 4);
				if (gm_RandomFloat01() + f >= g_6628a0) {
					ev[4] = 0x2e;
					*(int*) (ev + 8) = *(int*) (a0 + 2);
					*(int*) (ev + 0xc) = -1;
					ev[0x36] = 2;
					*(int*) (ev + 0x5c) = me->f4;
					*(int*) (ev + 0x58) = *(int*) (a0 + 2);
					fcn_004c5530(ev);
					io_FormatTextBuffer(text, 0x175b, *a0);
				} else {
					io_FormatTextBuffer(text, 0x175c, *a0, *a0);
				}
				fcn_00526120(text, 0);
				g_774654 = 1;
				result = 1;
			} else if (g_67d370 == h2) {
				g_774654 = 1;
			}
		}
	} while (fcn_005373e0((void*) fcn_005c06e0, 0x677c7) != 0);
	fcn_00471e30(dlg);
	return result;
none:
	return 0;
}
