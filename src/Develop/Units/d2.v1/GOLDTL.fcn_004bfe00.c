#include "client_dialog_state.h"
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

void *__cdecl fcn_004be2a0(void *);
void *__cdecl fcn_004be1f0(void *);
int __cdecl rt_CountRoutePoints(void *);
void __cdecl rt_FreeRoutePoints(void *);
void __cdecl fcn_004be3d0(void *, void *, void *, void *);
void __cdecl fcn_004be530(void);
void __cdecl fcn_004bf1b0(int, void *);
void __cdecl fcn_004bf8e0(void *, void *);
void __cdecl fcn_004bfc10(void);
void __cdecl fcn_004bfca0(void *, void *);
int __cdecl d2_ClearRadioGroup(int);
void __cdecl d2_SelectRadioGroup(int, int);
void __cdecl fcn_00472640(int, int);
void __cdecl d2_SetForm(int, int);
void __cdecl cm_AppendCommandSyncField(int, int, int, char *);
void __cdecl cm_SendSetAttribute(void);
void __cdecl fcn_004c6e20(int, void *);
void __cdecl fcn_004c6ea0(int);
int __cdecl gm_SearchTable67(int);
void __cdecl fcn_00533bb0(int, int, void *, int, int, int, int);
int __cdecl main_RunFrameLoop(void *, int);
void __cdecl fcn_005b0230(void *);
int __cdecl fcn_005b0dd0(void *);
void __cdecl fcn_005b11f0(void *);
void __cdecl fcn_005b18c0(void *);

/* ADDRESS: GOLDTL 0x004bfe00 */
int __cdecl fcn_004bfe00(char *obj)
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
	g_772908 = (int) fcn_004be2a0(*(void **) (obj + 0x29));
	memset(town + 0xc, 0, 0x50);
	*(int *) (town + 0x10) = 0x400;
	*(int *) (town + 0x1c) = 0;
	*(int *) (town + 0x18) = 0x40000001;
	*(int *) (town + 0x14) = (int) 0xb07d7fb0;
	*(int *) (town + 0x4) = 0x10;
	*(int *) (town + 0x58) = 0x723;
	strcpy(town + 0x5c, *(char **) 0x14b5e84);
	fcn_005b0dd0(town);
	fcn_005b0230(town);
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
		head = (int) fcn_004be1f0(0);
		g_772908 = head;
		*(int *) (head + 4) = *(int *) (obj + 0x1c);
		*(int *) head = *(int *) (obj + 2);
		fcn_004be3d0(town, obj, (void *) head, (void *) head);
		d2_SelectRadioGroup(g_6816d8, 0);
		g_772904 = 0;
	} else {
		for (p = (char *) head; p != 0; p = *(char **) (p + 0x3c)) {
			fcn_004be3d0(town, obj, (void *) g_772908, p);
		}
	}
	d2_SetForm(*(int *) town, 2);
	fcn_00533bb0(d2_CurrentWindowId, 5, forms, 3,
		*(int *) 0x14b5e90, *(int *) 0x14b5e94, *(int *) 0x14b5e98);
	form0 = forms[0]; form1 = forms[1]; form2 = forms[2];
	while (main_RunFrameLoop((void *) 0x4bfe00, 0x657c7) != 0) {
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
		}
		g_6ab3dc = (tp_d2_SelectedControl == 0);
		if (g_100f1dc != -1) {
			if (d2_CurrentElementId == form2) {
				fcn_004bf8e0(obj, town);
			} else if (d2_CurrentElementId == form0) {
				if (g_6816d8 != -1) {
					v = *(int *) (g_6816d8 * 0x8c + 0x102cbc8);
					if (v != -1) {
						fcn_004bf1b0(*(int *) (0x10058a4 + v * 8), town);
					}
				}
			} else if (d2_CurrentElementId == form1 && g_772904 != 0) {
				p = (char *) fcn_004be1f0((void *) g_772908);
				*(int *) (p + 4) = *(int *) (g_772904 + 1);
				*(int *) p = *(int *) (obj + 2);
				fcn_004be3d0(town, obj, (void *) g_772908, p);
				d2_SelectRadioGroup(g_6816d8, g_772900 - 1);
				g_772904 = 0;
			}
		}
		fcn_005b11f0(town);
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
			fcn_00472640(form1, 1);
			fcn_00472640(form0, 0);
		} else {
			fcn_00472640(form1, 0);
			fcn_00472640(form0, 1);
		}
		fcn_004bfca0((void *) g_772908, town);
		fcn_004bfc10();
		fcn_004be530();
	}
	n = rt_CountRoutePoints((void *) g_772908);
	if (n >= 2) {
		fcn_004c6e20((int) obj, (void *) g_772908);
	} else {
		changed = 0; fcn_004c6ea0((int) obj);
		cm_BeginPacketFieldDelta(obj, *(int *) (obj + 2));
		cm_AppendCommandSyncField(1, 1, (int) (obj - g_aed32c) + 0x33, &changed);
		cm_SendSetAttribute();
	}
	fcn_005b18c0(town);
	if (g_6816d8 != -1) {
		d2_ClearRadioGroup(g_6816d8);
		g_6816d8 = -1;
	}
	rt_FreeRoutePoints((void *) g_772908);
	return 0;
}
