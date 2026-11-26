


#include <string.h>
#pragma intrinsic(memset)

// SIZE 0x21c
#include "Develop/DieGildeAddOn/game/entity_record.h"






#include "Develop/DieGildeAddOn/game/game_player.h"
extern __int64 g_666018;
#include "Develop/DieGildeAddOn/game/game_data.h"
#include "client_dialog_state.h"
extern char g_6ac494[];

int __cdecl fcn_00525f60(void*, int);
void __cdecl io_FormatTextBuffer(void*, int, ...);
unsigned short* __cdecl fcn_005cd440(int*, char*, int, int);
int __cdecl CountMatchingStraftatEntries(int, unsigned short);
void __cdecl fcn_00526120(char*, int);
void __cdecl fcn_00532ef0(void);
int __cdecl fcn_00470820(int, int, void*);
void __cdecl d2_CenterDialogWindows(int);
void __cdecl d2_SetOverlayAnimation(int, int);
void __cdecl d2_SetForm(int, int);
int __cdecl io_AppendText(int, ...);
int __cdecl d2_GetWindowListItem(int, int, int);
int __cdecl main_RunFrameLoop(void*, int);
void __cdecl fcn_004c5530(char* msg);
void __cdecl fcn_004c6ae0(int id, int k);
void __cdecl fcn_00471e30(int);

void __cdecl fcn_005c0a90(int arg)
{
	int h2;
	int h1;
	int msg[0x14];
	char buf[0x40];
	char text[0x200];
	unsigned short* a;
	unsigned short* b;
	int r;
	int d;
	int t;
	int v;

	if (fcn_00525f60(&((ENTITY_RECORD*)g_7f4ca0)[g_774970], 2) == 0) {
		return;
	}
	if (arg == 0) {
		return;
	}
	memset(msg, 0, sizeof(msg));
	msg[1] = 0x400;
	msg[4] = 6;
	msg[2] = (*(int*)&g_666018);
	msg[3] = g_66601c;
	io_FormatTextBuffer(buf, 0x175f);
	a = fcn_005cd440(msg, buf, 0, 0);
	if (a == 0) {
		return;
	}
	io_FormatTextBuffer(buf, 0x1760, *a);
	b = fcn_005cd440(msg, buf, 0, 0);
	if (b == 0) {
		return;
	}
	r = CountMatchingStraftatEntries(*(int*) (a + 2), g_774970);
	if (r <= 0) {
		io_FormatTextBuffer(text, 0x1756, *a);
		fcn_00526120(text, 0);
		fcn_00532ef0();
		return;
	}
	if (fcn_00525f60(&((ENTITY_RECORD*)g_7f4ca0)[g_774970], 3) == 0) {
		fcn_00532ef0();
		return;
	}
	d = fcn_00470820(0, 0, g_6ac494);
	d2_CenterDialogWindows(d);
	d2_SetOverlayAnimation(0, 0);
	d2_SetForm(d, 1);
	t = io_AppendText(0x1761, r, (r != 1) + 0x1752, *b, *a);
	h1 = d2_GetWindowListItem(d, 1, t);
	h2 = d2_GetWindowListItem(d, 1, t + 1);
	g_100f1dc = -1;
	do {
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
		}
		if (g_100f1dc != -1) {
			if (d2_CurrentElementId == h1) {
				char ev[0xf8];

				v = *(int*) (b + 2);
				*(int*) (ev + 8) = v;
				*(int*) (ev + 0xc) = v;
				*(int*) (ev + 0x5c) = ((ENTITY_RECORD*)g_7f4ca0)[g_774970].entity_id;
				*(int*) (ev + 0x60) = v;
				*(int*) (ev + 0x58) = *(int*) (a + 2);
				ev[4] = 0x2f;
				ev[0x36] = 9;
				fcn_004c5530(ev);
				fcn_004c6ae0(((ENTITY_RECORD*)g_7f4ca0)[g_774970].entity_id, -3);
				io_FormatTextBuffer(text, 0x1762, *b);
				fcn_00526120(text, 0);
				g_774654 = 1;
			}
			else if (d2_CurrentElementId == h2) {
				g_774654 = 1;
			}
		}
	} while (main_RunFrameLoop((void*) fcn_005c0a90, 0x677c7) != 0);
	fcn_00471e30(d);
	fcn_00532ef0();
}
