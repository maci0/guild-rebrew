/* "Locations\zigeuner\blutrache" blood-revenge dialog.
 *
 * Opens the dialog through fcn_00470820, installs the two range timers
 * (fcn_004677e0), fills the two choice ids with fcn_00533a60, then runs the
 * modal frame loop: each pass refreshes the local 0xe-byte UI time stamp from
 * the selected house entity at +0x52 (or from g_7f4c00 when no entity is
 * selected), drives the entity's progress ratio through the 0x500d20
 * stamps and fcn_00472380, updates the markup text through io_AppendText,
 * and on focus id 0 pays out through fcn_00525f60/fcn_005100f0 before filling
 * the 0xf8-byte panel record for fcn_004c5530.
 *
 * The stored row extent (1961 bytes) is wrong: this body ends at 0x5e635f
 * (add esp,0x128; jmp 0x532ef0, 1215 bytes). Bytes 0x5e6360-0x5e664f are a
 * separate dialog callback (frame 0x458, own ret) that the inventory has not
 * split out, so the row cannot be byte-exact until the extent is repaired. */
#include <string.h>

#include "client_types.h"
#include "Develop/DieGildeAddOn/game/game_player.h"
#include "client_dialog_state.h"

#pragma pack(push, 2)
/* 0xe-byte UI time stamp: dword a, 16-bit type at +4, +6, dword d, 16-bit e. */
typedef struct {
	int a;
	unsigned short b;
	unsigned short c;
	int d;
	unsigned short e;
} Stamp;
#pragma pack(pop)

/* 0xf8-byte dialog panel record handed to fcn_004c5530. */
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
	int sel;                    /* 0x58 */
	char pad5c[0x9c];           /* 0x5c */
} Panel;                        /* SIZE 0xf8 */

/* 0x21c-byte house record indexed by g_774970. */
typedef struct {
	int f0;                     /* 0x00 */
	int f4;                     /* 0x04 */
	char pad8[0x180];
	unsigned char b188;         /* 0x188 */
	char pad189[0x93];
} House;                        /* SIZE 0x21c */

extern char s_6ad434[];
extern char s_6811b0[];
extern int g_772514;
extern char* g_77255c;
extern int g_6b7fac;
extern int g_14b5af8;
extern int g_14b5afc;
extern pos14_7f4c00 g_7f4c00;
extern char g_7f4ca0[];
extern int g_14ce8e0;
extern int g_100f1dc;
extern int g_67d370;
extern float g_6628a0;
extern float g_662cf8;

void __cdecl fcn_00500bb0(void*, int, int, int);
int __cdecl fcn_0042e410(int);
int __cdecl fcn_00470820(int, int, char*);
void __cdecl d2_SetOverlayAnimation(int, int);
void __cdecl fcn_00471b60(int);
void __cdecl d2_SetForm(int, int);
void __cdecl fcn_005340f0(int);
int __cdecl fcn_004677e0(int, int, int, int, int, int, int, int);
void __cdecl fcn_00472380(int, int, int, int);
int __cdecl fcn_00510550(char*, ...);
void __cdecl fcn_00533a60(int, int, int*, int, int, int);
int __cdecl fcn_0057c9d0(char*);
int __cdecl fcn_00500d20(void*, void*);
int __cdecl io_AppendText(int, ...);
int __cdecl fcn_00471f80(int);
void __cdecl fcn_00472640(int, int);
void __cdecl fcn_00472170(int, int);
int __cdecl fcn_00525f60(void*, int);
void __cdecl fcn_005100f0(int, int);
void __cdecl fcn_004c5530(void*);
int __cdecl fcn_005373e0(void*, int);
void __cdecl fcn_00471e30(int);
void __cdecl fcn_00532ef0(void);

