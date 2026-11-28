typedef struct {
	unsigned char kind;
	unsigned char remaining[0x24c];
} BuildingProto599350;
#include "Develop/DieGildeAddOn/game/building_prototype.h"
typedef struct {
	char pad0[4];
	unsigned char type;
	char pad5[3];
	int f08;
	int f0c;
	char pad10[0x18];
	int f28;
	int f2c;
	int f30;
	unsigned short f34;
	unsigned char f36;
	char pad37[0x21];
	int f58;
	int f5c;
	int f60;
	char pad64[0x1c];
	float pos[3];
	char pad8c[4];
	float rot[3];
	char name[0x3f];
	char pad_db[0x1d];
} Msg_599350;                        /* SIZE 0xf8 */

#include "Develop/Units/d2.v1/d2_gui.h"
extern unsigned char* lpGebaeudePROT;
#include "Develop/DieGildeAddOn/game/game_player.h"
extern int d2_CurrentWindowId;
extern int d2_DialogButtonAction;
extern int g_6aa0a8;
extern int d2_CurrentElementId;
#include "Develop/Units/d2.v1/client_dialog_state.h"
extern int io_RightButtonReleased;
extern int g_7746f8;
extern unsigned char gm_ActiveTownIndex;
extern char* gm_CityEntity;
extern int gm_GameTime;
extern int gm_GameTimeHour;
extern int gm_GameTimeSliceDword;
extern short gm_GameTimeTailWord;
extern char gm_EntitySlotTable[];
extern char* g_14a7898[];
extern char str_empty[];

int __cdecl d2_TutorialAllowsFlag(int);
void __cdecl d2_DispatchTutorialInput(int, int, int, int);
int __cdecl d2_LoadForm(int, int, char*);
void __cdecl d2_CenterDialogWindows(int);
int __cdecl d2_SetForm(int, int);
int __cdecl d2_GetFormWindow(int, int);
void __cdecl d2_CreateWindowScrollbar(int, int, int, int, int, int*, int*, int*);
void __cdecl io_AppendText(int, ...);
int __cdecl d2_AddElementToWindow(int, int, int, int);
int __cdecl gm_GetBuildingTypeCategory(int);
unsigned int __cdecl gm_CanBuildBuildingType(int, int);
int __cdecl d2_ShowTxt(int, int, char*, int);
int __cdecl gm_CalcBuildingCost(unsigned char*, int);
void __cdecl d2_FormatCurrencyString(int, unsigned char, char*);
int __cdecl d2_SetElementFont(int, int);
void __cdecl d2_SetLabelText(int, const char*);
int __cdecl d2_ClearWindowChildren(int, int);
char* __cdecl gm_FindPublicTreasury(int);
int __cdecl d2_CheckFundsAndNotify(int, int, int, int);
int __cdecl gm_CheckEntityStock(void*, int, int);
void __cdecl d2_SetFormVisibility(int, int);
int __cdecl lc_GebaeudeAusrichten(int, char*);
void __cdecl d3_TransformPoint(char*, float*, float*);
void __cdecl d3_ComputeObjectYawToTarget(float*, int);
char* __cdecl strncpy(char*, const char*, unsigned int);
char* __cdecl strcpy(char*, const char*);
int __cdecl cm_SendCopyEntityData(char*);
int __cdecl main_RunFrameLoop(void*, int);
void __cdecl d2_DestroyForm(int);

