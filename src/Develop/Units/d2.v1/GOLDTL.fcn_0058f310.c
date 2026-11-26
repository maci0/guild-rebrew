#include "client_types.h"
#include "Develop/DieGildeAddOn/game/entity_record.h"
extern int d2_CurrentWindowId;
#include "Develop/DieGildeAddOn/game/game_player.h"
extern int g_100f1dc;
extern int d2_CurrentElementId;
extern int g_14ce8e0;
#include "client_dialog_state.h"
extern int main_LoopFlags;
extern int g_14b556c;
extern int g_14b5574;
extern int g_14b5588;
extern int gm_GameTime;
extern int g_7f4c04;
extern int g_7f4c08;
extern short g_7f4c0c;
extern char g_7f4ca0[];
extern char g_7f4ca4[];

void* __cdecl fcn_005cd440(void*, char*, int, int);
int __cdecl fcn_00532ef0(void);
void __cdecl fcn_0052a0c0(char*, int);
int __cdecl fcn_00470820(int, int, char*);
void __cdecl d2_SetOverlayAnimation(int, int);
void __cdecl d2_CenterDialogWindows(int);
void __cdecl d2_SetForm(int, int);
void __cdecl fcn_005340f0(int);
int __cdecl io_AppendText(int, ...);
int __cdecl d2_GetWindowListItem(int, int, int);
void __cdecl fcn_00472380(int, int, int, int);
int __cdecl d2_GetControlValue(int);
int __cdecl fcn_00525f60(char*, int);
void __cdecl fcn_00526120(int, int);
typedef struct F8 {
	int mask;
	int b;
} F8;
/* SIZE 0x8 */
int __cdecl fcn_004a5e60(char*, int, F8, int, float, int*);
int __cdecl fcn_004c5530(void*);
int __cdecl fcn_004c4450(int);
int __cdecl main_RunFrameLoop(void*, int);
void __cdecl fcn_00471e30(int);
void __cdecl fcn_0052a2d0(void);
void __cdecl sv_ClearObjectSelection(void);

/* ADDRESS: GOLDTL 0x0058f310 */
int __cdecl d2_ShowHauntingDialog(char* subject)
{
	int q[20];
	char req[0xf8];
	int flag;
	int b1;
	int b2;
	int b3;
	int n;

	int i;

	int id;
	int h;
	char* v;
	char* hh;

	for (i = 0; i < 20; i++) {
		q[i] = 0;
	}
	for (i = 7; i < 15; i++) {
		q[i] = -1;
	}
	q[0] = 1;
	q[1] = 0x400;
	q[4] = 6;
	v = (char*) fcn_005cd440(q, (char*) g_14b5574, 0, 0);
	if (v == 0) {
		return fcn_00532ef0();
	}
	fcn_0052a0c0(subject, 0);
	h = fcn_00470820(0, 0, (char*) 0x6a96d8);
	d2_SetOverlayAnimation(0, 0);
	d2_CenterDialogWindows(h);
	d2_SetForm(h, 0);
	fcn_005340f0(d2_CurrentWindowId);
	d2_SetForm(h, 1);
	n = io_AppendText(0x4098, 0x4097, *(unsigned short*) v, *(unsigned short*) v);
	b1 = d2_GetWindowListItem(h, 1, n);
	d2_SetForm(h, 2);
	n = io_AppendText(0x4099);
	b2 = d2_GetWindowListItem(h, 2, n);
	b3 = d2_GetWindowListItem(h, 2, n + 1);
	fcn_00472380(b1, 4, 0xc, 4);
	g_100f1dc = -1;
	do {
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
		} else if (g_100f1dc != -1) {
			if (d2_CurrentElementId == b2) {
				flag = 0;
				n = d2_GetControlValue(b1);

				if (fcn_00525f60(((char*)&((ENTITY_RECORD*)g_7f4ca0)[g_774970]), n) == 0) {
					flag = 1;
				}
				hh = 0;
				for (i = 0; i < 768; i++) {
					if (*(unsigned char*) ((char*)&((ENTITY_RECORD*)g_7f4ca0)[i].unk_17c[0xc]) != 0) {
						hh = ((char*)&((ENTITY_RECORD*)g_7f4ca0)[i]);
						break;
					}
				}
				if (hh == 0) {
					fcn_00526120(g_14b556c, 0);
				} else if (flag == 0) {
					for (i = 0; i < 0x3e; i++) {
						*(int*) (req + i * 4) = 0;
					}
					req[4] = (char) 0x88;
					req[0x36] = 2;
					*(int*) (req + 0x64) = n;
					*(int*) (req + 8) = *(int*)&((ENTITY_RECORD*)(g_7f4ca4 - 4))[*(unsigned short*) (subject + 0x27)].entity_id;
					*(int*) (req + 0xc) = *(int*) (subject + 1);
					*(int*) (req + 0x28) = gm_GameTime;
					*(int*) (req + 0x2c) = g_7f4c04;
					*(int*) (req + 0x30) = g_7f4c08;
					*(short*) (req + 0x34) = g_7f4c0c;
					*(int*) (req + 0x5c) = *(int*) (v + 4);
					*(int*) (req + 0x60) = *(int*) (hh + 4);
					*(int*) (req + 0x38) = *(int*) (hh + 4);
					if (*(int*) (v + 0x170) != 0) {
						*(int*) (req + 0x58) = *(int*) (*(int*) (v + 0x170) + 1);
					} else if (*(int*) (v + 0x16c) != 0) {
						*(int*) (req + 0x58) = *(int*) (*(int*) (v + 0x16c) + 1);
					} else {
						F8 f;
						flag = -1;
						f.mask = 0x7b4c4a0;
						f.b = 0;
						fcn_004a5e60(((char*)&((ENTITY_RECORD*)g_7f4ca0)[g_774970]), 0, f, 0,
						    100.0f, &flag);
						*(int*) (req + 0x58) = flag;
					}
					id = fcn_004c5530(req);
					while (id != -1 && fcn_004c4450(id) == 0) {
						main_RunFrameLoop(0, 0x20007);
					}
					main_LoopFlags = 0x677c7;
					g_774654 = 1;
					fcn_00526120(g_14b5588, 0);
				}
			} else if (d2_CurrentElementId == b3) {
				g_774654 = 1;
			}
		}
	} while (main_RunFrameLoop((void*) d2_ShowHauntingDialog, 0x677c7) != 0);
	fcn_00471e30(h);
	fcn_0052a2d0();
	sv_ClearObjectSelection();
	return fcn_00532ef0();
}