/* ADDRESS: GOLDTL 0x005e5ea0 */
void __cdecl fcn_005e5ea0(char* participant)
{
	Stamp st;
	int timer2;
	int stage = 2;
	int idx = 0;
	int timer1;
	int ids[2];
	int n;
	int last = 0;
	int value;
	Panel msg;
	char* entity;
	int dlg;
	float f;

	st = *(Stamp*) &g_7f4c00;
	fcn_00500bb0(&st, 0x18, 0, 0);
	st.b = (unsigned short) (fcn_0042e410(stage) + 0x15);
	*(int*) ((char*) &st + 6) = 0;

	dlg = fcn_00470820(0, 0, s_6ad434);
	d2_SetOverlayAnimation(0, 0);
	fcn_00471b60(dlg);
	d2_SetForm(dlg, 0);
	fcn_005340f0(g_772514);
	d2_SetForm(dlg, stage);
	timer1 = fcn_004677e0((*(int*) (g_77255c + 0xc) - 300) / 2, 10, 300, 0, 100, 0x75, 0x42, g_772514);
	fcn_00472380(timer1, 0, 100, 0);
	d2_SetForm(dlg, 2);
	timer2 = fcn_004677e0(0x57, 7, 200, 0, 100, 0x7b, 2, g_772514);
	fcn_00510550(participant);
	fcn_00472380(timer2, 0, fcn_00510550(participant, 0, 1) - 1, 0);
	d2_SetForm(dlg, 3);
	fcn_00533a60(g_772514, 0, ids, stage, g_14b5af8, g_14b5afc);

	for (;;) {
		if (g_6b7fac > last + 0x8c || fcn_00471f80(timer2) != idx) {
			last = g_6b7fac;
			entity = (char*) fcn_0057c9d0(participant);
			if (entity != 0) {
				st = *(Stamp*) (entity + 0x52);
				st.b += *(int*) (entity + 0x70) ? 0 : 2;
				value = fcn_00500d20(entity + 0x44, (void*) 0x7f4c00);
				n = fcn_00500d20(entity + 0x44, &st);
				f = (float) value / (float) n;
				if (!(f < g_6628a0)) {
					f = g_6628a0;
				}
				f = f * g_662cf8;
				fcn_00472380(timer1, 0, 100, (int) f);
			}
			else {
				st = *(Stamp*) &g_7f4c00;
				fcn_00500bb0(&st, 0x18, 0, 0);
				st.b = (unsigned short) (fcn_0042e410(2) + 0x15);
				*(int*) ((char*) &st + 6) = 0;
				fcn_00472380(timer1, 0, 100, 0);
			}
			d2_SetForm(dlg, 1);
			io_AppendText((int) s_6811b0);
			if (entity != 0) {
				if (*(int*) (entity + 0x70) == 0) {
					io_AppendText(0x41f8, 0x41f4, *(int*) (entity + 0xac) + 0x41fb, &st);
				}
				else {
					io_AppendText(0x41f9, 0x41f4);
				}
			}
			else {
				idx = fcn_00471f80(timer2);
				if (idx < 4) {
					stage = 2;
				}
				else {
					stage = (idx >= 7) + 3;
				}
				io_AppendText(0x41f5, 0x41f4, stage, idx + 0x41fb, &st);
			}
			fcn_00472640(ids[0], entity == 0);
			fcn_00472640(ids[1], entity == 0);
			d2_SetForm(dlg, 2);
			fcn_00472170(timer1, entity != 0);
			fcn_00472170(timer2, entity == 0);
		}
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
		}
		else if (g_100f1dc != -1) {
			if (g_67d370 == ids[0]) {
				if (fcn_00525f60(((House*) g_7f4ca0) + g_774970, stage) == 1) {
					fcn_005100f0(((House*) g_7f4ca0)[g_774970].f4, -stage);
					memset(&msg, 0, sizeof(msg));
					msg.b4 = 0xa0;
					msg.b36 = 2;
					msg.f8 = ((House*) g_7f4ca0)[g_774970].f4;
					msg.fc = *(int*) (participant + 1);
					msg.pos = g_7f4c00;
					msg.sel = idx;
					fcn_004c5530(&msg);
					g_774654 = 1;
				}
			}
			else if (g_67d370 == ids[1]) {
				g_774654 = 1;
			}
		}
		if (fcn_005373e0((void*) fcn_005e5ea0, 0x677c7) == 0) {
			break;
		}
	}
	fcn_00471e30(dlg);
	fcn_00532ef0();
}
