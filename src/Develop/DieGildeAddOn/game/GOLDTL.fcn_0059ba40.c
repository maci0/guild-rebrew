#include <string.h>

extern int d2_CurrentWindowId;
extern char g_779160[];
extern char* g_1015ea0;
extern int g_100f1dc;
extern int g_100f884;
extern int d2_CurrentElementId;
extern int g_7746cc;
#include "client_dialog_state.h"
extern int g_14ce8e0;
extern int gm_GameTime;
extern int g_7f4c04;
extern int g_7f4c08;
extern short g_7f4c0c;
#include "Develop/Units/d2.v1/d2_gui.h"
int __cdecl d2_CheckOwnerBlocked(int);
int __cdecl fcn_00470820(int, int, char*);
void __cdecl d2_CenterDialogWindows(int);
void __cdecl fcn_0052a0c0(char*, int);
void __cdecl d2_SetForm(int, int);
int __cdecl io_AppendText(int);
void __cdecl fcn_00594340(void);
void __cdecl d2_DrawPanelFrame(int, int, int);
int __cdecl fcn_00472830(int, int, int, int*, int*, int*);
void __cdecl fcn_00533f40(int, int, int, int);
int __cdecl fcn_00502cd0(int, int, ...);
int __cdecl he_StartHandlungSearch(int, int, int, int, int);
int __cdecl he_fn_Handlung(void);
unsigned short* __cdecl gm_NextEntityQueryMatch(void);
void __cdecl d3snd_PlayWorkerOrderVoice(void);
int __cdecl cm_SendCopyEntityData(void*);
int __cdecl cm_GetCommandStatus(int);
int __cdecl cm_GetCommandResult(int);
int __cdecl main_RunFrameLoop(int, int);
void __cdecl he_AssignActionSlot(char*, int, int, int);
void __cdecl d3_EndCameraAndUiMode(void);
int __cdecl gm_GetMsgField(int, int);
void __cdecl fcn_0046f940(int, char*);
void __cdecl d2_RenderProduktionStockRows(int, int, int, int, int);
void __cdecl fcn_00595e20(char*, int);
void __cdecl fcn_005963f0(int, int, int, char*);
void __cdecl d2_DestroyForm(int);
void __cdecl d2_RestoreHudAfterDialog(void);
char* __cdecl itoa(int, char*, int);
#include "Develop/DieGildeAddOn/game/entity_record.h"
typedef struct {
	int kind;
	char flag4;
	char pad5[3];
	int f8;
	int f12;
	int f16;
	int f20;
	char pad24[0x10];
	int c28;
	int c2c;
	int c30;
	unsigned short c34;
	char flag36;
	char pad37[0x21];
	unsigned short id;
	char pad5a[0xa];
	int f68;
	int f6c;
	int f70;
	char pad74[0x88];
} Req_59ba40;

