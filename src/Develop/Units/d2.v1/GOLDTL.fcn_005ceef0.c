#include <string.h>

extern int g_775348;
extern int d2_CurrentWindowId;
extern char g_773d75;
extern int g_100f1dc;
#include "client_dialog_state.h"
#include "Develop/DieGildeAddOn/game/game_data.h"
#include "Develop/Units/d2.v1/d2_gui.h"
extern int g_aed32c;

extern int g_14a90a0;
extern int g_14b5874;

typedef struct Ce800Config {
	unsigned int flags;
	int pad4;
	int pad8;
	int padc;
} Ce800Config;

int* __cdecl hp_FindProdSetting(int a);
int* __cdecl hp_AddProdSetting(int a);
void __cdecl hp_SyncProdSetting(int a);
void __cdecl gm_AdjustProductionShare(int a, unsigned int b, unsigned int c);
void __cdecl hp_SetProdSettingScale(int a, float v);
int __cdecl d2_LoadForm(int a, int b, char* name);
void __cdecl d2_SetForm(int a, int b);
void __cdecl d2_InitWindowBounds(int a);
void __cdecl d2_CenterDialogWindows(int a);
void __cdecl d2_SetOverlayAnimation(int a, int b);
int __cdecl gm_AmountToUnits(int a, unsigned char k);
int __cdecl fcn_0050b750(int a, unsigned char k);
void __cdecl d2_PopulateProdSettingBars(int dlg, int* list, int* bars, int* icons);
void __cdecl d2_InitProdSettingControls(int id, int* out, int* value, int* slots,
	unsigned char* type, int text, Ce800Config cfg, int* handle, int source);
void __cdecl d2_CreateButtonRow(int a, int b, int* c, int d, int e, int f);
int __cdecl d2_GetControlValue(int a);
void __cdecl d2_CreateGuiWindow(int a, int b, int c, int d);
void __cdecl d2_SetElementEnabled(int a, int b);
void __cdecl cm_BeginPacketFieldDelta(void* p, unsigned int value);
void __cdecl cm_AppendPacketFieldDelta(int a, int b, int off, unsigned int* value);
void __cdecl cm_AppendPacketFieldValue(int a, int b, int off, void* value);
void __cdecl cm_RequestChangeAttribute(void);
int __cdecl main_RunFrameLoop(void* fn, int msg);
void __cdecl d2_DestroyForm(int a);

