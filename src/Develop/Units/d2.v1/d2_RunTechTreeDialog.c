#include "Develop/DieGildeAddOn/game/object_prototype.h"
#include "Develop/DieGildeAddOn/game/entity_record.h"
#include <string.h>
#include "Develop/client_types.h"
/* SIZE 0x21c */
typedef struct {
	unsigned short f0;
	int f2;
	int f4;
	char pad8[0x18c];
	int f194;
} House;
extern char* lpObjektePROT;
extern char* g_7746c4;
extern int g_7746c8;
extern int g_7746f8;
#include "Develop/Units/d2.v1/client_dialog_state.h"
extern int g_7747b4;
extern int g_85ab60;
extern int g_14ce8e0;
extern int g_100f1dc;
extern int d2_CurrentElementId;
extern char* gm_CityEntity;
extern unsigned char g_773d75;
#include "Develop/DieGildeAddOn/game/game_player.h"
extern char g_7f4ca0[];
extern char g_7f3f24[];
extern char* g_14a5398;
extern char s_6aa330[];
extern char s_6aa328[];
extern char s_68b7ac[];
extern pos14_7f4c00 gm_GameTime;

int __cdecl d2_TutorialAllowsFlag(int);
void __cdecl d2_DispatchTutorialInput(int, int, int, int);
void* __cdecl fcn_00502cd0(int, int, ...);
int __cdecl d2_OpenDependencyDiagram(char*, char*, void*);
int __cdecl d2_ShowModalMessageBox(char*, int);
void __cdecl d2_CenterDialogWindows(int);
void __cdecl d2_SetForm(int, int);
int __cdecl d2_GetWindowListItem(int, int, int);
int __cdecl io_AppendText(int);
void __cdecl gm_CollectGebaeudeUpgrades(char*);
int __cdecl main_RunFrameLoop(void*, int);
void __cdecl d2_ShowTechTreeEffects(char*);
int __cdecl d2_DispatchTutorialEvent(int, int, int, int);
void __cdecl d2_CloseDependencyDiagram(void);
void __cdecl d2_UpdateDependencyDiagram(char*, char*);
float __cdecl eval_ObjektPreis2Credits(int, int);
int __cdecl gm_CheckEntityStock(char*, int, char);
int __cdecl d2_CheckFundsAndNotify(char*, int, int, char);
void __cdecl io_FormatTextBuffer(char*, int, ...);
void __cdecl d2_EnterBuildingObjekt(char*, int, char*);
char* __cdecl gm_FindBuildingTreasury(char*);
void __cdecl cm_SendLogAction(char*);
void __cdecl cm_SendTraceEnd(char*);
void __cdecl cm_RequestMoveCredits(int, int, char, int);
void __cdecl cm_RequestTransferCurrencyNoKill(int, int, char, int);
void __cdecl cm_RequestModifyHealth(int, int);
int __cdecl cm_SendCopyEntityData(void*);
int __cdecl cm_GetCommandStatus(int);
char* __cdecl gm_GetEntityTableEntry(char*);
int __cdecl fcn_0064d41a(char*, char*, ...);

