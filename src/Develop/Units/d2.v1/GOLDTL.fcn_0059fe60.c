#include <string.h>
#include "Develop/DieGildeAddOn/game/game_player.h"
#include "client_dialog_state.h"

/* SIZE 0x21c */
typedef struct {
	char p0[4];
	int f4;
	char p8;
	unsigned char b9;
	char pa[0x21c - 0xa];
} Slot59fe;

extern Slot59fe g_7f4ca0[];
extern int g_772514;
extern int g_100f1dc;
extern int g_14ce8e0;
extern int g_67d370;
extern int g_666018;
extern int g_66601c;

void __cdecl fcn_005338a0(void);
int __cdecl fcn_00470820(int, int, char *);
void __cdecl d2_SetForm(int, int);
void __cdecl fcn_005340f0(int);
void __cdecl fcn_00471b60(int);
void __cdecl d2_SetOverlayAnimation(int, int);
int __cdecl io_AppendText();
int __cdecl fcn_00472250(int, int, int);
char *__cdecl fcn_005463a0(int, int, int);
char *__cdecl he_fn_Handlung(void);
char *__cdecl gm_LookupEntityRecordById(int);
void __cdecl fcn_00472640(int, int);
void __cdecl io_FormatTextBuffer(char *, int, ...);
unsigned short *__cdecl fcn_005cd440(int *, char *, char *, int);
int __cdecl fcn_00526120(char *, int);
void __cdecl fcn_004c5530(char *);
void __cdecl fcn_00471af0(int, int);
void __cdecl fcn_0059fa80(Slot59fe *, char *, char *);
int __cdecl fcn_005373e0(void *, int);
void __cdecl fcn_00471e30(int);
void __cdecl fcn_00532ef0(void);

/* Residence ("Wohnsitz") dialog: lists the player's lovers' residences as
 * buttons and runs the dialog loop until it closes. */
/* ADDRESS: GOLDTL 0x0059fe60 */
void __cdecl fcn_0059fe60(char *a0)
{
	int item;
	int ids[4];
	int buttons[4];
	int acts[4];
	int avail[4];
	int box[0x14];
	char msg[0xf8];
	char text_b[0x3c];
	char text_a[0x44];
	char text_c[0x200];
	int dlg;
	int n;
	int i;
	char *ent;
	char *act;
	unsigned short *sel;

	buttons[0] = -1;
	buttons[1] = -1;
	buttons[2] = -1;
	buttons[3] = -1;
	fcn_005338a0();
	dlg = fcn_00470820(0, 0, "locations\\wohnsitz\\geliebte");
	d2_SetForm(dlg, 0);
	fcn_005340f0(g_772514);
	fcn_00471b60(dlg);
	d2_SetOverlayAnimation(0, 0);
	d2_SetForm(dlg, 2);
	item = fcn_00472250(dlg, 2, io_AppendText(g_7f4ca0[g_774970].b9 == 0 ? 0x1a50 : 0x1a51));
	g_100f1dc = -1;
	do {
		acts[0] = -1;
		acts[1] = -1;
		ids[0] = -1;
		acts[2] = -1;
		ids[1] = -1;
		acts[3] = -1;
		ids[2] = -1;
		ids[3] = -1;
		n = 0;
		for (ent = fcn_005463a0(1, 0, 0x6f); ent != 0 && n < 4; ent = he_fn_Handlung()) {
			if (*(int *) (ent + 0xac) == g_7f4ca0[g_774970].f4) {
				acts[n] = *(int *) (ent + 4);
				if (*(int *) (ent + 0x70) == 0) {
					avail[n] = 1;
				} else {
					avail[n] = 0;
				}
				ids[n] = *(int *) (ent + 0xb0);
				n++;
			}
		}
		d2_SetForm(dlg, 1);
		io_AppendText("$C");
		io_AppendText("$Z$[%s$]$N", 0x1a4e);
		io_AppendText(0x1a4f);
		for (i = 0; i < 4; i++) {
			ent = gm_LookupEntityRecordById(ids[i]);
			if (ent == 0) {
				break;
			}
			buttons[i] = fcn_00472250(dlg, 1, io_AppendText(0x1a52, *(unsigned short *) ent));
			fcn_00472640(buttons[i], avail[i]);
		}
		fcn_00472640(item, n < 4);
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
		} else if (g_100f1dc != -1) {
			if (g_67d370 == item) {
				memset(box, 0, sizeof(box));
				box[4] = 6;
				box[2] = g_666018;
				box[3] = g_66601c;
				box[1] = 0x2040a - (g_7f4ca0[g_774970].b9 != 0);
				io_FormatTextBuffer(text_a, 0x1a53);
				io_FormatTextBuffer(text_b, 0x1a54);
				sel = fcn_005cd440(box, text_a, text_b, 0);
				if (sel != 0) {
					if (g_7f4ca0[g_774970].b9 == 0) {
						io_FormatTextBuffer(text_c, 0x1a55, *sel);
					} else {
						io_FormatTextBuffer(text_c, 0x1a56, *sel);
					}
					if (fcn_00526120(text_c, 1) != 0) {
						memset(msg, 0, sizeof(msg));
						msg[4] = 0x6f;
						msg[0x36] = 2;
						*(int *) (msg + 8) = g_7f4ca0[g_774970].f4;
						*(int *) (msg + 0xc) = *(int *) (a0 + 1);
						*(int *) (msg + 0x5c) = *(int *) (sel + 2);
						*(int *) (msg + 0x58) = g_7f4ca0[g_774970].f4;
						fcn_004c5530(msg);
					}
				}
			} else {
				for (i = 0; i < 4; i++) {
					if (g_67d370 == buttons[i]) {
						ent = gm_LookupEntityRecordById(ids[i]);
						act = fcn_005463a0(1, 1, acts[i]);
						fcn_00471af0(dlg, 0);
						fcn_0059fa80(&g_7f4ca0[g_774970], ent, act);
						fcn_00471af0(dlg, 1);
						break;
					}
				}
			}
		}
	} while (fcn_005373e0((void *) fcn_0059fe60, 0x67fff) != 0);
	fcn_00471e30(dlg);
	fcn_00532ef0();
}