/* ADDRESS: GOLDTL 0x005ceef0 */
void __cdecl d2_RunProdSettingsDialog(int building, unsigned short* actor)
{
	int v12[7];
	int v13;
	int v14[4];
	int v15;
	unsigned int v16;
	int v17[7];
	int v18[2];
	Ce800Config cfg;
	Ce800Config* cfgp;
	char v2;
	int v20;
	char* v21;
	int v22;
	int v23;
	unsigned int v24;
	unsigned char* v26;
	int* v27;
	unsigned int v28;
	int v29;
	int v30;
	unsigned int v5;
	int v8;

	v20 = 1;
	v29 = -1;
	v30 = -1;
	v13 = -1;
	v27 = hp_FindProdSetting(*(unsigned int*) ((char*) building + 1));
	memset(v12, -1, sizeof(v12));
	if (!v27) {
		v27 = hp_AddProdSetting(building);
	}
	if (!v27) {
		g_775348 = 0;
		v20 = 0;
	} else {
		hp_SyncProdSetting(building);
	}
	v28 = d2_LoadForm(0, 0, (char*) 0x6aca84);
	d2_SetForm(v28, 0);
	d2_InitWindowBounds(d2_CurrentWindowId);
	d2_CenterDialogWindows(v28);
	d2_SetOverlayAnimation(0, 0);
	v15 = gm_AmountToUnits(*(unsigned int*) ((char*) building + 0x39), g_773d75);
	cfgp = (Ce800Config*) &actor[0xda];
	cfg = *cfgp;
	if (!g_775348) {
		d2_InitProdSettingControls(v28, &v16, &v15, v14, (unsigned char*) building, *actor,
			*cfgp, &v13, (int) v27);
	} else {
		d2_PopulateProdSettingBars(v28, v27, v12, v17);
	}
	if (v20) {
		d2_SetForm(v28, 3);
		d2_CreateButtonRow(d2_CurrentWindowId, 0, &v18[0], 2, g_14a90a0, g_14b5874);
		v29 = v18[0];
		v30 = v18[1];
	}
	g_100f1dc = -1;
	for (;;) {
		if (g_14ce8e0) {
			g_774654 = 1;
		} else if (g_14ce8d0) {
			if (g_775348 == 1) {
				v23 = 0;
				do {
					if (d2_CurrentElementId == v12[v23]) {
						if (v23 < 7 && v12[v23] != -1) {
							g_100f1dc = -1;
							v5 = d2_GetControlValue(v12[v23]);
							gm_AdjustProductionShare(building,
								*(unsigned int*) ((char*) v27 + v23 * 8),
								v5);
							v23 = 0;
							v26 = (unsigned char*) v27 + 4;
							do {
								if (v12[v23] != -1) {
									d2_CreateGuiWindow(v12[v23], 0, 100,
										*v26);
								}
								v23 += 1;
								v26 += 8;
							} while (v23 < 7);
						}
						break;
					}
					v23 += 1;
				} while (v23 < 7);
			} else if (!g_775348 && v13 != -1 && d2_CurrentElementId == v13) {
				v18[0] = d2_GetControlValue(v13);
				hp_SetProdSettingScale(building, (float) v18[0] * 0.01f);
			}
		}
		if (g_14ce8d8 && d2_CurrentElementId != -1) {
			v21 = (char*) v27 + 5;
			v8 = 0;
			do {
				v23 = *(int*) ((char*) v17 + v8);
				if (d2_CurrentElementId == v23) {
					v2 = *v21;
					*v21 = (v2 == 0);
					*(unsigned int*) &((D2_CONTROL_TL*) g_1015ea0)[v23].value_038
						= (*v21 == 0);
					d2_SetElementEnabled(*(unsigned int*) ((char*) v12 + v8),
						*v21 == 0);
				}
				v8 += 4;
				v21 += 8;
			} while (v8 < 0x1c);
		}
		v23 = d2_CurrentElementId;
		if (g_100f1dc != -1) {
			if (g_775348 == 1) {
				if (v23 == v29) {
					d2_InitProdSettingControls(v28, &v16, &v15, v14,
						(unsigned char*) building, *actor, cfg, &v13, (int) v27);
					g_775348 = 0;
					d2_CurrentElementId = -1;
				} else {
					v22 = 0;
					do {
						if (v23 == v12[v22]) {
							if (v22 < 7) {
								v5 = d2_GetControlValue(v12[v22]);
								gm_AdjustProductionShare(building,
									*(unsigned int*) ((char*) v27 + v22 * 8), v5);
								v23 = 0;
								v26 = (unsigned char*) v27 + 4;
								do {
									if (v12[v23] != -1) {
										d2_CreateGuiWindow(v12[v23], 0, 100,
											*v26);
									}
									v23 += 1;
									v26 += 8;
								} while (v23 < 7);
							}
							break;
						}
						v22 += 1;
					} while (v22 < 7);
				}
			} else if (!g_775348) {
				v15 = d2_GetControlValue(v16);
				if (d2_CurrentElementId == v30) {
					d2_PopulateProdSettingBars(v28, v27, v12, v17);
					g_775348 = 1;
					d2_CurrentElementId = -1;
				} else {
					v24 = 0;
					v23 = d2_CurrentElementId;
					do {
						if (v23 == -1) {
							break;
						}
						v22 = v14[v24];
						if (v23 == v22) {
							cfg = *(Ce800Config*) &actor[0xda];
							if (d2_GetControlValue(v22)) {
								switch (v24) {
								case 0:
									cfg.flags |= 1;
									break;
								case 1:
									cfg.flags |= 2;
									break;
								case 2:
									cfg.flags |= 4;
									break;
								case 3:
									cfg.flags |= 8;
									break;
								}
							} else {
								switch (v24) {
								case 0:
									cfg.flags &= ~1;
									break;
								case 1:
									cfg.flags &= ~2;
									break;
								case 2:
									cfg.flags &= ~4;
									break;
								case 3:
									cfg.flags &= ~8;
									break;
								}
							}
							cm_BeginPacketFieldDelta(actor, *(unsigned int*) ((char*) actor + 4));
							cm_AppendPacketFieldDelta(4, 1,
								(int) ((char*) actor + 0x1b4 - g_aed32c),
								&cfg.flags);
							cm_RequestChangeAttribute();
							cm_BeginPacketFieldDelta(building, *(unsigned int*) ((char*) building + 1));
							cm_AppendPacketFieldDelta(4, 1,
								(int) ((char*) building + 0x99 - g_aed32c),
								&cfg.flags);
							cm_RequestChangeAttribute();
							d2_InitProdSettingControls(v28, &v16, &v15, v14,
								(unsigned char*) building, *actor, cfg, &v13, (int) v27);
							v23 = -1;
							d2_CurrentElementId = -1;
						}
						v24 += 1;
					} while ((int) v24 < 4);
				}
			}
		}
		if (!main_RunFrameLoop((void*) d2_RunProdSettingsDialog, 0x677c7)) {
			if (!g_775348) {
				v15 = d2_GetControlValue(v16);
			}
			v15 = fcn_0050b750(v15, g_773d75);
			cm_BeginPacketFieldDelta(building, *(unsigned int*) ((char*) building + 1));
			cm_AppendPacketFieldDelta(4, 1,
				(int) ((char*) building + 0x39 - g_aed32c), &v15);
			cm_RequestChangeAttribute();
			v18[0] = v15 - *(int*) ((char*) building + 0x39);
			cm_BeginPacketFieldDelta(actor, *(unsigned int*) ((char*) actor + 4));
			cm_AppendPacketFieldValue(4, 1,
				(int) ((char*) actor + 0x1b8 - g_aed32c), &v18[0]);
			cm_RequestChangeAttribute();
			d2_DestroyForm(v28);
			return;
		}
	}
}
