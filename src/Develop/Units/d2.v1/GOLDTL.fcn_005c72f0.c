#include "client_types.h"
#include "Develop/Units/d2.v1/d2_training_rows.h"
extern Slot_778da0 g_778da0[16];
extern Slot_778da0 g_7796e0[16];
#include "client_data.h"
/*
 * Open the trade-goods dialogue for the object a0 and run its modal loop.
 * Creates (or reuses) the dialog slot, fills the four product rows and the
 * container list, then dispatches clicks until the dialog closes.
 */

extern char* g_item_def_table; /* 0x0099ec10 */
extern int g_14aba94;          /* 0x014aba94 */
extern int g_14aba98;          /* 0x014aba98 */
extern int g_14aba9c;          /* 0x014aba9c */
extern int g_14abaa0;          /* 0x014abaa0 */
extern int g_14ce8cc;          /* 0x014ce8cc */
extern int g_14ce8e0;          /* 0x014ce8e0 */
extern int d2_HoveredWindow;          /* 0x0100f894 */
extern int g_100f1dc;          /* 0x0100f1dc */
extern char* g_1015ea0;          /* 0x01015ea0 */
extern int d2_CurrentElementId;           /* 0x0067d370 */
extern int d2_CurrentWindowId;           /* 0x00772514 */
extern unsigned char g_773d75; /* 0x00773d75 */
#include "client_dialog_state.h"           /* 0x00774654 */
extern int g_775334;           /* 0x00775334 */
extern int main_LoopFlags;           /* 0x007e46ac */
extern char s_6ac7b0[];        /* 0x006ac7b0 */

