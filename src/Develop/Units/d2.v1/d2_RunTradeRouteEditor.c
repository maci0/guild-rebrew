#include "Develop/Units/d2.v1/client_dialog_state.h"
#include "client_packet_builder.h"
extern int g_772908;
extern int g_772900;
extern int d2_CurrentWindowId;
#include "Develop/DieGildeAddOn/game/game_data.h"
extern int g_6ab3dc;
extern int tp_d2_SelectedControl;
extern int g_100f1dc;
extern char* g_772904;
#include <string.h>

void *__cdecl rt_CloneRoutePoints(void *);
void *__cdecl rt_AllocRoutePoint(void *);
int __cdecl rt_CountRoutePoints(void *);
void __cdecl rt_FreeRoutePoints(void *);
void __cdecl d2_AddRoutePointMarker(void *, void *, void *, void *);
void __cdecl d2_PollRadioSlots(void);
void __cdecl d2_EditRoutePointDialog(int, void *);
void __cdecl d2_RunRoutingSettingsDialog(void *, void *);
void __cdecl d2_UpdateAllRoutePointImages(void);
void __cdecl d2_UpdateRouteMapControlStates(void *, void *);
int __cdecl d2_ClearRadioGroup(int);
void __cdecl d2_SelectRadioGroup(int, int);
void __cdecl d2_SetElementEnabled(int, int);
void __cdecl d2_SetForm(int, int);
void __cdecl cm_AppendCommandSyncField(int, int, int, char *);
void __cdecl cm_SendSetAttribute(void);
void __cdecl cm_SendSetObjektRoute(int, void *);
void __cdecl cm_SendClearObjektResources(int);
int __cdecl gm_SearchTable67(int);
void __cdecl d2_LayoutCenteredButtonRow(int, int, void *, int, int, int, int);
int __cdecl main_RunFrameLoop(void *, int);
void __cdecl d2_BuildCityScrollMap(void *);
int __cdecl d2_InitLandkarteDialog(void *);
void __cdecl d2_UpdateCityScrollMap(void *);
void __cdecl d2_DestroyMapDialog(void *);

/* ADDRESS: GOLDTL 0x004bfe00 */
int __cdecl d2_RunTradeRouteEditor(char *obj)
{
	char town[0x27ac]; int forms[3]; char changed;

	char *p;
	int *slot;
	int head;
	int i;
	int j;
	int n;
	int v; int form0, form1, form2;


	g_772904 = 0;
	if (obj == 0) {
		return 0;
	}
	g_772908 = (int) rt_CloneRoutePoints(*(void **) (obj + 0x29));
	memset(town + 0xc, 0, 0x50);
	*(int *) (town + 0x10) = 0x400;
	*(int *) (town + 0x1c) = 0;
	*(int *) (town + 0x18) = 0x40000001;
	*(int *) (town + 0x14) = (int) 0xb07d7fb0;
	*(int *) (town + 0x4) = 0x10;
	*(int *) (town + 0x58) = 0x723;
	strcpy(town + 0x5c, *(char **) 0x14b5e84);
	d2_InitLandkarteDialog(town);
	d2_BuildCityScrollMap(town);
	g_772900 = 0;
	for (i = 0; i < 8; i++) {
		*(int *) (0x10058a0 + i * 8) = -1;
		*(int *) (0x10058a4 + i * 8) = 0;
	}
	head = g_772908;
	if (head == 0) {
		changed = 1; cm_BeginPacketFieldDelta(obj, *(int *) (obj + 2));
		cm_AppendCommandSyncField(1, 1, (int) (obj - g_aed32c) + 0x33, &changed);
		cm_SendSetAttribute();
		head = (int) rt_AllocRoutePoint(0);
		g_772908 = head;
		*(int *) (head + 4) = *(int *) (obj + 0x1c);
		*(int *) head = *(int *) (obj + 2);
		d2_AddRoutePointMarker(town, obj, (void *) head, (void *) head);
		d2_SelectRadioGroup(g_6816d8, 0);
		g_772904 = 0;
	} else {
		for (p = (char *) head; p != 0; p = *(char **) (p + 0x3c)) {
			d2_AddRoutePointMarker(town, obj, (void *) g_772908, p);
		}
	}
	d2_SetForm(*(int *) town, 2);
	d2_LayoutCenteredButtonRow(d2_CurrentWindowId, 5, forms, 3,
		*(int *) 0x14b5e90, *(int *) 0x14b5e94, *(int *) 0x14b5e98);
	form0 = forms[0]; form1 = forms[1]; form2 = forms[2];
	while (main_RunFrameLoop((void *) 0x4bfe00, 0x657c7) != 0) {
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
		}
		g_6ab3dc = (tp_d2_SelectedControl == 0);
		if (g_100f1dc != -1) {
			if (d2_CurrentElementId == form2) {
				d2_RunRoutingSettingsDialog(obj, town);
			} else if (d2_CurrentElementId == form0) {
				if (g_6816d8 != -1) {
					v = *(int *) (g_6816d8 * 0x8c + 0x102cbc8);
					if (v != -1) {
						d2_EditRoutePointDialog(*(int *) (0x10058a4 + v * 8), town);
					}
				}
			} else if (d2_CurrentElementId == form1 && g_772904 != 0) {
				p = (char *) rt_AllocRoutePoint((void *) g_772908);
				*(int *) (p + 4) = *(int *) (g_772904 + 1);
				*(int *) p = *(int *) (obj + 2);
				d2_AddRoutePointMarker(town, obj, (void *) g_772908, p);
				d2_SelectRadioGroup(g_6816d8, g_772900 - 1);
				g_772904 = 0;
			}
		}
		d2_UpdateCityScrollMap(town);
		if (g_14ce8d8 != 0 && d2_CurrentElementId != -1 &&
		    *(int *) (town + 0x27a4) > 0) {
			n = *(int *) (town + 0x27a4);
			for (i = 0; i < n; i++) {
				slot = (int *) (town + 0xdc + i * 0x18);
				if (slot[0] == d2_CurrentElementId) {
					g_772904 = (char *) slot[1];
					for (j = 0; j < 8; j++) {
						v = *(int *) (0x10058a4 + j * 8);
						if (v != 0 && (v = *(int *) (v + 4)) != -1 &&
						    gm_SearchTable67(v) == (int) g_772904) {
							d2_SelectRadioGroup(g_6816d8, j);
							g_772904 = 0;
						}
					}
					break;
				}
			}
		}
		if (g_772904 != 0) {
			d2_SetElementEnabled(form1, 1);
			d2_SetElementEnabled(form0, 0);
		} else {
			d2_SetElementEnabled(form1, 0);
			d2_SetElementEnabled(form0, 1);
		}
		d2_UpdateRouteMapControlStates((void *) g_772908, town);
		d2_UpdateAllRoutePointImages();
		d2_PollRadioSlots();
	}
	n = rt_CountRoutePoints((void *) g_772908);
	if (n >= 2) {
		cm_SendSetObjektRoute((int) obj, (void *) g_772908);
	} else {
		changed = 0; cm_SendClearObjektResources((int) obj);
		cm_BeginPacketFieldDelta(obj, *(int *) (obj + 2));
		cm_AppendCommandSyncField(1, 1, (int) (obj - g_aed32c) + 0x33, &changed);
		cm_SendSetAttribute();
	}
	d2_DestroyMapDialog(town);
	if (g_6816d8 != -1) {
		d2_ClearRadioGroup(g_6816d8);
		g_6816d8 = -1;
	}
	rt_FreeRoutePoints((void *) g_772908);
	return 0;
}
