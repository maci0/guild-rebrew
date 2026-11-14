#include <string.h>
#include "client_types.h"
#include "Develop/DieGildeAddOn/game/game_player.h"
#include "Develop/Units/d2.v1/d2_gui.h"

/* 0xf8-byte message panel record handed to fcn_004c5530. */
typedef struct {
	int f0;                     /* 0x00 */
	unsigned char b4;           /* 0x04 */
	char pad5[3];
	int f8;                     /* 0x08 */
	int fc;                     /* 0x0c */
	char pad10[0x18];           /* 0x10 */
	pos14_7f4c00 pos;           /* 0x28 */
	unsigned char b36;          /* 0x36 */
	char pad37[0x21];           /* 0x37 */
	int val;                    /* 0x58 */
	int target_id;              /* 0x5c */
	char pad60[0x98];           /* 0x60 */
} Panel_5e5a50;                 /* SIZE 0xf8 */

extern char g_6811b0[];
extern int g_772514;
extern unsigned short g_774970;
extern unsigned char g_773d75;
extern pos14_7f4c00 g_7f4c00;
extern char g_7f4ca0[];
extern char g_7f4ca4[];
extern int g_100f1dc;
extern int g_666018;

int __cdecl fcn_004c3030(int, int, char*, int);
void __cdecl fcn_005263d0(int, int, int);
char* __cdecl fcn_005cd440(int*, int, int, void*);
void __cdecl fcn_00532ef0(void);
int __cdecl fcn_00470820(int, int, char*);
void __cdecl d2_SetOverlayAnimation(int, int);
void __cdecl fcn_00471b60(int);
void __cdecl d2_SetForm(int, int);
void __cdecl fcn_005340f0(int);
int __cdecl fcn_004677e0(int, int, int, int, int, int, int, int);
void __cdecl fcn_00468bb0(int, int, ...);
void __cdecl fcn_00533a60(int, int, int*, int, ...);
int __cdecl fcn_00510470(char*);
int __cdecl fcn_00471f80(int);
void __cdecl io_FormatTextBuffer(char*, int, ...);
int __cdecl io_AppendText(int, ...);
int __cdecl fcn_00526010(char*, int, unsigned char);
void __cdecl fcn_004c5420(int, int, int, int, int);
void __cdecl fcn_004c51a0(int, int, unsigned char, int);
void __cdecl fcn_004c5530(void*);
int __cdecl fcn_0064d41a(char*, char*, ...);
void __cdecl fcn_00526120(char*, int);
int __cdecl fcn_005373e0(void*, int);
void __cdecl fcn_00471e30(int);

/* ADDRESS: GOLDTL 0x005e5a50 */
void __cdecl fcn_005e5a50(char* entity)
{
	char text[512];
	char buf[100];
	Panel_5e5a50 pkt;
	int query[20];
	int ids[2];
	int control;
	int dialog;
	char* target;
	int max_val;
	int val;

	if ((unsigned char) g_7f4ca0[g_774970 * 0x21c + 0x1cc] & 0x10) {
		fcn_004c3030(-7, 0, (char*) 0x6ad46c, -1);
		fcn_005263d0(*(int*) 0x14b5a24, *(int*) 0x14b5a28, 0);
		return;
	}
	memset(query, 0, sizeof(query));
	memset(query + 7, -1, 8 * sizeof(int));
	query[2] = g_666018;
	query[3] = *(int*) 0x66601c;
	query[0] = 1;
	query[1] = 0x400;
	query[4] = 6;
	target = fcn_005cd440(query, *(int*) 0x14b5a2c, 0, 0);
	if (target == 0) {
		fcn_00532ef0();
		return;
	}
	dialog = fcn_00470820(0, 0, (char*) 0x6ad434);
	d2_SetOverlayAnimation(0, 0);
	fcn_00471b60(dialog);
	d2_SetForm(dialog, 0);
	fcn_005340f0(g_772514);
	d2_SetForm(dialog, 2);
	control = fcn_004677e0(0x57, 7, 200, 0, 100, 0x7b, 2, g_772514);
	d2_SetElementValue(control, 0, 5, 0, 1);
	fcn_00468bb0(control, 6, *(int*) 0x14b5a48, *(int*) 0x14b5a4c,
	             *(int*) 0x14b5a50, *(int*) 0x14b5a54,
	             *(int*) 0x14b5a58, *(int*) 0x14b5a5c);
	d2_SetForm(dialog, 3);
	fcn_00533a60(g_772514, 0, ids, 2, *(int*) 0x14b5a80, *(int*) 0x14b5a84);
	do {
		max_val = fcn_00510470(entity) - 1;
		val = fcn_00471f80(control);
		if (val >= max_val) {
			val = max_val;
		}
		d2_SetElementValue(control, 0, max_val, val, 1);
		io_FormatTextBuffer(text, val + 0x41d0, *(unsigned short*) target);
		d2_SetForm(dialog, 1);
		io_AppendText((int) g_6811b0);
		io_AppendText(0x41d6, 0x41c1, val + 0x41c4, text);
		if (g_774970 != *(unsigned short*) (entity + 0x27)) {
			io_AppendText(0x41d7, (val > 1 ? val : 1) * 32000);
		}
		if (*(int*) 0x14ce8e0 != 0) {
			*(int*) 0x774654 = 1;
		} else if (g_100f1dc != -1) {
			int clicked = *(int*) 0x67d370;
			if (clicked == ids[0]) {
				if (fcn_00526010(g_7f4ca0 + g_774970 * 0x21c, val, g_773d75) != 0) {
					fcn_004c5420(*(int*) (g_7f4ca4 + g_774970 * 0x21c), 0x1cc, 4, 0x10, 0);
					if (g_774970 != *(unsigned short*) (entity + 0x27)) {
						fcn_004c51a0(-1, *(int*) (g_7f4ca4 + g_774970 * 0x21c),
						             g_773d75, (val > 1 ? val : 1) * 32000);
					}
					memset(&pkt, 0, sizeof(pkt));
					pkt.b4 = 0x9d;
					pkt.fc = -1;
					pkt.b36 = 2;
					pkt.val = val;
					pkt.f8 = *(int*) (g_7f4ca4 + g_774970 * 0x21c);
					pkt.pos = g_7f4c00;
					pkt.target_id = *(int*) (target + 4);
					fcn_004c5530(&pkt);
					io_FormatTextBuffer(text, 0x41da, 0x41c1);
					fcn_0064d41a(buf, (char*) 0x6ad454, val);
					fcn_004c3030(-7, 0, buf, -1);
					fcn_00526120(text, 0);
					*(int*) 0x774654 = 1;
				}
			} else if (clicked == ids[1]) {
				*(int*) 0x774654 = 1;
			}
		}
	} while (fcn_005373e0((void*) fcn_005e5a50, 0x677c7) != 0);
	fcn_00471e30(dialog);
	fcn_00532ef0();
}
