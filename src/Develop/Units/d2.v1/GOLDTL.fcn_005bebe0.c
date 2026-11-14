/*
 * Draw the tooltip of record broadcast slot a2 (0..4) at the house of
 * g_774970.
 */

#include <string.h>

#include "client_types.h"
typedef pos14_7f4c00 Tbebe;


/* Message packet handed to fcn_004c5530. Field names unknown, so the layout
 * keeps raw offsets. */
typedef struct
{
	int f0;
	unsigned char b4;
	char pad5[3];
	int f8;
	int fc;
	char pad10[0x26];
	unsigned char b36;
	char pad37[0x23];
	unsigned char b5a;
	char pad5b[0x9d];
} MsgBebe;
/* SIZE 0xf8 */

struct s_1015f4c
{
	int x;
	int y;
	char pad[0x384];
	int idx;
	char pad2[0xc];
	int w;
	int h;
	int c;
	int d;
	char pad3[0x20];
};

extern char g_7f4ca0[];
#include "Develop/DieGildeAddOn/game/game_player.h"
extern int g_772514;
extern int g_7725d0;
extern int g_100f1dc;
extern int g_14ce8e0;
#include "client_dialog_state.h"
extern char* g_1015ea0;
extern float g_662a98;
extern float g_664168;
#include "client_types.h"
extern pos14_7f4c00 g_7f4c00;
extern s_1015f4c g_1015f4c[];

char* __cdecl fcn_005463a0(int a, int b, int c, int d, int e);
int __cdecl fcn_004fa5b0(int a1, char* a2, int a3);
int __cdecl fcn_00470820(int a, int b, char* name);
void __cdecl fcn_00471b60(int h);
void __cdecl fcn_00471e30(int h);
void __cdecl d2_SetForm(int h, int a);
void __cdecl d2_SetOverlayAnimation(int a, int b);
int __cdecl io_AppendText(int id, ...);
int __cdecl fcn_0046f740(int x, int y, int id, int layer);
void __cdecl fcn_005340f0(int i);
void __cdecl fcn_00534160(int x0, int y, int len, int t);
int __cdecl fcn_0051e070(void);
void __cdecl fcn_00532ef0(void);
int __cdecl fcn_005373e0(void* fn, int a);
void __cdecl fcn_0057e880(int a, int b, int c, int d);
void __cdecl fcn_00500bb0(Tbebe*, int, int, int);
int __cdecl fcn_00500d20(void*, void*);
void __cdecl fcn_004c6ae0(int a, int b);
void __cdecl fcn_004c5530(MsgBebe* msg);