int __cdecl fcn_00525fb0(int);
int __cdecl fcn_00502cd0(int, int, int, int, int);
int __cdecl fcn_00526120(int, int);
int __cdecl fcn_00470820(int, int, char*);
void __cdecl d2_CenterDialogWindows(int);
void __cdecl d2_SetForm(int, int);
int __cdecl io_AppendText(int, ...);
void __cdecl d2_ResetTrainingRows(int);
int __cdecl d2_SetOverlayAnimation(int, int);
int __cdecl fcn_00594340(void);
int __cdecl d2_DrawPanelFrame(int, int, int);
int __cdecl fcn_00472830(int, int, int, int*, int*, int*);
int __cdecl fcn_00533f40(int, int, int, int);
int __cdecl fcn_00595e20(int, int);
int __cdecl fcn_005963f0(int, int, int, int);
int __cdecl fcn_005974e0(int, int);
int __cdecl fcn_00597940(int, int, int, int, int);
int __cdecl d2_GetControlValue(int);
int* __cdecl fcn_004ce590(int);
int* __cdecl gm_GetEquippedCombatGear(int);
int __cdecl fcn_005c7270(int, int);
int __cdecl cm_SendSellObjekt(int, int, int, int, char, int);
int __cdecl fcn_00472380(int, int, int, int, int);
void __cdecl cm_BeginCommandSync(void);
void __cdecl cm_EndCommandSync(void);
int __cdecl cm_AreQueuedCommandsDone(void);
void __cdecl fcn_00535960(void);
void __cdecl d2_ClearSelectedControl(void);
int __cdecl ch_UpdateHeldObjectAttachment(int);
int __cdecl d2_UpdateTrainingRows(int, int);
int __cdecl fcn_0046f940(int, char*);
int __cdecl fcn_00471e30(int);
int __cdecl main_RunFrameLoop(int, int);
void __cdecl fcn_00532ef0(void);
int __cdecl CountDisplayCounters(void);
void __cdecl ResetDisplayCounters(void);
int __cdecl __itoa(int, char*, int);
#include "Develop/Units/d2.v1/d2_gui.h"
/* ADDRESS: GOLDTL 0x005c72f0 */
int __cdecl fcn_005c72f0(int objectArg)
{
	int v7;
	int v8;
	int v9buf[1];
	int v10[1];
	char v11[256];
	int v13;
	int v14;
	int v15;
	int v16;
	int v17;
	int v18;
	int v19;
	int v20;
	int v21;
	int v22;
	int v23;
	int v24;
	int v25; int selected;
	unsigned short* p;
	char* def;
	char* list;
	int* p4;
	int* rec;
	int win;

	v7 = objectArg;
	v15 = 0;
	v8 = -1;
	v15 = fcn_00525fb0(objectArg);
	if (v15 != 0) {
		return v15;
	}
	v18 = (main_LoopFlags & 0x10000) != 0 ? 0x7d6c6 : 0x677c7;




	p = (unsigned short*) fcn_00502cd0(*(int*) (v7 + 0x5d), 2, 0, 0x2a, 6);
	if (p == 0) {
		p = (unsigned short*) fcn_00502cd0(*(int*) (v7 + 0x5d), 2, 0, 0x116, 6);
	}
	if (p == 0) {
		v15 = fcn_00526120(g_14aba98, 0);
		return v15;
	}
	win = fcn_00470820(0, 0, s_6ac7b0);
	d2_CenterDialogWindows(win);
	d2_SetForm(win, 3);
	io_AppendText(0x19db);
	d2_ResetTrainingRows(v7);
	d2_SetOverlayAnimation(0, 0);
	fcn_00594340();
	d2_SetForm(win, 0);
	d2_DrawPanelFrame(d2_CurrentWindowId, 0x72f, 0);
	fcn_00533f40(0x270, 0x15c, d2_CurrentWindowId,
			fcn_00472830(win, 2, 0x78, v10, v9buf, &v8));
	((D2_CONTROL_TL*) (g_1015ea0))[v8].font = 0x54;
	def = g_item_def_table + (unsigned int) *p * 0x41;
	v16 = win * 0xaf;
label_5c7466:
	v7 = objectArg;
	if (*p != 0x116 && *def != 0x11) {
		if (*def == 0x05) {
			v15 = fcn_00595e20(objectArg, (int) p);
			fcn_005963f0(win, 1, 1, v7);
		}
	} else {
		v15 = fcn_005974e0(objectArg, (int) p);
		fcn_00597940(win, 1, 1, v7, (int) p);
	}
	if (g_100f1dc != -1 && v15 != 0) {
		v7 = 0;
		p4 = (int*) ((int) g_7774a0 + 0x8);
		for (;;) {
			if (p4[-2] != 0 && *p4 == d2_CurrentElementId) {
				selected = g_7774a0[v7].entity;
				if (selected != 0) {
					cm_BeginCommandSync();
					d2_ClearSelectedControl();
					v7 = 0; rec = (int*) ((char*) g_778da0 + 0x10);
					goto label_5c752a;
				}
				break;
			}
			p4 += 0x10;
			v7 += 1;
			if ((int) p4 >= 0x777ca8) {
				break;
			}
		}
	}
	goto label_5c76eb;
label_5c752a:
	do {
		int v5;
		v5 = *rec;
		if (v5 != -1 && d2_GetControlValue(v5) != 0) {
			v5 = rec[-4];
			if (fcn_004ce590(v5) != 0) {
				if (*(int*) gm_GetEquippedCombatGear(selected) != 0) {
					fcn_00526120(g_14aba9c, 4);
					goto label_5c7572;
				}
				v7 *= 0x38;
				v13 = *(int*) (v7 + ((int) g_778da0 + 0x0));
				v5 = fcn_005c7270(selected, v13);
				if (v5 != 0) {
					cm_SendSellObjekt(*(int*) (selected + 4), *(int*) &p[1], v13, 1,
							g_773d75, 0);
					v5 = d2_GetControlValue(*(int*) (v7 + ((int) g_778da0 + 0x10)));
					fcn_00472380(*(int*) (v7 + ((int) g_778da0 + 0x10)), 0,
							*(int*) (v7 + ((int) g_778da0 + 0x30)), v5 - 1, 0);
					break;
				}
				v14 = 4;
				v13 = g_14abaa0;
			} else {
				v14 = 0;
				v13 = g_14aba94;
			}
			fcn_00526120(v13, v14);
			break;
		}
label_5c7572:
		rec += 0xe;
		v7 += 1;
	} while ((int) rec < ((int) g_778da0 + 0x390));
	v7 = 0;
	rec = (int*) ((int) g_7796e0 + 0x10);
	do {
		int v5;
		v5 = *rec;
		if (v5 != -1 && d2_GetControlValue(v5) != 0) {
			v7 *= 0x38;
			v13 = *(int*) (v7 + ((int) g_7796e0 + 0x0));
			if (fcn_004ce590(v13) != 0) {
				v13 = *(int*) (v7 + ((int) g_7796e0 + 0x0));
				v5 = fcn_005c7270(selected, v13);
				if (v5 != 0) {
					cm_SendSellObjekt(*(int*) (selected + 4), *(int*) &p[1], v13, 1,
							g_773d75, 0);
					v5 = d2_GetControlValue(*(int*) (v7 + ((int) g_7796e0 + 0x10)));
					fcn_00472380(*(int*) (v7 + ((int) g_7796e0 + 0x10)), 0,
							*(int*) (v7 + ((int) g_7796e0 + 0x30)), v5 - 1, 0);
					break;
				}
				v13 = g_14abaa0;
			} else {
				v13 = g_14aba94;
			}
			fcn_00526120(v13, 0);
			break;
		}
		rec += 0xe;
		v7 += 1;
	} while ((int) rec < ((int) g_7796e0 + 0x1d0));
	cm_EndCommandSync();
	v7 = cm_AreQueuedCommandsDone();
	while (v7 == 0) {
		fcn_00535960();
		v7 = cm_AreQueuedCommandsDone();
	}
	ch_UpdateHeldObjectAttachment(selected);
label_5c76eb:
	v7 = d2_UpdateTrainingRows(win, 2);
	if (d2_HoveredWindow == g_1038140[win].wins[1] && v7 != 0 && g_14ce8cc != 0) {
		cm_BeginCommandSync();
		p4 = (int*) ((int) g_7774a0 + 0x0);
		do {
			if (*p4 != 0) {
				int* q;
				int n;
				q = &p4[4];
				n = 6;
				do {
					if (*q != -1 && d2_GetControlValue(*q) != 0) {
						cm_SendSellObjekt(*(int*) &p[1], *(int*) (*p4 + 4),
								q[1], 1,
								g_773d75,
								0);
					}
					q += 2;
					n -= 1;
				} while (n != 0);
			}
			p4 += 0x10;
		} while ((int) p4 < ((int) g_7774a0 + 0x800));
		cm_EndCommandSync();
		v7 = cm_AreQueuedCommandsDone();
		while (v7 == 0) {
			fcn_00535960();
			v7 = cm_AreQueuedCommandsDone();
		}
		p4 = (int*) ((int) g_7774a0 + 0x0);
		do {
			if (*p4 != 0) {
				ch_UpdateHeldObjectAttachment(*p4);
			}
			p4 += 0x10;
		} while ((int) p4 < ((int) g_7774a0 + 0x800));
	}
	__itoa(g_775334, v11, 10);
	fcn_0046f940(v8, v11);
	if (g_14ce8e0 != 0) {
		if (CountDisplayCounters() == 0) {
			g_774654 = 1;
		} else {
			int* q;
			ResetDisplayCounters();
			q = (int*) ((int) g_778da0 + 0x10);
			do {
				v7 = *q;
				if (v7 != -1 && d2_GetControlValue(v7) != 0) {
					fcn_00472380(*q, 0, q[8], 0, 0);
				}
				q += 0xe;
			} while ((int) q < ((int) g_778da0 + 0x390));
			q = (int*) ((int) g_7796e0 + 0x10);
			do {
				v7 = *q;
				if (v7 != -1 && d2_GetControlValue(v7) != 0) {
					fcn_00472380(*q, 0, q[8], 0, 0);
				}
				q += 0xe;
			} while ((int) q < ((int) g_7796e0 + 0x1d0));
			p4 = (int*) ((int) g_7774a0 + 0x10);
			do {
				if (p4[-4] != 0) {
					int* q2;
					int n;
					v7 = 6;
					q2 = p4;
					do {
						if (*q2 != -1) {
							fcn_00472380(*q2, 0, 0, 0, 0);
						}
						q2 += 2;
						v7 -= 1;
					} while (v7 != 0);
				}
				p4 += 0x10;
			} while ((int) p4 < 0x777cb0);
		}
	}
	v7 = main_RunFrameLoop(0x5c72f0, v18);
	if (v7 != 0) {
		goto label_5c7466;
	}
	fcn_00471e30(win);
	fcn_00532ef0();
}