/* ADDRESS: GOLDTL 0x0059ba40 */
int __cdecl d2_RunProductionTradeDialog(char* building)
{
	Req_59ba40 req;
	char buf[4];
	int v15;
	int v16;
	int item;
	int count;
	int any;
	int r;
	int h;
	int q;
	int t;
	int found;
	int i;
	int k;
	int m;
	int* p;
	int* acc;
	char* row;

	if (d2_CheckOwnerBlocked((int) building))
		return 0;
	h = fcn_00470820(0, 0, "Handel\\Handel_PRODUKTION");
	d2_CenterDialogWindows(h);
	fcn_0052a0c0(building, 0);
	d2_SetForm(h, 3);
	io_AppendText(0xca);
	fcn_00594340();
	count = 0;
	d2_SetForm(h, 0);
	k = d2_CurrentWindowId;
	m = k * 0x3cc;
	*(int*) (m + 0x10162e8) = 0xe;
	*(int*) (m + 0x10162ec) = 0xe;
	*(int*) (m + 0x10162f0) = 0xe;
	*(int*) (m + 0x10162f4) = 0xe;
	d2_DrawPanelFrame(k, 0x70b, 0x742);
	fcn_00533f40(0x270, 0x15e, d2_CurrentWindowId, fcn_00472830(h, 2, 0x78, &v16, &v15, &item));
	*(unsigned int*) &((D2_CONTROL_TL*) g_1015ea0)[item].font = 0x54;
	do {
		d2_SetForm(h, 2);
		t = fcn_00502cd0(*(unsigned int*) (building + 0x5d), 2, 6, 0, 0xff);
		if (!t)
			return 0;
		q = fcn_00502cd0(*(unsigned int*) (building + 0x5d), 1, 0, 0xfe);
		if (!q)
			return 0;
		r = fcn_00502cd0(*(unsigned int*) (building + 0x5d), 2, 6, 0, 0x2a);
		if (!r)
			return 0;
		if ((g_100f1dc != -1) && (g_100f884 == h)) {
			any = 0;
			p = (int*) 0x7e30e0;
			do {
				if ((int) p >= 0x7e35e0)
					break;
				if (p[-4] == 0xffff)
					break;
				if (*p)
					any = 1;
				p += 10;
			} while (!any);
			if (count > 0) {
				for (k = 0; k < count; k++) {
					if (d2_CurrentElementId == *(int*) (g_779160 + 0x34 + k * 0x58)) {
						if (!any) {
							p = (int*) 0x7e30d0;
							do {
								if (*p == 0xffff)
									break;
								row = *(char**) &((ENTITY_RECORD_VIEW*) 0x7f4ca0)[*p].ptr_17c;
								if (row && (*row == 3) && (*(int*) (row + 0x10) == *(int*) (building + 1)) && (*(unsigned short*) (row + 0xac) == *(unsigned int*) (g_779160 + k * 0x58)))
									*(char*) &((ENTITY_RECORD_VIEW*) 0x7f4ca0)[*p].selected = 1;
								p += 10;
							} while ((int) p < 0x7e35d0);
						} else {
							d3snd_PlayWorkerOrderVoice();
							found = he_StartHandlungSearch(2, 0, 3, 3, *(unsigned int*) (building + 1));
							while (found) {
								if (*(unsigned short*) (found + 0xac) == *(unsigned int*) (g_779160 + k * 0x58))
									goto located;
								found = he_fn_Handlung();
							}
							memset(&req, 0, sizeof(req));
							req.flag4 = 3;
							req.f16 = 0;
							req.f20 = 0;
							req.flag36 = 1;
							req.f8 = *(unsigned int*) &((ENTITY_RECORD*) 0x7f4ca0)[*(unsigned short*) (building + 0x27)].entity_id;
							req.f12 = *(unsigned int*) (building + 1);
							req.c28 = gm_GameTime;
							req.c2c = g_7f4c04;
							req.c30 = g_7f4c08;
							req.c34 = g_7f4c0c;
							req.id = *(unsigned short*) (g_779160 + k * 0x58);
							req.f68 = req.f12;
							req.f70 = *(unsigned int*) (r + 2);
							req.f6c = *(unsigned int*) (q + 2);
							m = cm_SendCopyEntityData(&req);
							while (!cm_GetCommandStatus(m))
								main_RunFrameLoop(0, 0x20007);
							found = cm_GetCommandResult(m);
located:
							p = (int*) 0x7e30d0;
							do {
								if (*p == 0xffff)
									break;
								if (p[4]) {
									he_AssignActionSlot(building, g_7746cc, *p, found);
									*(char*) &((ENTITY_RECORD_VIEW*) 0x7f4ca0)[*p].selected = 0;
								}
								p += 10;
							} while ((int) p < 0x7e35d0);
							if (!*(int*) (found + 0x70))
								*(int*) (found + 0x70) = 1;
						}
					}
				}
			}
		}
		if (g_14ce8e0) {
			any = 0;
			p = (int*) 0x7e30e0;
			do {
				if ((int) p >= 0x7e35e0)
					break;
				if (p[-4] == 0xffff)
					break;
				if (*p)
					any = 1;
				p += 10;
			} while (!any);
			if (any) {
				p = (int*) 0x7e30d0;
				do {
					if (*p == 0xffff)
						break;
					*(char*) &((ENTITY_RECORD_VIEW*) 0x7f4ca0)[*p].selected = 0;
					p += 10;
				} while ((int) p < 0x7e35d0);
			} else {
				g_774654 = 1;
				d3_EndCameraAndUiMode();
			}
		}
		m = fcn_00502cd0(*(unsigned int*) (t + 0x14), 1, 4, 0x17);
		if (m) {
			acc = (int*) (0x779160 + count * 0x58);
			do {
				if (*(int*) (m + 0xe) > 1) {
					found = 1;
					for (i = 0; (i < count) && found; i++) {
						if (*(unsigned int*) (0x779160 + i * 0x58) == *(unsigned short*) m)
							found = 0;
					}
					if (found) {
						if ((int) acc < 0x7796e0) {
							count++;
							*acc = *(unsigned short*) m;
							acc += 0x16;
						}
					}
				}
				m = (int) gm_NextEntityQueryMatch();
			} while (m);
		}
		if (count > 0) {
			acc = (int*) 0x779160;
			for (i = count; i > 0; i--) {
				m = fcn_00502cd0(*(unsigned int*) (r + 0x14), 1, 0, *acc);
				if (m)
					acc[0x14] = *(int*) (m + 0xe);
				else
					acc[0x14] = 0;
				m = fcn_00502cd0(*(unsigned int*) (q + 0x14), 1, 0, *acc);
				if (m)
					acc[0x15] = gm_GetMsgField(q, m);
				else
					acc[0x15] = 0;
				acc[1] = 0;
				acc[2] = 0;
				acc[3] = 0;
				acc[4] = 0;
				acc += 0x16;
			}
		}
		itoa(count, buf, 10);
		fcn_0046f940(item, buf);
		d2_RenderProduktionStockRows(h, 2, count, r, 1);
		fcn_00595e20(building, r);
		fcn_005963f0(h, 1, 0, building);
	} while (main_RunFrameLoop((int) d2_RunProductionTradeDialog, 0x677c7));
	d2_DestroyForm(h);
	d2_RestoreHudAfterDialog();
	return 0;
}
