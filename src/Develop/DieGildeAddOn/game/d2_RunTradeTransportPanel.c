#include <string.h>
#include "Develop/Units/d2.v1/d2_gui.h"
extern char* sv_SelectedBuilding;
extern char* g_entity_type_table;
#include "Develop/DieGildeAddOn/game/game_data.h"
extern int d2_InventoryPanelWindowId;
extern unsigned char gm_ActiveTownIndex;
extern int d2_DialogCloseRequested;
extern unsigned short gm_LocalPlayerSlot;
extern int gm_GameTimeHour;
extern int gm_GameTimeSliceDword;
extern short gm_GameTimeTailWord;
extern unsigned char gm_ClientModeFlags;
extern char str_empty[];
extern char gm_EntityIdField[];
extern GuiWin g_00f8f120[];
extern GuiObj g_00fb1020[];
extern char gm_TownTable[];
extern int d2_SelectedEntityUiFlags;
extern char* g_99ec10;
extern char* d2_SelectedBuilding;
extern int g_776c60[];
extern int g_774698;
extern int d2_ObjektNameTable[];

unsigned short* __cdecl gm_QueryEntities(int, int, ...);
int __cdecl d2_LoadForm(int, int, char*);
int __cdecl d2_CreateWindowTextButton(int, int, int);
void __cdecl d2_CenterDialogWindows(int);
void __cdecl d2_DispatchTutorialInput(int, char*, int, int);
int __cdecl d2_SetForm(int, int);
int __cdecl d2_CreateButtonRow(int, int, int*, int, ...);
int __cdecl d2_SetSlotVisibility(int, int);
float __cdecl gm_CalcLevelProductionBonus(int);
unsigned short* __cdecl gm_StartFilteredEntitySearch(int, ...);
int __cdecl d2_GetFormWindow(int, int, int, int*, int*, int*);
void __cdecl d2_DrawPanelFrame(int, int, int);
void __cdecl d2_CreateWindowScrollbar(int, int, int, int);
void __cdecl io_AppendText(int, ...);
void __cdecl d2_ResetBuildingUiSlots(void);
void __cdecl d2_SetOverlayAnimation(int, int);
int __cdecl d2_AddElementToWindow(int, int, int, int);
void __cdecl d2_OpenEntityQuickSlots(int, int, int, int, int);
void __cdecl d2_ResetUiInputAndBounds(void);
int __cdecl gm_IsGebaeudeOpen(int, int, int);
int __cdecl gm_HasActiveSpecialObject(char*, int);
int __cdecl d2_BuildProduktionSlotGrid(int, int);
int __cdecl d2_LayoutProduktionSlotGrid(int, int, int, int);
int __cdecl d2_SyncWareProduktionSlotGrid(int, int);
int __cdecl d2_RefreshWorkshopInventoryGrids(int, int, int, int);
int __cdecl d2_SyncProduktionSlotGrid(int, int);
int __cdecl d2_DrawProduktionSlotGrid(int, int, int, int, int);
int __cdecl gm_IsWarehouse(int);
int __cdecl gm_CanTradeWithObject(int, int);
void __cdecl d2_DestroyGuiElement(int);
void __cdecl d2_RemoveElement(int);
void __cdecl d2_CloseWindow(int);
int __cdecl he_StartHandlungSearch(int, int, int, int, int, ...);
int __cdecl d2_AddWindowValueGauge(int, ...);
int __cdecl d2_CreateChildWindow(int, int, int, int, int, int);
int __cdecl d2_SetElementFont(int, int);
int __cdecl fcn_005462a0(void);
int __cdecl fcn_00502850(void);
int __cdecl d2_CreateGuiWindow(int, ...);
int __cdecl fcn_00466330(int, int);
int __cdecl gm_CalcEscortCost(int, int);
void __cdecl fcn_0051af00(int, int, ...);
int __cdecl cm_BeginPacketFieldDelta(char*, int);
int __cdecl cm_AppendCommandSyncField(int, int, int, void*);
void __cdecl cm_SendSetAttribute(void);
void __cdecl d2_ShowStatusBanner(int);
int __cdecl d2_SetControlText(int, int);
int __cdecl d2_SetFormVisibility(int, int);
void __cdecl d2_RunTradeRouteEditor(int);
int __cdecl d2_GetControlValue(int);
int __cdecl gm_GetStorageSlotCapacity(int, int);
int __cdecl d2_AddWindowField(int, int, int, int, int);
int __cdecl fcn_0064d41a(int, int, int, int, int);
int __cdecl d2_UpdateActiveItemSlots(void);
void __cdecl ResetDisplayCounters(void);
int __cdecl d2_AddDisplayCounter(int, int);
int __cdecl CountDisplayCounters(void);
void __cdecl d2_ClearSelectedControl(void);
int __cdecl d2_CanCloseWindowDuringTutorial(void);
void __cdecl d3_EndCameraAndUiMode(void);
float __cdecl gm_GetSeasonPrice(int, int);
float __cdecl gm_RandomFloat01(void);
int __cdecl ob_TransportFromLager(int, int, int, int, int, float, int, int);
void __cdecl io_ClearInputState(void);
int __cdecl d2_ShowModalMessageBox(int, int);
int __cdecl gm_CheckInventoryCapacity(char*, int, int);
int __cdecl gm_AddTime(int, int, int, int);
int __cdecl gm_PackGameTime(int, int);
int __cdecl cm_RequestMoveCredits(int, int, char, int);
int __cdecl cm_SendSellObjekt(int, int, int, int, int, int);
int __cdecl cm_RequestChrWalkToDummy(int, int, int, int);
int __cdecl cm_SendCopyEntityData(int);
float __cdecl eval_ObjektPreis2Credits(int, int);
int __cdecl sb_PlayVoice(int, int, int, int, int, int, int);
int __cdecl gm_CheckEntityStock(int, int, int);
int __cdecl d2_DestroyForm(int);
void __cdecl d2_CloseInventoryPanel(void);
int __cdecl d2_SellObjectsDialog(int, int);
int __cdecl cm_DispatchCartTransfer(int, int, int, int);
void __cdecl cm_CompleteAction0x0f(int);
int __cdecl d2_ShowNewCartDialog(int);
void __cdecl d2_CalcTradeCartCost(int, float, int);
int __cdecl gm_eval_SlotVoll(int, int, int);
int __cdecl d2_DispatchTutorialEvent(int, int, int, int);
int __cdecl gm_ConvertUnitsToAmount(int, int);
int __cdecl cm_RequestClearLagerslot(int, int);
int __cdecl d2_RunCityScrollMapDialog(int, int, int, int, int);
int __cdecl gm_CheckEntityType(int);
int __cdecl d3snd_PlayWorkerOrderVoice(void);
int __cdecl fcn_005ba0e0(int, int, int, int, int, float, int, int);
void __cdecl gm_CalcEntityInventoryStats(int, int*);
int __cdecl main_RunFrameLoop(void*, int);

/* One 0xf0-byte inventory entity slot. Only the eight bytes at +0x0c..+0x18
   and the two three-int arrays at +0xd8 are written by the native body so far;
   everything between them is still an unnamed region. */
typedef struct {
	int f00;
	int f04;
	int f08;
	int f0c;
	int f10;
	int f14;
	int f18;
	int f1c;
	char pad20[0xb8];
	int fD8[3];
	int fE4[3];
} Ent5af320;

/*
 * Trade/transport inventory panel controller, frameless __chkstk frame
 * 0x1848 with saved ebx, ebp, esi, edi; arg1 at 0x184c, arg2 at 0x1850.
 * Native extents (offsets from the frame base, i.e. the value added to esp):
 * scalars 0x00..0x158, struct 0xb4 at 0x15c, 16 entity slots of 0xf0 at
 * 0x6d8, two 0x100 objects at 0x15d8/0x16d8, int[28] at 0x17d8.
 * The frame struct below holds those extents while the 0x5af320 body
 * (3413 instructions) is reconstructed; native locals stay separate and the
 * register assignment (ebp as the zero register, esi for arg1) only
 * converges once the whole body exists.
 */
typedef struct {
	int v10;
	int v1c;
	int v14;
	int v18;
	int v20;
	int v24;
	int v28;
	int v2c;
	int v30;
	int v34;
	int v38;
	int v3c;
	int v40;
	int v44;
	int v48;
	int v4c;
	float v50;
	int v54;
	int v58;
	int v5c;
	int v60;
	float v64;
	int v68;
	int v6c;
	int v70;
	int v74;
	int v78;
	int v7c;
	int v80;
	float v84;
	int v88;
	float v8c;
	int v90;
	int v94;
	int v98;
	int v9c;
	int vA0;
	int vA4;
	int vA8;
	int vAC;
	int vB0;
	int vB4;
	int vB8;
	int vBC;
	int vC0;
	int vC4;
	int vC8;
	int vCC;
	int vD0;
	int vD4[7];
	int vF0[7];
	int v10C[9];
	int v130;
	int v134;
	int v138;
	int v13C;
	int v140;
	int v144;
	int v148;
	int v14C;
	int v150;
	int v154;
	int v158;
	char v15C[0xb4];
	char v210[0x4c8];
	Ent5af320 v6D8[16];
	char v15D8[0x100];
	char v16D8[0x100];
	char v17D8[0x80];
} frame_t;

