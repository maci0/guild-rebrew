#include <string.h>
extern char* lpGebaeudePROT;
extern char* lpObjektePROT;
#include "Develop/Units/d2.v1/d2_gui.h"
extern int d2_CurrentWindowId;
extern int g_7f4c04;
extern int g_7f4c08;
extern short g_7f4c0c;
extern int g_100f1dc;
extern int g_14b556c;
extern int g_774654;
extern int main_LoopFlags;
extern int d2_CurrentElementId;
extern int g_14ce8e0;
#include "Develop/DieGildeAddOn/game/building_prototype.h"
int __cdecl fcn_00502cd0(int, int, ...);
int __cdecl d2_CheckOwnerBlocked(int);
int __cdecl he_StartHandlungSearch(int, int, int, int, int);
int __cdecl he_fn_Handlung(void);
void* __cdecl fcn_00470820(int, int, char*);
void __cdecl d2_CenterDialogWindows(int);
void __cdecl d2_SetForm(int, int);
void __cdecl d2_DrawPanelFrame(int, int, int);
int __cdecl io_AppendText(int, ...);
void __cdecl fcn_0052a0c0(int, int);
void __cdecl fcn_00594340(void);
int __cdecl d2_AddElementToWindow(int, int, int, int);
void __cdecl fcn_0046f9b0(int, int);
void __cdecl fcn_00472640(int, int);
void __cdecl d2_SetOverlayAnimation(int, int);
void __cdecl fcn_00595e20(int, int);
void __cdecl fcn_005963f0(int, int, int, int);
int __cdecl main_RunFrameLoop(int, int);
void __cdecl io_FormatTextBuffer(void*, int, ...);
int __cdecl cm_SendCopyEntityData(void*);
int __cdecl cm_GetCommandStatus(int);
void __cdecl sv_ClearObjectSelection(void);
void __cdecl fcn_00526120(int, int);
void __cdecl d2_RestoreHudAfterDialog(void);
void __cdecl fcn_00471e30(int);
void __cdecl fcn_00532ef0(void);

/* SIZE 0xf8 */
typedef struct {
	char pad0[4];
	unsigned char kind;	/* +0x04 */
	char pad5[3];
	unsigned int owner;	/* +0x08 */
	unsigned int self;	/* +0x0c */
	char pad10[0x18];
	int date0;		/* +0x28 */
	int date1;		/* +0x2c */
	int date2;		/* +0x30 */
	unsigned short date3;	/* +0x34 */
	unsigned char flag;	/* +0x36 */
	char pad37;
	unsigned int list[4];	/* +0x38 */
	char pad48[0x10];
	unsigned short good;	/* +0x58 */
	char pad5a[0x9e];
} Req_58d5f0;