/* ADDRESS: GOLDTL 0x005bebe0 */
void __cdecl fcn_005bebe0(int a0, int a1, int a2)
{
	int big[0x88];
	MsgBebe msg;
	int yoff[5] = {0x25e, 0x264, 0x26a, 0x270, 0x276};
	int found;
	int ids[5];
	int flag;
	unsigned char color;
	char* slot;
	int miss;
	unsigned char level;
	float f;
	int h;
	int x;

	slot = fcn_005463a0(2, 2, g_774970, 0, 0x60);
	memset(big, 0, sizeof(big));
	flag = 0;
	ids[0] = 0x3a;
	ids[1] = 0x1a;
	ids[2] = 0x17;
	ids[3] = 0x18;
	ids[4] = 0x19;
	big[0] = 1;
	if (a2 >= 5) {
		return;
	}
	miss = (fcn_004fa5b0(ids[a2], (char*) g_7f4ca0 + g_774970 * 0x21c, (int) big) & 2) != 0 ? -1 : 0;
	color = *(unsigned char*) (g_7f4ca0 + g_774970 * 0x21c + 0x80 + a2);
	if (color < 0x2a) {
		level = 1;
	} else if (color < 0x54) {
		level = 2;
	} else if (color < 0x7e) {
		level = 4;
	} else if (color < 0xa8) {
		level = 6;
	} else if (color < 0xd2) {
		level = 9;
	} else {
		level = 12;
	}
	color = level + miss;
	h = fcn_00470820(0, 0, (char*) 0x6ac484);
	d2_SetForm(h, 0);
	fcn_005340f0(g_772514);
	fcn_00471b60(h);
	d2_SetForm(h, 1);
	d2_SetOverlayAnimation(0, 0);
	io_AppendText(0x16af, a2 + 0x16b7);
	io_AppendText(a2 + 0x16c3);
	d2_SetForm(h, 2);
	x = ((struct s_1015f4c*) g_1015f4c)[g_772514].x;
	f = (float) *(unsigned char*) (g_7f4ca0 + g_774970 * 0x21c + 0x80 + a2) * g_664168;
	if (!(f < g_662a98)) {
		f = g_662a98;
	}
	found = fcn_0046f740(x / 2 - 0x18, 4, (int) ((float) yoff[a2] + f), g_772514);
	fcn_00534160(x / 2 - 0x23, 0x3c, *(unsigned char*) (g_7f4ca0 + g_774970 * 0x21c + 0x80 + a2), 0x4df);
	d2_SetForm(h, 3);
	if (slot != 0) {
		io_AppendText(0x16b3, *(unsigned char*) (slot + 0xae) + 0x16b7, a2 + 0x16b7);
	} else if (*(unsigned char*) (g_7f4ca0 + g_774970 * 0x21c + 0x80 + a2) >= 0xfc) {
		io_AppendText(0x16b2);
	} else if (*(int*) (g_7f4ca0 + g_774970 * 0x21c + 0x194) >= (int) color) {
		if (miss == 0) {
			switch (fcn_0051e070()) {
			case 0:
				io_AppendText(0x16b1, color, a2 + 0x16b7);
				break;
			case 1:
				io_AppendText(0x16b1, color, a2 + 0x16b7);
				break;
			}
			flag = 1;
		} else {
			switch (fcn_0051e070()) {
			case 0:
				io_AppendText(0x16b0,
					     (*(unsigned char*) (g_7f4ca0 + g_774970 * 0x21c + 9) != 0 ? 0x28 : 0) + 0x253 +
						     *(unsigned char*) (g_7f4ca0 + g_774970 * 0x21c + 0x169),
					     color, a2 + 0x16b7);
				break;
			case 1:
				io_AppendText(0x16b0,
					     (*(unsigned char*) (g_7f4ca0 + g_774970 * 0x21c + 9) != 0 ? 0x28 : 0) + 0x253 +
						     *(unsigned char*) (g_7f4ca0 + g_774970 * 0x21c + 0x169),
					     a2 + 0x16b7, color);
				break;
			}
			flag = 1;
		}
	} else {
		io_AppendText(0x16b4, color, a2 + 0x16b7);
	}
	do {
		if (slot != 0 && found != -1) {
			Tbebe t;
			float dur;

			t = *(Tbebe*) (slot + 0x44);
			fcn_00500bb0(&t, 5, 0, 0);
			dur = (float) fcn_00500d20(slot + 0x44, slot + 0x52);
			*(float*) (g_1015ea0 + found * 0x2f4 + 500) =
				(float) fcn_00500d20(slot + 0x44, (void*) &g_7f4c00) / dur;
		}
		if (g_14ce8e0 != 0 && g_7725d0 == 0) {
			g_774654 = 1;
		}
		if (g_100f1dc == 2) {
			if (flag) {
				fcn_004c6ae0(*(int*) (g_7f4ca0 + g_774970 * 0x21c + 4), -color);
				msg.b36 = 1;
				msg.b4 = 0x60;
				msg.b5a = (unsigned char) a2;
				msg.f8 = *(int*) (g_7f4ca0 + g_774970 * 0x21c + 4);
				msg.fc = *(int*) (g_7f4ca0 + g_774970 * 0x21c + 4);
				fcn_004c5530(&msg);
				fcn_0057e880(0x2c, 0, 0, a2);
				g_774654 = 1;
			}
		} else if (g_100f1dc == 1) {
			g_774654 = 1;
		}
	} while (fcn_005373e0((void*) fcn_005bebe0, 0x677c7) != 0);
	fcn_00532ef0();
	fcn_00471e30(h);
}