/* ADDRESS: GOLD 0x005af320 */
int __cdecl d2_RunTradeTransportPanel(int entity, int flags)
{
	frame_t f;
	int idx;
	int i;
	int j;
	int h;
	int slot_value;
	Ent5af320* e;

	f.v158 = 0;
	memset(f.v15C, 0, 0xb4);
	f.v18 = 0;
	f.v44 = 0;
	f.v94 = 0;
	f.v7c = entity;
	f.v88 = 0;
	f.v10C[0] = 0x51;
	f.v10C[1] = 0;
	f.v10C[2] = 0;
	f.v10C[3] = 0x30;
	f.v10C[4] = 0x71;
	f.v10C[5] = 0;
	f.v10C[6] = 0x11;
	f.v10C[7] = 0x52;
	f.v10C[8] = 0x93;
	f.v38 = 0;
	f.v68 = 0;
	f.v40 = 0;
	f.v3c = 0;
	f.v4c = 0;
	f.v60 = 0;
	f.v50 = 1.0f;
	f.v90 = -1;
	f.vD4[0] = -1;
	f.vD4[1] = -1;
	f.vD4[2] = -1;
	f.vD4[3] = -1;
	f.vD4[4] = -1;
	f.vD4[5] = -1;
	f.vD4[6] = -1;
	f.vF0[0] = 0x95;
	f.vF0[1] = 0x92;
	f.vF0[2] = 0x93;
	f.vF0[3] = 0x94;
	f.vF0[4] = 0x97;
	f.vF0[5] = 0x96;
	f.vF0[6] = 0x2db;
	f.vA4 = -1;
	f.v14 = entity;
	f.v80 = flags & 8;

	if (f.v80 != 0) {
		int* tp;

		f.vA4 = d2_LoadForm((short) (g_00fb9072 - 0x68), 0x106, "panel\\infopanel_marktstand");
		tp = (int*) 0x143a588;
		for (i = 0; i < 7; i++) {
			int d;

			d = f.vD4[i] = d2_CreateWindowTextButton(0, 0xc + i * 0x18, *tp);
			tp = tp + 1;
			if (*(unsigned short*) (int) sv_SelectedBuilding == f.vF0[i]) {
				int k;
				k = d * 0x2ec;
				*(int*) ((int) g_00f8f080 + k + 0x28) = 1;
				*(int*) ((int) g_00f8f080 + k + 0x2c) = 1;
			}
		}
		f.v14 = *(int*) 0x6f1bc8;
	}

	/* 0x5bab17: table-row pointer for the first selected entity */
	*(char*) 0x6f2f64 = 0;
	idx = *(unsigned char*) entity;
	f.v74 = (int) g_entity_type_table + idx + idx * 0x24c;

	if ((int) sv_SelectedBuilding != 0) {
		f.v70 = flags & 1;
		if (f.v70 != 0) {
			/* 0x5bab5a: refresh slot 0xff, then the 0x2a and 0x116 rows */
			f.v44 = (int) gm_QueryEntities(*(int*) ((int) sv_SelectedBuilding + 0x14), 2, 0, 0xff, 6);
			f.v18 = (int) gm_QueryEntities(*(int*) ((int) sv_SelectedBuilding + 0x14), 2, 4, 5, 6);
			if (f.v18 == 0) {
				f.v18 = (int) gm_QueryEntities(*(int*) ((int) sv_SelectedBuilding + 0x14), 1, 4, 0x11);
			}
			if (f.v18 == 0) {
				f.v18 = (int) gm_QueryEntities(*(int*) (entity + 0x5d), 2, 0, 0x2a, 6);
			}
			if (f.v18 == 0) {
				f.v18 = (int) gm_QueryEntities(*(int*) (entity + 0x5d), 2, 0, 0x116, 6);
			}
			if (f.v18 != 0) {
				goto l_packet;
			}
		} else {
			/* 0x5babe5: the a2 == 2 / a2 == 4 rows, nothing otherwise */
			if (flags == 2) {
				f.v18 = (int) gm_QueryEntities(*(int*) ((int) sv_SelectedBuilding + 0x14), flags, 0, 0x1db, 6);
			} else if (flags == 4) {
				f.v18 = (int) gm_QueryEntities(*(int*) ((int) sv_SelectedBuilding + 0x14), 2, 0, 0x1dc, 6);
			} else {
				goto l_after;
			}
			if (f.v18 != 0) {
				goto l_packet;
			}
			goto l_after;
		}
	} else {
		f.v70 = flags & 1;
		if (f.v70 == 0) {
			if (flags == 2) {
				f.v18 = (int) gm_QueryEntities(*(int*) (entity + 0x5d), flags, 0, 0x1db, 6);
			} else if (flags == 4) {
				f.v18 = (int) gm_QueryEntities(*(int*) (entity + 0x5d), 2, 0, 0x1dc, 6);
			} else {
				goto l_after;
			}
			if (f.v18 != 0) {
				goto l_packet;
			}
			goto l_after;
		} else {
			/* 0x5bac1b: entity slot rows without an open container */
			f.v18 = (int) gm_QueryEntities(*(int*) (entity + 0x5d), 2, 0, 0x2a, 6);
			if (f.v18 != 0) {
				goto l_packet;
			}
			f.v18 = (int) gm_QueryEntities(*(int*) (entity + 0x5d), 2, 0, 0x116, 6);
			if (f.v18 != 0) {
				goto l_packet;
			}
			goto l_after;
		}
	}

l_packet:
	/* 0x5bac7d: the packet header word indexes the 0x41-byte record table */
	{
		int pk;

		pk = *(unsigned short*) (char*) f.v18;
		f.v94 = (int) g_99ec10 + (pk << 6) + pk;
	}

l_after:
	/* 0x5bac98: clear the 16 entity slots */
	e = f.v6D8;
	for (i = 0; i < 16; i++) {
		e->f0c = -1;
		e->f10 = -1;
		e->f14 = -1;
		e->f18 = -1;
		e->f00 = 0;
		e->f04 = 0;
		e->f08 = 0;
		for (j = 0; j < 3; j++) {
			e->fD8[j] = -1;
			e->fE4[j] = -1;
		}
		e++;
	}

	/* 0x5bacd6: open the panel window and select its fourth page */
	d2_DispatchTutorialInput(0x23, (char*) entity, 0, 0);
	f.v2c = d2_LoadForm(0, 0, "Handel\\Handel_Transport");
	d2_CenterDialogWindows(f.v2c);
	d2_SetForm(f.v2c, 4);

	if (f.v70 != 0) {
		/* 0x5bad0e: four row ids through the shared layout helper */
		d2_CreateButtonRow(d2_CurrentWindowId, 0, &f.v138, 4,
			*(int*) 0x143a50c, *(int*) 0x143a508,
			*(int*) 0x143a504, *(int*) 0x143a510);
		f.v6c = f.v140;
		f.v58 = f.v144;
		f.v34 = gm_ActiveTownIndex;
		f.v54 = f.v13C;
	} else {
		/* 0x5bad6d: one row id, then the entity's own selection field */
		d2_CreateButtonRow(d2_CurrentWindowId, 0, &f.v138, 1, *(int*) 0x143a50c);
		f.v6c = -1;
		f.v58 = -1;
		f.v34 = *(int*) (f.v14 + 0x65);
		f.v54 = -1;
	}

	/* 0x5bada3: page zero, then the transport-entity branch */
	f.vA0 = f.v138;
	d2_SetForm(f.v2c, 0);

	if (flags == 2) {
		f.v40 = 1;
		f.v50 = gm_CalcLevelProductionBonus(gm_LocalPlayerSlot);
	} else if (flags == 4) {
		f.v3c = 1;
		f.v50 = gm_CalcLevelProductionBonus(gm_LocalPlayerSlot);
	} else if (*(short*) (f.v14 + 0x27) == (short) gm_LocalPlayerSlot) {
		f.v4c = 1;
	} else {
		if (*(char*) f.v74 == 0xa) {
			f.v58 = 1;
			/* 0x5bae4e: the search result lands in the v88 slot, not a1 */
			f.v88 = (int) gm_StartFilteredEntitySearch(1, 0, 0x44);
			f.v40 = 1;
			f.v50 = gm_CalcLevelProductionBonus(gm_LocalPlayerSlot);
		}
		f.v3c = 1;
		if (f.v54 != -1) {
			d2_SetSlotVisibility(f.v54, 0);
		}
		if (f.v6c != -1) {
			d2_SetSlotVisibility(f.v6c, 0);
		}
		if (f.v58 != -1) {
			d2_SetSlotVisibility(f.v58, 0);
		}
	}

	d2_SetForm(f.v2c, 0);

	/* 0x5baec2: status-line message id for the current container state */
	if (d2_VisitedBuilding == 0 && d2_InteriorBuilding == 0) {
		d2_DrawPanelFrame(d2_CurrentWindowId, 0x70b, 0x73f);
	} else {
		int msg;
		unsigned char kind;

		kind = *(unsigned char*) f.v74;
		msg = 0x70b;
		if (kind == 0x13 || kind == 4 || kind == 0x10) {
			msg = 0x72f;
		} else if (kind == 8 || kind == 0xe) {
			msg = 0x70f;
		} else if (kind == 6) {
			msg = 0x713;
		} else if (kind == 0x16) {
			msg = 0x717;
		} else if (kind == 0xd || kind == 0xc || kind == 0xb) {
			msg = 0x71b;
		} else if (kind == 2 || kind == 7) {
			msg = 0x737;
		}
		/* the native arms push 0x73f when the trade flag is set */
		if (f.v3c == 0) {
			d2_DrawPanelFrame(d2_CurrentWindowId, msg, 0x741);
		} else {
			d2_DrawPanelFrame(d2_CurrentWindowId, msg, 0x73f);
		}
	}

	/* 0x5baf75: the item rectangle and its definition-table entry */
	d2_CreateWindowScrollbar(0x270, 0x15c, d2_CurrentWindowId,
	             d2_GetFormWindow(f.v2c, 2, 0x5e2, &f.v130, &f.v134, &f.vB4));
	g_00f8f080[f.vB4].font = 0x54;
	d2_SetForm(f.v2c, 3);

	if (flags == 2) {
		io_AppendText(0xd0, gm_TownTable + *(int*) (f.v14 + 0x65) * 0x2f4);
	} else if (flags == 4) {
		io_AppendText(0xcf, gm_TownTable + *(int*) (f.v14 + 0x65) * 0x2f4);
	} else if ((int) sv_SelectedBuilding != 0 && d2_VisitedBuilding == 0
	           && d2_InteriorBuilding == 0) {
		io_AppendText(0x9a8 + *(unsigned short*) ((int) sv_SelectedBuilding) * 2);
	} else {
		io_AppendText(f.v3c != 0 ? 0xcd : 0xcc);
	}

	d2_SetForm(f.v2c, 2);
	d2_ResetBuildingUiSlots();
	d2_SetOverlayAnimation(0, 0);
	d2_SetForm(f.v2c, 0);

	/* 0x5bb0ab: the two scroll-bar rows and the item table entry */
	d2_OpenEntityQuickSlots(d2_CurrentWindowId, 0x172, 0x64,
	             gm_LocalPlayerSlot, 0x1f3c);
	d2_SetForm(f.v2c, 0);
	f.v78 = d2_AddElementToWindow(0x261, 0xd2, 0x528, d2_CurrentWindowId);
	{
		int k;
		k = f.v78 * 0x2ec;
		*(int*) ((int) g_00f8f080 + k + 0x1c0) = 3;
		*(int*) ((int) g_00f8f080 + k + 0x48) = 1;
	}
	f.vB0 = d2_AddElementToWindow(0x261, 0x104, 0x527, d2_CurrentWindowId);
	f.v9c = f.vB0 * 0x2ec;
	*(int*) ((int) g_00f8f080 + f.v9c + 0x1c0) = 3;
	d2_ResetUiInputAndBounds();
	f.vA8 = f.vA0 * 0x2ec;
	f.vAC = f.v2c * 0xab;

l_5bb193:
	/* 0x5bb193: entity gate, then the trade-row lookup for the status code */
	{
	int ent;

	ent = f.v14;
	if ((d2_SelectedEntityUiFlags & 0x200) == 0) {
		if (gm_IsGebaeudeOpen(ent, 0, 0) == 0) {
			if ((short) gm_LocalPlayerSlot == *(short*) (ent + 0x27)) {
				goto l_c4;
			}
			f.v40 = 0;
			f.v3c = 0;
			f.v4c = 0;
			goto l_row;
		}
	}
	if (*(short*) (ent + 0x27) == (short) gm_LocalPlayerSlot) {
		goto l_c4;
	}
	if (*(char*) f.v74 == 0xa) {
		f.v68 = 1;
		f.v40 = 1;
	}
	f.v3c = 1;
	}
l_row:
	if (gm_HasActiveSpecialObject(gm_EntitySlotTable + (int) (gm_LocalPlayerSlot) * 0x21c, 0x299) != 0) {
		f.v3c = 1;
	}
	goto l_sel;
l_c4:
	f.v4c = 1;
l_sel:
	/* 0x5bb232: push the matching selection row into slot v88 */
	if (f.v80 != 0 && d2_DialogButtonAction != -1) {
		for (i = 0; i < 7; i++) {
			if (d2_CurrentElementId == f.vD4[i]) {
				f.v88 = (int) gm_QueryEntities(0, 2, 7, 0, f.vF0[i]);
				d2_DialogCloseRequested = 1;
			}
		}
	}

	/* 0x5bb287: hand the selected packet to the matching dialog module */
	if (*(char*) f.v74 == 0xa) {
		if (f.v18 != 0) {
			f.v38 = (int) d2_BuildProduktionSlotGrid(f.v18, f.v44);
			d2_LayoutProduktionSlotGrid(f.v2c, 1, 1, f.v14);
		}
	} else if (f.v18 != 0) {
		if (*(char*) f.v94 == 5) {
			f.v38 = (int) d2_SyncWareProduktionSlotGrid(f.v14, f.v18);
			d2_RefreshWorkshopInventoryGrids(f.v2c, 1, 1, f.v14);
		} else if (*(char*) f.v94 == 0x11) {
			f.v38 = (int) d2_SyncProduktionSlotGrid(f.v14, f.v18);
			d2_DrawProduktionSlotGrid(f.v2c, 1, 1, f.v14, f.v18);
		}
	}

	/* 0x5bb30b: release every entity slot and the handles it owns */
	e = f.v6D8;
	f.v10 = 0x10;
	do {
		idx = e->f00;
		if (idx != 0) {
			if (gm_QueryEntities(*(int*) (f.v7c + 0x5d), 2, 1,
			                 *(int*) (idx + 2), 3,
			                 (int) (gm_LocalPlayerSlot)) != 0
			    && e->f04 == 0) {
				if (gm_IsWarehouse(f.v14) == 0) {
					goto l_next;
				}
				if (gm_CanTradeWithObject(f.v14, idx) != 0) {
					goto l_next;
				}
			}
			if (e->f0c != -1) {
				e->f00 = 0;
				d2_DestroyGuiElement(e->f0c);
				e->f0c = -1;
				e->f04 = 0;
			}
			j = 3;
			idx = (int) e->fD8;
			do {
				if (*(int*) idx != -1) {
					d2_DestroyGuiElement(*(int*) idx);
					d2_RemoveElement(*(int*) (idx + 0xc));
					*(int*) idx = -1;
					*(int*) (idx + 0xc) = -1;
				}
				idx += 4;
			} while (--j != 0);
			d2_RemoveElement(e->f14);
			d2_DestroyGuiElement(e->f18);
			d2_DestroyGuiElement(e->f1c);
			e->f14 = -1;
			e->f18 = -1;
			e->f1c = -1;
			if (e->f10 != -1) {
				d2_CloseWindow(e->f10);
				e->f10 = -1;
			}
		}
l_next:
		e++;
	} while (--f.v10 != 0);

	/* 0x5bb419: fill the visible slot table from the trade container */
	f.v20 = (int) gm_QueryEntities(*(int*) (f.v7c + 0x5d), 2, 4, 0x1d, 3,
	                           (int) (gm_LocalPlayerSlot));
	for (f.v30 = 0;; ) {
		if (f.v20 == 0) {
			break;
		}
		d2_SetForm(f.v2c, 2);
		if (gm_IsWarehouse(entity) != 0) {
			if (gm_CanTradeWithObject(entity, f.v20) == 0) {
				goto l_fill_next;
			}
		}
		/* an entity that already owns a slot is left where it is */
		for (i = 0; i < 16; i++) {
			if (f.v6D8[i].f00 != 0
			    && *(int*) (f.v6D8[i].f00 + 2) == *(int*) (f.v20 + 2)) {
				break;
			}
		}
		if (i < 16) {
			goto l_fill_next;
		}
		for (i = 0; i < 16; i++) {
			if (f.v6D8[i].f00 == 0) {
				break;
			}
		}
		if (i >= 16) {
			goto l_fill_next;
		}
		if (he_StartHandlungSearch(3, 0, 0xf, 2, (int) (gm_LocalPlayerSlot), 3,
		                 *(int*) (f.v20 + 2)) != 0) {
			goto l_fill_next;
		}
		j = i * ((int) (*(short*) (d2_FileObjTable + 0x1ee7a)) + 0x16);
		e = f.v6D8 + i;
		e->f00 = f.v20;
		e->f0c = d2_AddElementToWindow(0x10, j + 0x16,
		                      0x4ae + (int) (*(unsigned short*) f.v20),
		                      d2_CurrentWindowId);
		f.v1c = j + 0x54;
		e->f18 = d2_AddElementToWindow(0x18, f.v1c, 0x5e8, d2_CurrentWindowId);
		e->f1c = d2_AddElementToWindow(0xac, f.v1c, 0x5eb, d2_CurrentWindowId);
		f.v1c = e->f0c;
		{
			int k;
			char* src;
			char* dst;

			k = e->f18 * 0x2ec;
			*(int*) ((int) g_00f8f080 + k + 0x4c) = 1;
			*(int*) ((int) g_00f8f080 + k + 0x1c0) = 0x43;
			*(char*) ((int) g_00f8f080 + k + 0xbc) = str_empty[0];
			k = e->f1c * 0x2ec;
			*(int*) ((int) g_00f8f080 + k + 0x4c) = 1;
			*(int*) ((int) g_00f8f080 + k + 0x1c0) = 0x43;
			src = *(char**) 0x144ad24;
			dst = (char*) ((int) g_00f8f080 + k + 0xbc);
			while ((*dst++ = *src++) != 0) {
				;
			}
		}
		d2_SetElementFont(e->f1c, 0x54);
		e->f14 = d2_AddWindowValueGauge(0x4b, j + 0x59, 0x50, 0, 0x64, 0x65, 0x2a,
		                      d2_CurrentWindowId);
		j += 0x26;
		e->f10 = d2_CreateChildWindow(0x10, j, 0xc8, 0x40, 0x10, d2_CurrentWindowId);
		d2_SetElementFont(g_00f8f120[e->f10].id, 0x53);
		g_00f8f080[f.v1c].f4c = 1;
		i = he_StartHandlungSearch(2, 3, *(int*) (f.v20 + 2), 0, 0x11);
		while (i != 0) {
			*(int*) (i + 0x52) = g_current_year;
			*(int*) (i + 0x56) = gm_GameTimeHour;
			*(int*) (i + 0x5a) = gm_GameTimeSliceDword;
			*(short*) (i + 0x5e) = gm_GameTimeTailWord;
			*(int*) (i + 0x70) = -1;
			i = fcn_005462a0();
		}
l_fill_next:
		f.v20 = (int) fcn_00502850();
		if (++f.v30 >= 0x10) {
			break;
		}
	}

	/* 0x5bb720: rebind each slot to the row the container returned for it */
	for (e = f.v6D8; e < f.v6D8 + 16; e++) {
		e->f04 = 0;
	}
	i = he_StartHandlungSearch(2, 0, 0xf, 2, (int) (gm_LocalPlayerSlot));
	if (i != 0) {
		do {
			for (j = 0; j < 16; j++) {
				if (f.v6D8[j].f00 != 0
				    && *(int*) (f.v6D8[j].f00 + 2) == *(int*) (i + 0xac)) {
					f.v6D8[j].f04 = i;
				}
			}
			i = fcn_005462a0();
		} while (i != 0);
	}
	f.v48 = 0;
	f.v30 = 0;
	f.v10 = 0;
	f.v28 = 0;

	do {
l_slot:
	/* 0x5bb798: per-slot panel refresh, f.v28 is the slot byte offset */
	e = (Ent5af320*) ((char*) f.v6D8 + f.v28);
	if (e->f00 != -1) {
		d2_CurrentWindowId = e->f00;
		io_AppendText((int) str_dollar_C);
	}
	idx = e->f00;
	if (idx == 0) {
		goto l_da9;
	}
	gm_CalcEntityInventoryStats(idx, (int*) &f.v158);
	if (f.v158 > 0) {
		j = 0;
		do {
			if (*(int*) ((char*) e + 0xd8 + j * 4) != -1) {
				g_00f8f080[*(int*) ((char*) e + 0xd8 + j * 4)].hidden =
				    (f.v38 != 0) ? 1 : 0;
			}
			j++;
		} while (j < f.v158);
	}
	if ((*(char*) (idx + 0x13) & 0x20) != 0) {
		io_AppendText(0xde, "$Z%s");
	}
	if (e->f14 != -1) {
		d2_CreateGuiWindow(e->f14, 0, 0x64, (int) (*(unsigned char*) (idx + 0x12)));
	}
	if (e->f18 == -1) {
		goto l_slot_handles;
	}
	i = (int) (*(signed char*) (idx + 0x28)) + 0x5e8;
	if (g_00f8f080[e->f18].f08 != i) {
		fcn_00466330(e->f18, i);
	}
	j = gm_CalcEscortCost(*(int*) (f.v15C + 0xac),
	                 (int) (*(signed char*) (idx + 0x28)));
	fcn_0051af00((int) (g_00f8f080[e->f18].u.text + 0x3c),
	             (int) (*(signed char*) (idx + 0x28)) + 0xe4, j);
	if (d2_DialogButtonAction == -1) {
		goto l_slot_handles;
	}
	if (d2_CurrentElementId != e->f18) {
		goto l_slot_handles;
	}
	if (!((*(char*) (idx + 0x20) & 1) != 0)) {
		*(signed char*) (idx + 0x28) =
		    (signed char) (((int) (*(signed char*) (idx + 0x28)) + 1) % 3);
		((char*) &f.v5c)[3] = *(signed char*) (idx + 0x28);
		cm_BeginPacketFieldDelta((char*) idx, *(int*) (idx + 2));
		cm_AppendCommandSyncField(1, 1, 0x28, (void*) (((char*) &f.v5c) + 3));
		cm_SendSetAttribute();
	} else {
		d2_ShowStatusBanner(*(int*) 0x143a580);
	}
l_slot_handles:
	/* 0x5bb937: item handle, selection frame and the list of owned rows */
	if (e->f1c != -1) {
		d2_SetControlText(e->f1c, (*(char*) (idx + 0x33) != 0)
		             ? *(int*) 0x144ad6c : *(int*) 0x144ad68);
	}
	if (d2_DialogButtonAction != -1 && d2_CurrentElementId == e->f1c
	    && (*(char*) (idx + 0x20) & 1) == 0) {
		d2_SetFormVisibility(f.v2c, 0);
		d2_RunTradeRouteEditor(idx);
		d2_SetFormVisibility(f.v2c, 1);
	}
	{
		int k;
		if ((*(char*) (idx + 0x13) & 0x20) != 0 || (*(char*) (idx + 0x20) & 1) != 0) {
			e->f08 = 0;
			k = e->f0c * 0x2ec;
			*(int*) ((int) g_00f8f080 + k + 0x50) = 1;
		} else {
			k = e->f0c * 0x2ec;
			*(int*) ((int) g_00f8f080 + k + 0x50) = 0;
		}
		*(int*) ((int) g_00f8f080 + k + 0x2c) = (e->f08 != 0) ? 1 : 0;
	}
	gm_CalcEntityInventoryStats(idx, (int*) &f.v158);
	d2_SetForm(f.v2c, 2);
	for (f.v20 = 0; f.v20 < f.v158; f.v20++) {
		for (j = 0; j < *(int*) &f.v15C; j++) {
			if (*(int*) ((char*) e + 0xd8 + f.v20 * 4) != -1
			    && *(short*) (f.v15C + 0x44 + j * 2) != 0
			    && g_00f8f080[*(int*) ((char*) e + 0xd8 + f.v20 * 4)].f08
			       == (int) (*(unsigned short*) (f.v15C + 0x44 + j * 2)) + 0xdf) {
				break;
			}
		}
		if (j >= *(int*) &f.v15C) {
			if (*(int*) ((char*) e + 0xd8 + f.v20 * 4) != -1) {
				d2_DestroyGuiElement(*(int*) ((char*) e + 0xd8 + f.v20 * 4));
				if (*(int*) ((char*) e + 0xe4 + f.v20 * 4) != -1) {
					d2_RemoveElement(*(int*) ((char*) e + 0xe4 + f.v20 * 4));
				}
				*(int*) ((char*) e + 0xd8 + f.v20 * 4) = -1;
				*(int*) ((char*) e + 0xe4 + f.v20 * 4) = -1;
			}
		}
	}
	/* 0x5bbaed: draw the row list of this slot */
	if (*(int*) &f.v15C > 0) {
		for (f.v24 = 0; f.v24 < *(int*) &f.v15C; f.v24++) {
			if (*(short*) (f.v15C + 0x44 + f.v24 * 2) == 0) {
				continue;
			}
			for (j = 0; j < f.v158; j++) {
				if (*(int*) ((char*) e + 0xd8 + j * 4) != -1
				    && g_00f8f080[*(int*) ((char*) e + 0xd8 + j * 4)].f08
				       == (int) (*(unsigned short*) (f.v15C + 0x44 + f.v24 * 2)) + 0xdf) {
					break;
				}
			}
			if (j < f.v158) {
				i = ((int*) ((char*) f.v6D8 + 0xd8))[f.v10 + f.v20];
				f.v1c = ((int*) (f.v15C + 4))[f.v24];
				j = d2_GetControlValue(i);
				if (j > 0) {
					f.v48 = 1;
				}
				d2_CreateGuiWindow(i, 0, ((int*) (f.v15C + 0x64))[f.v24], j);
				d2_CreateGuiWindow(((int*) ((char*) f.v6D8 + 0xe4))[f.v10 + f.v20], 0, f.v1c,
				             ((int*) (f.v15C + 0x64))[f.v24] - j);
				{
					int k;
					k = i * 0x2ec;
					*(int*) ((int) g_00f8f080 + k + 0x1c0) = 0x22;
					*(int*) ((int) g_00f8f080 + k + 0x1cc) = -1;
					*(int*) ((int) g_00f8f080 + k + 0x1d0) = 0;
					*(int*) ((int) g_00f8f080 + k + 0x5c) = 1;
				}
				fcn_0064d41a((int) (g_00f8f080[i].u.text + 0x3c), (int) "%s~ %li %s",
				             d2_ObjektNameTable[(int) (*(unsigned short*) (f.v15C + 0x44 + f.v24 * 2)) * 2],
				             ((int*) (f.v15C + 0x64))[f.v24],
				             *(int*) 0x144a160);
			}
			if (f.v20 < f.v158) {
				continue;
			}
			for (i = 0; i < f.v158; i++) {
				if (*(int*) ((char*) e + 0xd8 + i * 4) == -1) {
					f.v30 = gm_GetStorageSlotCapacity(*(int*) (f.v15C + 0xb0),
					                     (int) (*(unsigned short*) (f.v15C + 0x44 + f.v24 * 2)));
					j = ((int*) &f.v10C[0])[3 * ((int) (*(short*) e->f00) - 0x134) + i];
					j -= g_00f8f120[d2_CurrentWindowId].x;
					j += g_00f8f080[e->f0c].x;
					f.v1c = ((int) (*(short*) (d2_FileObjTable + 0x1ee7a)) + 0x16) * f.v30 + 0x1e;
					e->fE4[f.v10 + i] = d2_AddWindowValueGauge(j - 8, f.v1c - 5, 0x2f, 0, f.v30,
					                                 0x6a, 0x2d, d2_CurrentWindowId);
					{
						int d;
						d = d2_AddWindowField(j, f.v1c,
						                 (int) (*(unsigned short*) (f.v15C + 0x44 + f.v24 * 2)) + 0xdf,
						                 0x8a, d2_CurrentWindowId);
						e->fD8[f.v10 + i] = d;
						d2_SetElementFont(d, 0x54);
					}
					break;
				}
			}
		}
	}
l_da9:
	f.v28 += 0xf0;
	f.v30++;
	f.v10 += 0x3c;
	} while (f.v28 < 0xf00);

	/* 0x5bbdd5: keep the row selection cursor in sync with the open container */
	if (d2_InventoryPanelWindowId != -1) {
		if (f.v38 == 0) {
			f.v60 = d2_UpdateActiveItemSlots();
			i = d2_GetControlValue(f.v78);
			if (f.v90 != i) {
				if (i != 0) {
					d2_SetSlotVisibility(g_00f8f120[d2_InventoryPanelWindowId].id, 1);
					d2_SetForm(f.v2c, 2);
					d2_SetSlotVisibility(g_00f8f120[d2_CurrentWindowId].id, 0);
				} else {
					d2_SetSlotVisibility(g_00f8f120[d2_InventoryPanelWindowId].id, 0);
					d2_SetForm(f.v2c, 2);
					d2_SetSlotVisibility(g_00f8f120[d2_CurrentWindowId].id, 1);
				}
			}
			f.v90 = i;
		} else {
			d2_UpdateActiveItemSlots();
		}
	}
	/* 0x5bbeb7: mark the open container row in the item table */
	i = 0;
	j = 0;
	for (e = f.v6D8; e < f.v6D8 + 16; e++) {
		if (e->f00 == 0 || e->f08 == 0) {
			continue;
		}
		if (*(unsigned char*) (e->f00 + 0x12) < 0x64) {
			j = 1;
		}
		i++;
	}
	if (i != 0) {
		{
			int k;
			k = f.vA8;
			*(int*) ((int) g_00f8f080 + k + 0x3c) = 0;
			*(int*) ((int) g_00f8f080 + k + 0x50) = 0;
		}
		if (f.v58 != -1) {
			int k;
			k = f.v58 * 0x2ec;
			*(int*) ((int) g_00f8f080 + k + 0x3c) = 0;
			*(int*) ((int) g_00f8f080 + k + 0x50) = 0;
		}
		if (f.v70 != 0) {
			/* the native body also stores through a -1 row here */
			if (j != 0 && f.v54 != -1) {
				int k;
				k = f.v54 * 0x2ec;
				*(int*) ((int) g_00f8f080 + k + 0x3c) = 0;
				*(int*) ((int) g_00f8f080 + k + 0x50) = 0;
			} else {
				int k;
				k = f.v54 * 0x2ec;
				*(int*) ((int) g_00f8f080 + k + 0x3c) = 1;
				*(int*) ((int) g_00f8f080 + k + 0x50) = 1;
			}
		}
	} else {
		{
			int k;
			k = f.vA8;
			*(int*) ((int) g_00f8f080 + k + 0x3c) = 1;
			*(int*) ((int) g_00f8f080 + k + 0x50) = 1;
		}
		if (f.v70 != 0) {
			if (f.v58 != -1) {
				int k;
				k = f.v58 * 0x2ec;
				*(int*) ((int) g_00f8f080 + k + 0x3c) = 1;
				*(int*) ((int) g_00f8f080 + k + 0x50) = 1;
			}
			if (f.v54 != -1) {
				int k;
				k = f.v54 * 0x2ec;
				*(int*) ((int) g_00f8f080 + k + 0x3c) = 1;
				*(int*) ((int) g_00f8f080 + k + 0x50) = 1;
			}
		}
	}
	if (f.v38 == 0 && f.v60 == 0) {
		ResetDisplayCounters();
	}
	if (f.v48 != 0) {
		/* 0x5bbff0: refresh the three owned-row handles of every filled slot */
		i = 0x10;
		for (e = f.v6D8; i != 0; i--, e++) {
			if (e->f00 == 0) {
				continue;
			}
			j = 3;
			idx = (int) e->fD8;
			do {
				if (*(int*) idx != -1) {
					d2_AddDisplayCounter(g_00f8f080[*(int*) idx].f08,
					             d2_GetControlValue(*(int*) idx));
				}
				idx += 4;
			} while (--j != 0);
		}
	}

	/* 0x5bc052: tear the display counters down before the panel reloads */
	if (io_RightButtonReleased != 0) {
		if (CountDisplayCounters() != 0) {
			d2_ClearSelectedControl();
			for (e = f.v6D8; e < f.v6D8 + 16; e++) {
				if (e->f00 != 0) {
					for (j = 0; j < 3; j++) {
						if (e->fD8[j] != -1) {
							d2_CreateGuiWindow(e->fD8[j], 0, 0, 0);
						}
					}
				}
			}
			for (idx = 0x6f58b0; idx < 0x6f5a70; idx += 0x38) {
				if (*(int*) idx != -1) {
					d2_CreateGuiWindow(*(int*) idx, 0, 0, 0);
				}
			}
			for (idx = 0x6f4f70; idx < 0x6f52f0; idx += 0x38) {
				if (*(int*) idx != -1) {
					d2_CreateGuiWindow(*(int*) idx, 0, 0, 0);
				}
			}
			for (idx = (int) g_776c60; idx < (int) (g_776c60 + 12); idx += 8) {
				if (*(int*) (idx + 4) != 0) {
					d2_CreateGuiWindow(*(int*) idx, 0, 0, 0);
				}
			}
			f.v48 = 0;
			f.v38 = 0;
			f.v60 = 0;
			ResetDisplayCounters();
		} else {
			/* 0x5bc131: the panel's own row, or the pending dialog refresh */
			i = f.v78;
			if (d2_GetControlValue(i) != 0) {
				d2_CreateGuiWindow(i, 0);
				f.v90 = 0;
			} else if (d2_CanCloseWindowDuringTutorial() == 1) {
				d2_DialogCloseRequested = 1;
				if (f.v88 == 0 && d2_SelectedBuilding == 0) {
					d3_EndCameraAndUiMode();
				}
			}
		}
	}

	/* 0x5bc182: the selected container row drives one slot of the panel */
	if (d2_DialogButtonAction == -1 || f.v48 != 0) {
		goto l_5bc453;
	}
	if (f.v38 == 0) {
		goto l_5bc3fa;
	}
	/* 0x5bc1a9: locate the slot bound to the current row id */
	e = f.v6D8;
	for (j = 0; j < 16; j++, e++) {
		if (e->f00 != 0 && e->f0c == d2_CurrentElementId) {
			goto l_5bc2f8;
		}
	}
	goto l_5bc1d3;
l_5bc2f8:
	if ((*(char*) (e->f00 + 0x20) & 1) != 0) {
		d2_ShowStatusBanner(*(int*) 0x143a580);
		goto l_5bc1d3;
	}
	idx = (int) e->f00;
	e->f08 = 1;
	if (idx == 0) {
		goto l_5bc1d3;
	}
	if (f.v3c != 0 || f.v4c != 0) {
		goto l_5bc370;
	}
	fcn_0051af00((int) f.v15D8, 0xee, f.v14);
	d2_ShowStatusBanner((int) (f.v15D8 + 0xc));
	goto l_5bc1d7;
l_5bc370:
	i = (int) gm_QueryEntities(*(int*) (idx + 0x14), 1, 0, 0x1dd);
	d2_ClearSelectedControl();
	if (gm_RandomFloat01() < 0.25f) {
		ob_TransportFromLager(*(int*) (i + 2), f.v18, f.v14, f.v3c, 0, f.v50,
		                      f.v34, flags);
	} else {
		ob_TransportFromLager(*(int*) (i + 2), f.v18, f.v14, f.v3c, 0, 1.0f,
		                      f.v34, flags);
	}
	goto l_5bc1d7;
l_5bc1d3:
l_5bc1d7:
	/* 0x5bc1d7: the selection table decides between layout and overlay */
	if (d2_HoveredWindow != ((int*) g_00fb1020)[f.vAC + 2] || f.v48 == 0
	    || g_14ce8d8 == 0) {
		goto l_5bcb2a;
	}
	if (f.v40 == 0 && f.v4c == 0) {
		goto l_5bcacf;
	}
	*(float*) &f.v64 = 1.0f;
	if (gm_RandomFloat01() < 0.25f) {
		*(float*) &f.v64 = f.v50;
	}

	/* 0x5bc240: lay out every filled slot from its three owned rows */
	f.v1c = 0x10;
	f.v24 = (int) f.v6D8;
l_5bc253:
	idx = *(int*) f.v24;
	if (idx == 0) {
		goto l_5bcab6;
	}
	if ((*(char*) (idx + 0x20) & 1) != 0) {
		goto l_5bcab6;
	}
	f.v98 = (int) gm_QueryEntities(*(int*) (idx + 0x14), 1, 0, 0x1dd);
	f.v30 = (int) (((Ent5af320*) f.v24)->fD8);
	for (f.v20 = 3; f.v20 != 0; f.v20--, f.v30 += 4) {
		j = *(int*) f.v30;
		if (j == -1) {
			continue;
		}
		slot_value = g_00f8f080[j].f08 - 0xdf;
		if (f.v40 == 0) {
			i = 0;
		} else if (f.v68 == 0) {
			i = (int) (gm_GetSeasonPrice(slot_value, f.v34) * *(float*) (f.v14 + 0x49));
		} else {
			i = (int) (gm_GetSeasonPrice(slot_value, f.v34) * 0.9);
		}
		if (flags == 2 || flags == 4) {
			i = (int) gm_GetSeasonPrice(slot_value, (int) (*(unsigned char*) (f.v14 + 0x65)));
		}
		f.v10 = i;
		idx = 1;
		if (f.v34 != 0
		    && gm_QueryEntities(*(int*) (f.v34 + 0x14), 1, 0, slot_value) == 0) {
			idx = 0;
		}
		j = d2_GetControlValue(j);
		if (idx == 0) {
			goto l_5bca65;
		}
		if (j <= 0) {
			continue;
		}
		idx = gm_eval_SlotVoll(f.v18, slot_value, j);
		f.v28 = idx * i;
		f.vA4 = (int) gm_ConvertUnitsToAmount(1, (int) (gm_ActiveTownIndex));
		*(float*) &f.v84 = (float) f.v28;
		if ((int) (*(float*) &f.v84 * *(float*) &f.v64 - *(float*) &f.v84)
		    < f.vA4) {
			*(float*) &f.v64 = 1.0f;
		}
		if (f.v80 != 0) {
			if (d2_DispatchTutorialEvent(0x28, f.v14, 0, slot_value) == 0) {
				continue;
			}
			d2_DispatchTutorialInput(0x28, f.v14, 0, slot_value);
		} else if (f.v70 != 0) {
			if (d2_DispatchTutorialEvent(0x26, f.v14, 0, slot_value) == 0) {
				continue;
			}
			d2_DispatchTutorialInput(0x26, f.v14, 0, slot_value);
		}
		if (idx <= 0) {
			continue;
		}
		cm_SendSellObjekt(*(int*) (f.v18 + 2), *(int*) (f.v98 + 2), slot_value, idx,
		             f.v34, (int) (*(float*) &f.v10 * *(float*) &f.v64));
		if (*(float*) &f.v64 == 1.0f) {
			fcn_0051af00((int) (f.v210 + 0x238), 0xed,
			             (int) (*(float*) &f.v28 * *(float*) &f.v64
			                    - *(float*) &f.v28));
			d2_ShowStatusBanner((int) (f.v210 + 0x240));
			sb_PlayVoice(0, (int) "RollenKurz_s_01", 1, 0x3f, 0x7f, 0, 0);
		}
		d2_CreateGuiWindow(*(int*) f.v30, 0, 0x64, 0);
		continue;
	l_5bca65:
		if (j <= 0) {
			continue;
		}
		fcn_0051af00((int) (f.v210 + 0x238), 0xeb, slot_value + slot_value + 0x9a8);
		d2_ShowModalMessageBox((int) (f.v210 + 0x238), 0x100);
	}
l_5bcab6:
	f.v24 += 0xf0;
	f.v1c--;
	if (f.v1c != 0) {
		goto l_5bc253;
	}

l_5bcacf:
	ResetDisplayCounters();
	for (idx = 0x6f58b0; idx < 0x6f5a70; idx += 0x38) {
		if (*(int*) idx != -1) {
			d2_CreateGuiWindow(*(int*) idx, 0, 0, 0);
		}
	}
	for (idx = 0x6f4f70; idx < 0x6f52f0; idx += 0x38) {
		if (*(int*) idx != -1) {
			d2_CreateGuiWindow(*(int*) idx, 0, 0, 0);
		}
	}
	io_ClearInputState();
	goto l_5bcd16;

l_5bc3fa:
	/* 0x5bc3fa: without a container the slot flags are only toggled */
	if (f.v60 != 0) {
		goto l_5bc453;
	}
	e = f.v6D8;
	for (j = 0x10; j != 0; j--, e++) {
		if (e->f00 == 0 || e->f0c != d2_CurrentElementId) {
			continue;
		}
		if (!((*(char*) (e->f00 + 0x20) & 1) != 0)) {
			e->f08 = (e->f08 == 0) ? 1 : 0;
		} else {
			d2_ShowStatusBanner(*(int*) 0x143a580);
		}
	}
	goto l_5bc1d3;

l_5bc453:
	/* 0x5bc453: the row id of the selection against the shared row tables */
	j = f.v60;
	idx = ((int*) g_00fb1020)[f.vAC + 2];
	if (d2_HoveredWindow != idx || j == 0 || g_14ce8cc == 0) {
		goto l_5bc5ce;
	}
	if (f.v4c != 0) {
		/* 0x5bc494: every trade entry of the current row */
		for (i = (int) g_776c60; i < (int) (g_776c60 + 12); i += 8) {
			int slot;

			if (*(int*) (i + 4) == 0) {
				continue;
			}
			slot = (int) (*(unsigned short*) *(int*) (i + 4));
			j = d2_GetControlValue(*(int*) i);
			if (j == 0) {
				continue;
			}
			if (f.v40 == 0) {
				*(float*) &f.v84 = 0.0f;
			} else if (f.v68 == 0) {
				*(float*) &f.v84 =
				    gm_GetSeasonPrice(slot, f.v34) * *(float*) (f.v14 + 0x49);
			} else {
				*(float*) &f.v84 = gm_GetSeasonPrice(slot, f.v34) * 0.9;
			}
			idx = 1;
			if (f.v44 != 0
			    && gm_QueryEntities(*(int*) (f.v44 + 0x14), 1, 0, slot) == 0) {
				idx = 0;
			}
			j = gm_eval_SlotVoll(f.v18, slot, j);
			if (idx == 0 || j == 0) {
				continue;
			}
			cm_SendSellObjekt(*(int*) (f.v18 + 2),
			             *(int*) (*(int*) 0x6f2f60 + 4), slot, j, f.v34,
			             (int) (*(float*) &f.v84));
			d2_CreateGuiWindow(*(int*) i, 0, 0x64, 0);
		}
		goto l_5bc1d3;
	}
	/* 0x5bc5a2: no trade entry, refresh the pick slot text */
	fcn_0051af00((int) (f.v210 + 0x348), 0xef);
	d2_ShowModalMessageBox((int) (f.v210 + 0x348), 0x100);
	goto l_5bc1d3;

l_5bc5ce:
	if (d2_HoveredWindow != d2_InventoryPanelWindowId || g_14ce8cc == 0
	    || f.v60 != 0 || f.v38 == 0) {
		goto l_5bc700;
	}
	if (f.v3c != 0 || f.v4c != 0) {
		goto l_5bc632;
	}
	fcn_0051af00((int) f.v16D8, 0xee, f.v14);
	d2_ShowStatusBanner((int) (f.v16D8 + 0xc));
	goto l_5bc1d7;

l_5bc632:
	d2_ClearSelectedControl();
	if (gm_RandomFloat01() < 0.25f) {
		ob_TransportFromLager(*(int*) (*(int*) 0x6f2f60 + 4), f.v18, f.v14, f.v3c,
		                      (int) (gm_EntitySlotTable
		                             + (int) (gm_LocalPlayerSlot) * 0x21c),
		                      f.v50, f.v34, flags);
	} else {
		ob_TransportFromLager(*(int*) (*(int*) 0x6f2f60 + 4), f.v18, f.v14, f.v3c,
		                      (int) (gm_EntitySlotTable
		                             + (int) (gm_LocalPlayerSlot) * 0x21c),
		                      1.0f, f.v34, flags);
	}
	for (idx = (int) g_776c60; idx < (int) (g_776c60 + 12); idx += 8) {
		if (*(int*) (idx + 4) == 0) {
			continue;
		}
		d2_CreateGuiWindow(*(int*) idx, 0, 0, 0);
	}
	io_ClearInputState();
	goto l_5bc1d7;

l_5bc700:
	/* 0x5bc700: bind the current row to its slot and lay its rows out */
	if (f.v3c == -1 || f.v60 == 0 || g_14ce8d8 == 0) {
		goto l_5bc1d3;
	}
	e = f.v6D8;
	for (i = 0; i < 16; i++, e++) {
		if (e->f00 == 0 || e->f0c != d2_CurrentElementId) {
			continue;
		}
		if ((*(char*) (e->f00 + 0x20) & 1) != 0) {
			d2_ShowStatusBanner(*(int*) 0x143a580);
			continue;
		}
		e->f08 = 1;
		f.v20 = (int) e->f00;
	}
	if (f.v20 == 0) {
		goto l_5bc1d3;
	}
	for (idx = (int) g_776c60; idx < (int) (g_776c60 + 12); idx += 8) {
		int slot;

		f.vA4 = (int) gm_QueryEntities(*(int*) (f.v20 + 0x14), 1, 0, 0x1dd);
		if (*(int*) (idx + 4) == 0) {
			continue;
		}
		slot = (int) (*(unsigned short*) *(int*) (idx + 4));
		j = d2_GetControlValue(*(int*) idx);
		if (j == 0) {
			continue;
		}
		if (f.v40 == 0) {
			*(float*) &f.v84 = 0.0f;
		} else if (f.v68 == 0) {
			*(float*) &f.v84 =
			    gm_GetSeasonPrice(slot, f.v34) * *(float*) (f.v14 + 0x49);
		} else {
			*(float*) &f.v84 = gm_GetSeasonPrice(slot, f.v34) * 0.9;
		}
		j = gm_eval_SlotVoll(f.vA4, slot, j);
		if (j == 0) {
			continue;
		}
		cm_SendSellObjekt(*(int*) (f.vA4 + 2),
		             *(int*) (*(int*) 0x6f2f60 + 4), slot, j, f.v34,
		             (int) (*(float*) &f.v84));
		d2_CreateGuiWindow(*(int*) idx, 0, 0x64, 0);
	}
	goto l_5bc1d7;

l_5bcb2a:
	/* 0x5bcb2a: the second overlay pass over the same selection row */
	if (f.vD0 != d2_InventoryPanelWindowId) {
		goto l_5bcd16;
	}
	if (g_14ce8d8 == 0) {
		goto l_5bcd16;
	}
	if (f.v60 != 0) {
		goto l_5bcd16;
	}
	if (f.v48 == 0) {
		goto l_5bcd16;
	}
	if (f.v40 == 0 && f.v4c == 0) {
		goto l_5bcd16;
	}
	f.v10 = (int) f.v6D8;
	f.v28 = 0x10;
l_5bcb82:
	idx = *(int*) f.v10;
	if (idx == 0) {
		goto l_5bcc9f;
	}
	if ((*(char*) (idx + 0x20) & 1) != 0) {
		goto l_5bcc9f;
	}
	h = (int) gm_QueryEntities(*(int*) (idx + 0x14), 1, 0, 0x1dd);
	f.v30 = f.v10 + 0xd8;
	for (f.v1c = 3; f.v1c != 0; f.v1c--, f.v30 += 4) {
		j = *(int*) f.v30;
		if (j == -1) {
			continue;
		}
		slot_value = g_00f8f080[j].f08 - 0xdf;
		if (f.v34 != 0
		    && gm_QueryEntities(*(int*) (f.v34 + 0x14), 1, 1, slot_value) == 0) {
			continue;
		}
		f.v38 = d2_GetControlValue(j);
		if (f.v38 <= 0) {
			continue;
		}
		f.v38 = gm_CheckInventoryCapacity(
			gm_EntitySlotTable + gm_LocalPlayerSlot * 0x21c,
			slot_value, f.v38);
		if (f.v38 <= 0) {
			continue;
		}
		cm_SendSellObjekt(*(int*) (gm_EntityIdField
		                      + gm_LocalPlayerSlot * 0x21c),
		             slot_value, *(int*) (h + 2), f.v38, f.v24, 0);
		d2_CreateGuiWindow(j, 0, 0x64, 0);
	}
l_5bcc9f:
	f.v10 += 0xf0;
	if (--f.v28 != 0) {
		goto l_5bcb82;
	}
	ResetDisplayCounters();
	for (idx = 0x6f58b0; idx < 0x6f5a70; idx += 0x38) {
		if (*(int*) idx != -1) {
			d2_CreateGuiWindow(*(int*) idx, 0, 0, 0);
		}
	}
	for (idx = 0x6f4f70; idx < 0x6f52f0; idx += 0x38) {
		if (*(int*) idx != -1) {
			d2_CreateGuiWindow(*(int*) idx, 0, 0, 0);
		}
	}
	io_ClearInputState();
	goto l_5bcd16;

l_5bcd16:
	/* 0x5bcd16: the selection flags of the panel row */
	if (f.vB0 != -1) {
		if (f.v48 == 0) {
			if (f.v38 == 0) {
				goto l_5bcd7b;
			}
			if (f.v68 != 0) {
				goto l_5bcd7b;
			}
			if (*(short*) (f.v14 + 0x27) != (short) gm_LocalPlayerSlot) {
				goto l_5bcd7b;
			}
		} else {
			if (f.v38 != 0) {
				goto l_5bcd7b;
			}
		}
		{
			int k;
			k = f.v9c;
			*(int*) ((int) g_00f8f080 + k + 0x4c) = 1;
			*(int*) ((int) g_00f8f080 + k + 0x50) = 0;
		}
		*(int*) ((int) g_00f8f080 + f.v9c + 0x1c0) = 3;
		goto l_5bcd9a;
	l_5bcd7b:
		{
			int k;
			k = f.v9c;
			*(int*) ((int) g_00f8f080 + k + 0x4c) = 0;
			*(int*) ((int) g_00f8f080 + k + 0x50) = 1;
		}
	}
l_5bcd9a:

	/* 0x5bcd9a: the dialog status of the current trade row */
	switch (d2_DialogButtonAction) {
	case 0x527:
		if (d2_ShowModalMessageBox(*(int*) 0x143a5a4, 0x101) == 0) {
			goto l_5bd632;
		}
		if (f.v38 == 0) {
			goto l_5bceb8;
		}
		if (f.v40 != 0) {
			goto l_5bd632;
		}
		/* 0x5bcdeb: the owner rows of the two 0x38-stride tables */
		for (idx = 0x6f58b0; idx < 0x6f5a70; idx += 0x38) {
			if (*(int*) idx == -1) {
				continue;
			}
			j = d2_GetControlValue(*(int*) idx);
			if (j > 0) {
				cm_SendSellObjekt(-1, *(int*) (f.v18 + 2), *(int*) (idx - 0x10), j,
				             (int) (gm_ActiveTownIndex), 0);
				d2_CreateGuiWindow(*(int*) idx, 0, *(int*) (idx + 0x20), 0);
			} else if (j < 0) {
				cm_RequestClearLagerslot(*(int*) (f.v18 + 2), *(int*) (idx - 0x10));
			}
		}
		for (idx = 0x6f4f70; idx < 0x6f52f0; idx += 0x38) {
			if (*(int*) idx == -1) {
				continue;
			}
			j = d2_GetControlValue(*(int*) idx);
			if (j > 0) {
				cm_SendSellObjekt(-1, *(int*) (f.v18 + 2), *(int*) (idx - 0x10), j,
				             (int) (gm_ActiveTownIndex), 0);
				d2_CreateGuiWindow(*(int*) idx, 0, *(int*) (idx + 0x20), 0);
			} else if (j < 0) {
				cm_RequestClearLagerslot(*(int*) (f.v18 + 2), *(int*) (idx - 0x10));
			}
		}
		goto l_5bd632;

	l_5bceb8:
		/* 0x5bceb8: the three owned rows of every filled slot */
		if (f.v48 == 0) {
			goto l_5bd632;
		}
		f.v24 = 0;
		f.v10 = (int) f.v6D8;
	l_5bced7:
		idx = *(int*) f.v10;
		if (idx != 0) {
			f.vA4 = (int) gm_QueryEntities(*(int*) (idx + 0x14), 1, 0, 0x1dd);
			f.v30 = f.v10 + 0xd8;
			for (f.v1c = 3; f.v1c != 0; f.v1c--, f.v30 += 4) {
				if (*(int*) f.v30 == -1) {
					continue;
				}
				slot_value = g_00f8f080[*(int*) f.v30].f08 - 0xdf;
				j = d2_GetControlValue(*(int*) f.v30);
				if (j <= 0) {
					continue;
				}
				cm_SendSellObjekt(-1, *(int*) (f.vA4 + 2), slot_value, j,
				             (int) (gm_ActiveTownIndex), 0);
				d2_CreateGuiWindow(*(int*) f.v30, 0,
				             ((int*) (f.v15C + 0x64))[f.v24], 0);
			}
		}
		f.v24++;
		f.v10 += 0xf0;
		if (f.v24 < 0x10) {
			goto l_5bced7;
		}
		goto l_5bd632;
	case 2:
l_5bcf9f:
	/* 0x5bcf9f: the row record of the transport dialog */
	f.vD0 = d2_CurrentElementId;
	if (f.vD0 == f.vA0) {
		memset(f.v210, 0, 0x50);
		*(int*) (f.v210 + 4) = 0x400;
		*(int*) (f.v210 + 0x10) = 0;
		*(int*) (f.v210 + 0xc) = 0x40000001;
		*(int*) (f.v210 + 8) = (int) 0xf07d7fb0;
		d2_SetFormVisibility(f.v2c, 0);
		j = 0;
		e = f.v6D8;
		for (i = 0x10; i != 0; i--, e++) {
			if (e->f00 != 0 && e->f08 != 0) {
				((int*) f.v17D8)[j] = (int) e->f00;
				j++;
			}
		}
		fcn_0051af00((int) (f.v210 + 0x138), 0xce, j, 0xc10);
		idx = d2_RunCityScrollMapDialog(0x11, (int) f.v210, (int) (f.v210 + 0x138), 0, 0);
		if (idx == 0 || idx == entity) {
			goto l_5bd26b;
		}
		f.v10 = 0;
		if (gm_CheckEntityType(idx) != 0) {
			goto l_5bd177;
		}
		if (gm_CheckEntityType(entity) != 0) {
			goto l_5bd177;
		}
		/* 0x5bd0a1: sum the row heights of every slot for this dialog */
		e = f.v6D8;
		for (f.v1c = 0x10; f.v1c != 0; f.v1c--, e++) {
			if (e->f00 == 0 || e->f08 == 0) {
				continue;
			}
			if (*(char*) idx == 0x47 && *(short*) e->f00 != 0x136) {
				fcn_0051af00((int) (f.v210 + 0x138), 0xe9);
				d2_ShowModalMessageBox((int) (f.v210 + 0x138), 0x100);
				continue;
			}
			if (d2_VisitedBuilding != 0 || d2_InteriorBuilding != 0) {
				i = (int) (*(unsigned char*) (d2_VisitedBuilding != 0
				                              ? (unsigned char*) d2_VisitedBuilding
				                              : d2_InteriorBuilding));
				if (g_entity_type_table[i + i * 0x24c] == 0x1e
				    || g_entity_type_table[i + i * 0x24c] == 0x1d) {
					goto l_5bd135;
				}
			}
			d3snd_PlayWorkerOrderVoice();
		l_5bd135:
			cm_CompleteAction0x0f((int) e->f00);
			f.v10 += cm_DispatchCartTransfer((int) (gm_LocalPlayerSlot),
			                      (int) e->f00, flags, idx);
		}
		goto l_5bd240;

l_5bd177:
		/* 0x5bd177: the same sum over a non-dialog entity list */
		e = f.v6D8;
		for (f.v1c = 0x10; f.v1c != 0; f.v1c--, e++) {
			if (e->f00 == 0 || e->f08 == 0) {
				continue;
			}
			if (*(char*) idx == 0x47 && *(short*) e->f00 != 0x136) {
				fcn_0051af00((int) (f.v210 + 0x138), 0xe9);
				d2_ShowModalMessageBox((int) (f.v210 + 0x138), 0x100);
				continue;
			}
			if (d2_VisitedBuilding != 0 || d2_InteriorBuilding != 0) {
				i = (int) (*(unsigned char*) (d2_VisitedBuilding != 0
				                              ? (unsigned char*) d2_VisitedBuilding
				                              : d2_InteriorBuilding));
				if (g_entity_type_table[i + i * 0x24c] == 0x1e
				    || g_entity_type_table[i + i * 0x24c] == 0x1d) {
					goto l_5bd207;
				}
			}
			d3snd_PlayWorkerOrderVoice();
		l_5bd207:
			cm_CompleteAction0x0f((int) e->f00);
			f.v10 += cm_DispatchCartTransfer((int) (gm_LocalPlayerSlot),
			                      (int) e->f00, flags, idx);
		}

l_5bd240:
		if (f.v10 > 0) {
			fcn_0051af00((int) (f.v210 + 0x138), 0xe3, f.v10);
			d2_ShowStatusBanner((int) (f.v210 + 0x138));
		}
l_5bd26b:
		d2_SetFormVisibility(f.v2c, 1);
		goto l_5bd62f;
}
	/* 0x5bd27c: the selected row, routed by the dialog that owns it */
	if (f.vD0 == f.v54 && (signed char) gm_ClientModeFlags >= 0) {
		/* 0x5bd295: weighted height of every filled slot */
		f.vCC = 0;
		f.v20 = 0;
		f.v24 = 0;
		e = f.v6D8;
		f.v1c = 0x10;
		do {
			if (e->f00 != 0 && e->f08 != 0) {
				f.v98 = 0x64 - *(unsigned char*) (e->f00 + 0x12);
				if (f.v98 > f.vCC) {
					f.vCC = f.v98;
				}
				f.v20 = (int) ((float) f.v98
				               * (eval_ObjektPreis2Credits(
				                      (int) *(unsigned short*) (e->f00),
				                      0x64)
				                  * 0.008f)
				               + (float) f.v20);
				f.v24++;
			}
			e++;
		} while (--f.v1c != 0);
		if (f.v24 == 0) {
			goto l_5bd632;
		}
		/* 0x5bd32c: the 0x7f4c00 box record and its text */
		f.vBC = gm_GameTimeHour;
		f.vC0 = gm_GameTimeSliceDword;
		f.vB8 = g_current_year;
		*(short*) &f.vC4 = gm_GameTimeTailWord;
		gm_AddTime((int) &f.vB8, 0, f.vCC * 4, 0);
		gm_PackGameTime((int) &f.vB8, (int) &f.vC8);
		fcn_0051af00((int) (f.v210 + 0x348), 0xdd, f.v20, f.v24,
		             (int) ((signed char*) &f.vC8)[0],
		             (int) ((signed char*) &f.vC8)[1],
		             (int) *(short*) ((char*) &f.vC8 + 2));
		if (d2_ShowModalMessageBox((int) (f.v210 + 0x348), 0x101) == 0) {
			goto l_5bd632;
		}
		if (gm_CheckEntityStock((int) (gm_EntitySlotTable
		                       + gm_LocalPlayerSlot * 0x21c),
		                f.v20, (int) gm_ActiveTownIndex) == 0) {
			goto l_5bd632;
		}
		cm_RequestMoveCredits(-1,
		             *(int*) (gm_EntityIdField
		                      + gm_LocalPlayerSlot * 0x21c),
		             (char) f.v34, f.v20);
		/* 0x5bd440: one 0x500bb0 row box per filled slot */
		e = f.v6D8;
		f.v1c = 0x10;
		do {
			if (e->f00 != 0 && e->f08 != 0) {
				memset(f.v210 + 0x50, 0, 0xf8);
				f.v210[0x54] = 0x10;
				f.v210[0x86] = 1;
				*(int*) (f.v210 + 0x5c) = *(int*) ((char*) entity + 1);
				*(int*) (f.v210 + 0x58) =
					*(int*) (gm_EntityIdField
					         + gm_LocalPlayerSlot * 0x21c);
				*(int*) (f.v210 + 0x78) = g_current_year;
				*(int*) (f.v210 + 0x7c) = gm_GameTimeHour;
				*(int*) (f.v210 + 0x80) = gm_GameTimeSliceDword;
				*(short*) (f.v210 + 0x84) = gm_GameTimeTailWord;
				gm_AddTime((int) (f.v210 + 0x78), 0, 0, 0xa);
				*(int*) (f.v210 + 0xa8) = *(int*) (e->f00 + 2);
				/* the record was zeroed above, so this byte store still leaves 4 */
				f.v210[0xb4] = 4;
				*(int*) (f.v210 + 0xd4) = 1;
				*(int*) (f.v210 + 0xac) =
					0x64 - *(unsigned char*) (e->f00 + 0x12);
				cm_SendCopyEntityData((int) (f.v210 + 0x50));
			}
			e++;
		} while (--f.v1c != 0);
	} else if (f.vD0 == f.v6c && (signed char) gm_ClientModeFlags >= 0) {
		/* 0x5bd550: the slot list of the owning dialog is redrawn */
		d2_SetFormVisibility(f.v2c, 0);
		d2_ShowNewCartDialog(f.vCC);
		d2_SetFormVisibility(f.v2c, 1);
		if (f.v94 == 0) {
			goto l_5bd632;
		}
		if (*(unsigned char*) f.v94 == 5) {
			f.v38 = d2_SyncWareProduktionSlotGrid(f.v14, f.v18);
			d2_RefreshWorkshopInventoryGrids(f.v2c, 1, 1, f.v14);
		} else if (*(unsigned char*) f.v94 == 0x11) {
			f.v38 = d2_SyncProduktionSlotGrid(f.v14, f.v18);
			d2_DrawProduktionSlotGrid(f.v2c, 1, 1, f.v14, f.v18);
		}
	} else if (f.vD0 == f.v58 && (signed char) gm_ClientModeFlags >= 0) {
		/* 0x5bd5e7: every filled slot of the panel as a pointer list */
		i = 0;
		j = 0;
		e = f.v6D8;
		for (;;) {
			if (i >= 0x20) {
				break;
			}
			if (e->f00 != 0 && e->f08 != 0) {
				((int*) (f.v210 + 0x448))[i] = e->f00;
				i++;
			}
			e++;
			if (++j >= 0x10) {
				break;
			}
		}
		d2_SellObjectsDialog(i, (int) (f.v210 + 0x448));
	}	}


l_5bd62f:
l_5bd632:
	/* 0x5bd632: release the dialog selection and hand the panel back */
	i = f.v14;
	if (*(short*) (i + 0x27) != (short) gm_LocalPlayerSlot) {
		if (f.v54 != -1) {
			d2_SetSlotVisibility(f.v54, 0);
		}
		if (f.v6c != -1) {
			d2_SetSlotVisibility(f.v6c, 0);
		}
		if (f.v58 != -1) {
			d2_SetSlotVisibility(f.v58, 0);
		}
	}
	if (d2_GetControlValue(f.v78) != 0) {
		d2_SetSlotVisibility(g_00f8f120[d2_InventoryPanelWindowId].id, 1);
		d2_SetForm(f.v2c, 2);
		d2_SetSlotVisibility(g_00f8f120[d2_CurrentWindowId].id, 0);
	} else {
		d2_SetSlotVisibility(g_00f8f120[d2_InventoryPanelWindowId].id, 0);
		d2_SetForm(f.v2c, 2);
		d2_SetSlotVisibility(g_00f8f120[d2_CurrentWindowId].id, 1);
	}
	if (f.v3c != 0 && f.v38 != 0) {
		d2_CalcTradeCartCost(f.v14, f.v50, flags);
	} else {
		g_774698 = 0;
	}
	if (main_RunFrameLoop((void*) d2_RunTradeTransportPanel, 0x657c7) != 0) {
		goto l_5bb193;
	}
	d2_CloseInventoryPanel();
	ResetDisplayCounters();
	d2_DestroyForm(f.v2c);
	g_774698 = 0;
	if (f.v80 != 0) {
		d2_DestroyForm(f.v94);
		sv_SelectedBuilding = (char*) f.v7c;
	}
	d2_DispatchTutorialInput(0x23, (char*) 0, 1, 0);
	return 0;

}