/* ADDRESS: GOLDTL 0x0059aa10 */
void __cdecl d2_RunTechTreeDialog(char* a0, int a1)
{
	char msg[0xf8];
	char buf[0x100];
	char name[0x80];
	char text[0x80];
	char* house;
	void* q;
	int h;
	char* node;
	int i;
	int sel;
	int ok;
	int item;
	float f;
	int n;
	int amount;
	int req;
	char* p;
	int s;

	if (a0 == g_7746c4) {
		if (!d2_TutorialAllowsFlag(0x200))
			return;
		d2_DispatchTutorialInput(0x11, (int) a0, 0, a1);
	}
	house = (char *)&((ENTITY_RECORD*)g_7f4ca0)[(unsigned int) g_774970];
	q = fcn_00502cd0(*(int*) (a0 + 0x5d), 1, 0, a1);
	if (!q) {
		q = fcn_00502cd0(*(int*) (a0 + 0x5d), 1, 4, 2);
		if (!q)
			return;
	}
	h = d2_OpenDependencyDiagram(s_6aa330, a0, q);
	if (h < 0) {
		d2_ShowModalMessageBox(g_14a5398, 0);
		return;
	}
	d2_CenterDialogWindows(h);
	d2_SetForm(h, 4);
	h = d2_GetWindowListItem(h, 4, io_AppendText(0x17e2));
	gm_CollectGebaeudeUpgrades(a0);
	while (main_RunFrameLoop((void*) d2_RunTechTreeDialog, 0x657c7)) {
		if (g_14ce8e0)
			g_774654 = 1;
		if (g_100f1dc != -1 && d2_CurrentElementId == h)
			d2_ShowTechTreeEffects(a0);
		if (g_100f1dc >= 0xdf && g_100f1dc <= 0x3bb) {
			for (i = 0; i < g_85ab60; i++) {
				p = &g_7f3f24[i * 0x34];
				if (*(int*) p != -1 && d2_CurrentElementId == *(int*) p)
					break;
			}
			if (i < g_85ab60) {
				sel = g_100f1dc - 0xdf;
				memset(msg, 0, sizeof msg);
				if (!d2_DispatchTutorialEvent(0x2b, (int) a0, 0, sel)) continue; {
					node = (char *)&((OBJECT_PROTOTYPE*)lpObjektePROT)[sel];
					if (q)
						item = (int) fcn_00502cd0(*(int*) ((char*) q + 0x14), 1, 0, sel);
					else
						item = (int) fcn_00502cd0(*(int*) (a0 + 0x5d), 2, 6, 0, sel);
					if (!item) {
						*(unsigned char*) (msg + 0x36) = 1;
						if (*(unsigned char*) ((char *)&((OBJECT_PROTOTYPE*)lpObjektePROT)[sel]) == 6) {
							*(unsigned char*) (msg + 4) = 0x0c;
							*(int*) (msg + 0x0c) = *(int*) (a0 + 1);
							*(int*) (msg + 0x58) = *(int*) (a0 + 1);
							*(int*) (msg + 0x60) = sel;
							*(pos14_7f4c00*) (msg + 0x28) = gm_GameTime;
							*(int*) (msg + 8) = *(int*) ((char *)&((ENTITY_RECORD*)g_7f4ca0)[(unsigned int) *(unsigned short*) (a0 + 0x25)] + 4);
							*(int*) (msg + 0x5c) = *(int*) (msg + 8);
						} else {
							*(int*) (msg + 0x0c) = *(int*) (a0 + 1);
							*(unsigned char*) (msg + 4) = 2;
							*(int*) (msg + 8) = *(int*) ((char *)&((ENTITY_RECORD*)g_7f4ca0)[(unsigned int) *(unsigned short*) (a0 + 0x25)] + 4);
							*(pos14_7f4c00*) (msg + 0x28) = gm_GameTime;
							*(short*) (msg + 0x58) = (short) sel;
							*(int*) (msg + 0x5c) = *(int*) ((char*) q + 2);
						}
						req = *(unsigned char*) (node + 0x40);
						if (req == 0) {
							ok = 0;
							f = (float) (g_7747b4 * 0.25 + 0.5);
							n = (int) eval_ObjektPreis2Credits(sel, 100);
							amount = (int) (n * f);
							if (*(unsigned short*) (a0 + 0x27) != *(unsigned short*) gm_CityEntity) {
								if (gm_CheckEntityStock((char *)&((ENTITY_RECORD*)g_7f4ca0)[(unsigned int) g_774970], amount, (char) g_773d75))
									ok = 1;
								io_FormatTextBuffer(buf, 0x1a, amount, a0, sel * 2 + 0x9a8);
							} else {
								p = gm_FindBuildingTreasury(a0);
								if (d2_CheckFundsAndNotify(p, *(int*) (p + 0x14), amount, (char) g_773d75))
									ok = 1;
								io_FormatTextBuffer(buf, 0x1c, amount, a0, sel * 2 + 0x9a8);
							}


							if (ok && d2_ShowModalMessageBox(buf, 1)) {
								d2_DispatchTutorialInput(0x2b, (int) a0, 0, sel);
								cm_SendLogAction(s_6aa328);
								if (*(unsigned short*) (a0 + 0x27) != *(unsigned short*) gm_CityEntity) {
									cm_RequestMoveCredits(-1, *(int*) ((char *)&((ENTITY_RECORD*)g_7f4ca0)[(unsigned int) *(unsigned short*) (a0 + 0x27)] + 4), (char) g_773d75, amount);
									p = gm_GetEntityTableEntry((char *)&((ENTITY_RECORD*)g_7f4ca0)[(unsigned int) g_774970]);
									if (p)
										*(int*) (p + 0x40) += amount;
								} else {
									p = gm_FindBuildingTreasury(a0);
									if (p)
										cm_RequestTransferCurrencyNoKill(-1, *(int*) (p + 2), (char) g_773d75, amount);
								}
								s = cm_SendCopyEntityData(msg);
								cm_SendTraceEnd(s_6aa328);
								goto wait;
							}
						} else {
							io_FormatTextBuffer(buf, 0x1b, req, a0, sel * 2 + 0x9a8);
							if (d2_ShowModalMessageBox(buf, 1)) {
								if (req > *(int*) (house + 0x194)) {
									io_FormatTextBuffer(buf, 0x74, req);
									d2_ShowModalMessageBox(buf, 0);
								} else {
									cm_SendLogAction(s_6aa328);
									cm_RequestModifyHealth(*(int*) (house + 4), -req);
									s = cm_SendCopyEntityData(msg);
									cm_SendTraceEnd(s_6aa328);
									goto wait;
								}
							}
						}
					} else {
						if (q && (((*(unsigned short*) q == 0) == 0xfd) || g_7746c8)) {
							p = node + 1;
							{
								char* d = name;
								while ((*d++ = *p++) != 0)
									;
							}
							_strupr(name);
							fcn_0064d41a(text, s_68b7ac, name);
							d2_EnterBuildingObjekt(a0, *(int*) ((char*) q + 2), text);
						}
					}
				}
			}
		}
		goto tail;
wait:
		if (s != -1) {
wait_loop:
			if (cm_GetCommandStatus(s) == 0) {
				main_RunFrameLoop(0, 0x657c7);
				goto wait_loop;
			}
		}
tail:
		d2_UpdateDependencyDiagram(a0, q);
	}
	d2_CloseDependencyDiagram();
	g_7746f8 = 0;
	if (a0 == g_7746c4)
		d2_DispatchTutorialInput(0x11, (int) a0, 1, a1);
}