/* ADDRESS: GOLDTL 0x0058d5f0 */
void __cdecl fcn_0058d5f0(unsigned char* gebaeude)
{
	Req_58d5f0 req;
	unsigned int ids[4];
	int counts[4];
	int handles[4];
	char text[224];
	unsigned char* p;
	unsigned char* vp;
	char* ents;
	int* q;
	int h;
	int i;
	int j;
	int n;
	int menu;
	int sel;
	int count;
	int screen;

	ids[2] = 0x227;
	handles[3] = fcn_00502cd0(*(unsigned int*) (gebaeude + 0x5d), 2, 6, 0, 0x2a);
	n = 2;
	ents = (char*)&((BUILDING_PROTOTYPE*)lpGebaeudePROT)[(unsigned int) *gebaeude];
	if (((char)(((BUILDING_PROTOTYPE*)ents)->category)) == 0x1f) {
		ids[0] = 0x293;
		ids[1] = 0x294;
		if ((unsigned char) ((char)(((BUILDING_PROTOTYPE*)ents)->level)) >= 2) {
			ids[2] = 0x295;
			n = 3;
		}
	} else {
		ids[0] = 0x225;
		ids[1] = 0x226;
		if ((unsigned char) ((char)(((BUILDING_PROTOTYPE*)ents)->level)) >= 2) {
			ids[2] = 0x227;
			n = 3;
		}
	}
	if (d2_CheckOwnerBlocked((int) gebaeude))
		return;
	counts[0] = 0;
	counts[1] = 0;
	counts[2] = 0;
	h = he_StartHandlungSearch(2, 0, 0x8c, 3, *(unsigned int*) (gebaeude + 1));
	while (h) {
		unsigned int action = *(unsigned short*) (h + 0xac);
		j = 0;
		do {
			if (action == *(unsigned int*) ((char*) ids + j)) {
				q = (int*) (h + 0x8c);
				for (i = 4; i != 0; i--) {
					if (*q != -1)
						(*(int*) ((char*) counts + j))++;
					q++;
				}
			}
			j += 4;
		} while (j < 0xc);
		h = he_fn_Handlung();
	}
	menu = (int) fcn_00470820(0, 0, "s_6a9750");
	ids[3] = menu;
	d2_CenterDialogWindows(menu);
	d2_SetForm(menu, 0);
	d2_DrawPanelFrame(d2_CurrentWindowId, 0x70f, 0x741);
	d2_SetForm(menu, 3);
	screen = (((char)(((BUILDING_PROTOTYPE*)ents)->category)) != 0x1f) ? 0x4128 : 0x421e;
	io_AppendText(screen);
	fcn_0052a0c0((int) gebaeude, 0);
	fcn_00594340();
	d2_CenterDialogWindows(menu);
	d2_SetForm(menu, 2);
	if (n) {
		i = *(int*) (0x1015f4c + d2_CurrentWindowId * 0x3cc) / 2 - 0x80;
		j = 0x19;
		for (count = 0; count < n; count++) {
			h = d2_AddElementToWindow(i, j, (int) ids[count] + 0xdf, d2_CurrentWindowId);
			vp = (unsigned char*) &((D2_CONTROL_TL*)g_1015ea0)[h];
			*(int*)&((D2_CONTROL_TL*)vp)->value_05c = 1;
			*(int*)&((D2_CONTROL_TL*)vp)->flags_1d0 = 3;
			*(int*)&((D2_CONTROL_TL*)vp)->value_1dc = 100;
			*(int*)&((D2_CONTROL_TL*)vp)->value_1e0 = 0x10;
			*(int*)&((D2_CONTROL_TL*)vp)->font = 0x54;
			fcn_0046f9b0(h, *(int*) (0x14a79c0 + (int) ids[count] * 8));
			handles[count] = h;
			fcn_00472640(h, 1);
			j += 0x50;
		}
		menu = ids[3];
	}
	d2_SetOverlayAnimation(0, 0);
	fcn_00595e20((int) gebaeude, handles[3]);
	fcn_005963f0(menu, 1, 0, (int) gebaeude);
	sel = main_RunFrameLoop(0x58d5f0, 0x677c7);
	while (sel) {
		fcn_00595e20((int) gebaeude, handles[3]);
		fcn_005963f0(menu, 1, 0, (int) gebaeude);
		counts[0] = 0;
		counts[1] = 0;
		counts[2] = 0;
		h = he_StartHandlungSearch(2, 0, 0x8c, 3, *(unsigned int*) (gebaeude + 1));
		while (h) {
			unsigned int action = *(unsigned short*) (h + 0xac);
			j = 0;
			do {
				if (action == *(unsigned int*) ((char*) ids + j)) {
					q = (int*) (h + 0x8c);
					for (i = 4; i != 0; i--) {
						if (*q != -1)
							(*(int*) ((char*) counts + j))++;
						q++;
					}
				}
				j += 4;
			} while (j < 0xc);
			h = he_fn_Handlung();
		}
		d2_SetForm(menu, 2);
		if (n) {
			for (i = 0; i < n; i++) {
				fcn_00472640(handles[i], 1);
				if (((char)(((BUILDING_PROTOTYPE*)ents)->category)) != 0x1f) {
					h = ids[i] * 2 + 0x9a8;
					if (counts[i] == 1) {
						io_FormatTextBuffer(text, 0x4129, 0x228, h);
					} else if (counts[i] > 1) {
						io_FormatTextBuffer(text, 0x412a, counts[i], 0x228, h);
					} else {
						io_FormatTextBuffer(text, 0x679060, h);
					}
				} else if (counts[i] == 1) {
					io_FormatTextBuffer(text, 0x421f, 0x22d, ids[i] * 2 + 0x9a8);
				} else if (counts[i] >= 2) {
					io_FormatTextBuffer(text, 0x4220, counts[i], 0x22d, ids[i] * 2 + 0x9a8);
				} else {
					io_FormatTextBuffer(text, 0x679060, ids[i] * 2 + 0x9a8);
				}
				fcn_0046f9b0(handles[i], text);
			}
		}
		if (g_100f1dc != -1) {
			for (sel = 0; sel < n; sel++) {
				if (handles[sel] == d2_CurrentElementId)
					break;
			}
			if (sel < n) {
				memset(&req, 0, sizeof(req));
				req.kind = 0x8c;
				req.flag = 1;
				req.owner = *(unsigned int*) (*(unsigned short*) (gebaeude + 0x27) * 0x21c + 0x7f4ca4);
				req.self = *(unsigned int*) (gebaeude + 1);
				req.date0 = *(int*) 0x7f4c00;
				req.date1 = g_7f4c04;
				req.date2 = g_7f4c08;
				req.date3 = g_7f4c0c;
				req.good = (unsigned short) ids[sel];
				j = 0;
				p = (unsigned char*) 0x7f4ca4;
				do {
					if (j > 3)
						break;
					if (p[0x184]) {
						req.list[j] = *(unsigned int*) p;
						j++;
					}
					p += 0x21c;
				} while ((int) p < 0x85a0a4);
				for (i = j; i < 4; i += 2) {
					req.list[i] = 0xffffffff;
				}
				if (j) {
					h = cm_SendCopyEntityData(&req);
					if (h != -1) {
						while (!cm_GetCommandStatus(h)) {
							main_RunFrameLoop(0, 0x20007);
						}
					}
					main_LoopFlags = 0x677c7;
					sv_ClearObjectSelection();
				} else {
					fcn_00526120(g_14b556c, 4);
					sv_ClearObjectSelection();
				}
				goto next;
			}
		} else if (g_14ce8e0) {
			g_774654 = 1;
		}
next:
		sel = main_RunFrameLoop(0x58d5f0, 0x677c7);
		menu = ids[3];
	}
	sv_ClearObjectSelection();
	d2_RestoreHudAfterDialog();
	fcn_00471e30(menu);
	fcn_00532ef0();
}