/* ADDRESS: GOLDTL 0x00599350 */
/* ADDRESS: GOLDDE 0x0057eb00 */
void __cdecl d2_ShowBuildingMenu(void)
{
	char path[0x104];
	char buf[0x80];
	Msg_599350 msg;
	int ids[10];
	int flag;
	int count;
	int i;
	int ida;
	int idb;
	int idc;
	int hwnd;
	int prevIdx;
	int off;
	BUILDING_PROTOTYPE* p;
	char* mode;
	int prev;
	int id;
	int idx;
	int txt;
	char* obj;
	unsigned char v;
	unsigned int avail;

	prevIdx = -1;
	prev = -1;
	mode = 0;
	if (!d2_TutorialAllowsFlag(0x40)) {
		return;
	}
	d2_DispatchTutorialInput(0xe, 0, 0, 0);
	hwnd = d2_LoadForm(0, 0, (char*) 0x6aa298);
	d2_CenterDialogWindows(hwnd);
	d2_SetForm(hwnd, 0);
	i = d2_CurrentWindowId * 0x3cc;
	*(int*) (i + 0x10162e8) = 0x18;
	*(int*) (i + 0x10162ec) = 0x18;
	*(int*) (i + 0x10162f0) = 0x18;
	*(int*) (i + 0x10162f4) = 0x18;
	d2_CreateWindowScrollbar(0x20c, 0x168, d2_CurrentWindowId, d2_GetFormWindow(hwnd, 3), 0x5a, &ida, &idc, &idb);
	d2_SetForm(hwnd, 1);
	io_AppendText(0x17eb);
	d2_SetForm(hwnd, 2);
	count = 0;
	flag = 0;
	for (i = 1; i < 10; i++) {
		if (i == 2 || i == 5) {
			continue;
		}
		if (i == 3) {
			v = *(unsigned char*) (gm_LocalPlayerSlot * 0x21c + 0x7f4e06);
			if (v != 0x0f && v != 0x0a) {
				flag = 1;
			}
		} else {
			if (i == 7) {
				v = *(unsigned char*) (gm_LocalPlayerSlot * 0x21c + 0x7f4e04);
				if (v < 0x34 || v > 0x39) {
					flag = 1;
				}
			}
		}
		id = d2_AddElementToWindow((count % 2) * 0x46 + 0x30, (count / 2) * 0x5a + 0x0f, i + 0x6d4, d2_CurrentWindowId);
		ids[i] = id;
		if (flag == 0) {
			*(int*) (((char*)&((D2_CONTROL_TL*)d2_Controls)[id].value_05c)) = 1;
			strcpy((char*) (((char*)&((D2_CONTROL_TL*)d2_Controls)[id] + 0x0cc)), g_14a7898[i]);
			*(int*) (((char*)&((D2_CONTROL_TL*)d2_Controls)[id].flags_1d0)) = 3;
			*(int*) (((char*)&((D2_CONTROL_TL*)d2_Controls)[id].value_1cc)) = 0x54;
			*(int*) (((char*)&((D2_CONTROL_TL*)d2_Controls)[id].value_1e0)) = -1;
		} else {
			*(int*) (((char*)&((D2_CONTROL_TL*)d2_Controls)[id].disabled)) = 1;
			*(int*) (((char*)&((D2_CONTROL_TL*)d2_Controls)[id].value_060)) = 1;
		}
		count++;
		flag = 0;
	}
	*(int*) (((char*)&((D2_CONTROL_TL*)d2_Controls)[ids[g_6aa0a8]].value_038)) = 1;
	do {
		if (d2_DialogButtonAction >= 0x6d4 && d2_DialogButtonAction < 0x6de) {
			g_6aa0a8 = d2_DialogButtonAction - 0x6d4;
			*(int*) (((char*)&((D2_CONTROL_TL*)d2_Controls)[ids[g_6aa0a8]].value_038)) = 1;
			if (prev != -1) {
				*(int*) (((char*)&((D2_CONTROL_TL*)d2_Controls)[ids[prev]].value_038)) = 0;
			}
		}
		if (g_6aa0a8 != prev) {
			char* rec;

			d2_SetForm(hwnd, 3);
			d2_ClearWindowChildren(d2_CurrentWindowId, 1);
			mode = 0;
			if (g_6aa0a8 == 3) {
				g_7746f8 = 1;
				mode = gm_FindPublicTreasury(1);
			} else {
				g_7746f8 = 0;
			}
			count = 0;
			off = 0;
			idx = 0;
			rec = (char*) 0x14a6558;
			do {
				if (gm_GetBuildingTypeCategory(idx) == g_6aa0a8) {
					p = &((BUILDING_PROTOTYPE*) lpGebaeudePROT)[idx];
					avail = gm_CanBuildBuildingType(idx, gm_LocalPlayerSlot);
					if (avail == 1) {
						if (p->category != 0x0f && p->category != 6) {
							id = d2_AddElementToWindow((count % 3) * 0x46 + 0x30, (count / 3) * 0x5a + 0x0f, idx + 0x427, d2_CurrentWindowId);
							*(int*) (((char*)&((D2_CONTROL_TL*)d2_Controls)[id].value_058)) = 1;
							strcpy((char*) (((char*)&((D2_CONTROL_TL*)d2_Controls)[id] + 0x0cc)), *(char**) rec);
							*(int*) (((char*)&((D2_CONTROL_TL*)d2_Controls)[id].flags_1d0)) = 3;
							*(int*) (((char*)&((D2_CONTROL_TL*)d2_Controls)[id].value_1cc)) = 0x54;
							txt = gm_CalcBuildingCost((unsigned char*) (gm_EntitySlotTable + gm_LocalPlayerSlot * 0x21c), idx);
							d2_FormatCurrencyString(txt, gm_ActiveTownIndex, buf);
							txt = d2_ShowTxt((count % 3) * 0x46 + 2, (count / 3) * 0x5a + 0x3f, str_empty, d2_CurrentWindowId);
							d2_SetElementFont(txt, 0x54);
							d2_SetLabelText(txt, buf);
							*(int*) (((char*)&((D2_CONTROL_TL*)d2_Controls)[txt].width)) = 0x8c;
							*(int*) (((char*)&((D2_CONTROL_TL*)d2_Controls)[txt].value_06c)) = 1;
							count++;
						}
					} else {
						if (avail == 2) {
							id = d2_AddElementToWindow((count % 3) * 0x46 + 0x30, (count / 3) * 0x5a + 0x0f, 0x4fb, d2_CurrentWindowId);
							*(char*) (((char*)&((D2_CONTROL_TL*)d2_Controls)[id] + 0x0cc)) = str_empty[0];
							*(int*) (((char*)&((D2_CONTROL_TL*)d2_Controls)[id].flags_1d0)) = 3;
							*(int*) (((char*)&((D2_CONTROL_TL*)d2_Controls)[id].value_1cc)) = 0x54;
							count++;
						}
					}
				}
				rec += 0x38;
				off += 0x24d;
				idx++;
			} while ((int) rec < (int) 0x14a7898);
			prev = g_6aa0a8;
		}
		if (d2_DialogButtonAction >= 0x427 && d2_DialogButtonAction <= 0x47f) {
			i = d2_DialogButtonAction - 0x427;
			if (prevIdx != -1) {
				*(int*) (((char*)&((D2_CONTROL_TL*)d2_Controls)[prevIdx].value_038)) = 0;
				*(int*) (((char*)&((D2_CONTROL_TL*)d2_Controls)[prevIdx].value_03c)) = 0;
			}
			prevIdx = d2_CurrentElementId;
			if (mode != 0) {
				txt = gm_CalcBuildingCost((unsigned char*) (gm_EntitySlotTable + gm_LocalPlayerSlot * 0x21c), i);
				if (!d2_CheckFundsAndNotify((int) mode, *(int*) (mode + 0x14), txt, gm_ActiveTownIndex)) {
					goto skip_place;
				}
			} else {
				txt = gm_CalcBuildingCost((unsigned char*) (gm_EntitySlotTable + gm_LocalPlayerSlot * 0x21c), i);
				if (!gm_CheckEntityStock(gm_EntitySlotTable + gm_LocalPlayerSlot * 0x21c, txt, gm_ActiveTownIndex)) {
					goto skip_place;
				}
			}
			d2_SetFormVisibility(hwnd, 0);
			obj = (char*) lc_GebaeudeAusrichten(i, path);
			if (obj != 0) {
				msg.f28 = gm_GameTime;
				msg.type = 0x0d;
				msg.f2c = gm_GameTimeHour;
				msg.f36 = 2;
				msg.f30 = gm_GameTimeSliceDword;
				msg.f34 = (unsigned short) gm_GameTimeTailWord;
				id = *(int*) (gm_EntitySlotTable + gm_LocalPlayerSlot * 0x21c + 4);
				msg.f08 = id;
				msg.f0c = id;
				if (g_6aa0a8 == 3) {
					msg.f58 = *(int*) (gm_CityEntity + 4);
				} else {
					msg.f58 = id;
				}
				msg.f5c = i;
				msg.f60 = gm_CalcBuildingCost((unsigned char*) (gm_EntitySlotTable + gm_LocalPlayerSlot * 0x21c), i);
				d3_TransformPoint(obj, (float*) (obj + 0x4c), msg.pos);
				d3_ComputeObjectYawToTarget(msg.rot, (int) obj);
				strncpy(msg.name, path, 0x3f);
				cm_SendCopyEntityData((char*) &msg);
				d2_DialogCloseRequested = 1;
			} else {
				d2_SetFormVisibility(hwnd, 1);
			}
		}
skip_place:
		if (io_RightButtonReleased != 0) {
			d2_DialogCloseRequested = 1;
		}
	} while (main_RunFrameLoop(d2_ShowBuildingMenu, 0x657c7) != 0);
	if (hwnd != -1) {
		d2_DestroyForm(hwnd);
	}
	g_7746f8 = 0;
	d2_DispatchTutorialInput(0xe, 0, 1, 0);
}
