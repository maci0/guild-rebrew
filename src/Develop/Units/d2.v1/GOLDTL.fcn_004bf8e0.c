#include "g_10058a0.h"

// SIZE 0x40
typedef struct Node_4bf8e0 {
	int f0;
	int f4;
	char pad8[0x38];
} Node_4bf8e0;

extern char s_681730[];
extern int d2_CurrentWindowId;
extern int g_14b5e9c;
extern int g_14b5eac;
extern int g_14b5ed8[];
extern int g_14b5eb4;
extern int g_14b5eb8;
extern int g_14b5ebc;
extern int g_14b5ec0;
extern int g_14b5ec4;
#include "Develop/DieGildeAddOn/game/game_data.h"
extern int g_100f1dc;
#include "client_dialog_state.h"
extern Node_4bf8e0* g_772908;
extern D2_RADIO_SLOT g_10058a0[8];
extern int g_772900;
#include "client_packet_builder.h"

int __cdecl fcn_00470820(int, int, char*);
void __cdecl d2_CenterDialogWindows(int);
void __cdecl d2_SetForm(int, int);
int __cdecl io_AppendText(int, ...);
int __cdecl d2_GetWindowListItem(int, int, int);
void __cdecl fcn_00533a60(int, int, int*, int, ...);
void __cdecl fcn_0046f9b0(int, int);
#include "Develop/Units/d2.v1/d2_gui.h"
void __cdecl fcn_00468cd0(int, int);
void __cdecl fcn_00468bb0(int, int, int, int, int, int, int);
int __cdecl main_RunFrameLoop(void*, int);
#include "Develop/DieGildeAddOn/game/spiel.h"
void __cdecl fcn_004bfc70(int);
void __cdecl fcn_004be360(void);
Node_4bf8e0* __cdecl fcn_004be1f0(Node_4bf8e0*);
void __cdecl d2_AddRoutePointMarker(int, char*, Node_4bf8e0*, Node_4bf8e0*);
void __cdecl d2_SelectRadioGroup(int, int);

int __cdecl cm_AppendCommandSyncField(unsigned char, unsigned char, short, void*);
void __cdecl cm_SendSetAttribute(void);
int __cdecl d2_GetControlValue(int);
void __cdecl d2_DestroyForm(int);
void __cdecl io_ClearInputState(void);

/* ADDRESS: GOLDTL 0x004bf8e0 */
void __cdecl fcn_004bf8e0(char* p, int arg)
{
	int ids[10];
	int ok;
	int clear;
	int flip;
	int dlg;
	int list;
	int i;

	dlg = fcn_00470820(0, 0, s_681730);
	d2_CenterDialogWindows(dlg);
	d2_SetForm(dlg, 1);
	io_AppendText(0x42e2);
	list = d2_GetWindowListItem(dlg, 2, 0);
	d2_SetForm(dlg, 4);
	io_AppendText(*(unsigned char*) (p + 0x33) + 0x42ec);
	d2_SetForm(dlg, 3);
	fcn_00533a60(d2_CurrentWindowId, 0, ids, 3, g_14b5e9c, g_14b5eac, g_14b5ed8[*(unsigned char*) (p + 0x33)]);
	ok = ids[0];
	clear = ids[1];
	flip = ids[2];
	fcn_0046f9b0(flip, g_14b5ed8[*(unsigned char*) (p + 0x33)]);
	d2_SetElementValue(list, 0, 4, *(unsigned char*) (p + 0x31));
	fcn_00468cd0(list, 0x82);
	fcn_00468bb0(list, 5, g_14b5eb4, g_14b5eb8, g_14b5ebc, g_14b5ec0, g_14b5ec4);
	while (main_RunFrameLoop(fcn_004bf8e0, 0x657c7) != 0) {
		if (g_14ce8e0 != 0 || (g_100f1dc != -1 && d2_CurrentElementId == ok)) {
			g_774654 = 1;
		}
		d2_SetForm(dlg, 4);
		io_AppendText(*(unsigned char*) (p + 0x33) + 0x42ec);
		fcn_0046f9b0(flip, g_14b5ed8[*(unsigned char*) (p + 0x33)]);
		if (g_100f1dc != -1 && d2_CurrentElementId == clear) {
			if (g_772908 != 0) {
				rt_FreeRoutePoints((char*) g_772908);
			}
			for (i = 0; i < 8; i++) {
				if (g_10058a0[i].id != -1) {
					fcn_004bfc70(i);
				}
			}
			g_772900 = 0;
			fcn_004be360();
			g_772908 = fcn_004be1f0(0);
			g_772908->f4 = *(int*) (p + 0x1c);
			g_772908->f0 = *(int*) (p + 2);
			d2_AddRoutePointMarker(arg, p, g_772908, g_772908);
			d2_SelectRadioGroup(g_6816d8, 0);
			g_774654 = 2;
		}
		if (g_100f1dc != -1 && d2_CurrentElementId == flip) {
			unsigned char b;

			b = *(unsigned char*) (p + 0x33) == 0;
			cm_BeginPacketFieldDelta(p, *(int*) (p + 2));
			cm_AppendCommandSyncField(1, 1, (short) (p + 0x33 - g_aed32c), &b);
			cm_SendSetAttribute();
		}
	}
	if (d2_GetControlValue(list) != *(unsigned char*) (p + 0x31)) {
		unsigned char b;

		b = d2_GetControlValue(list);
		cm_BeginPacketFieldDelta(p, *(int*) (p + 2));
		cm_AppendCommandSyncField(1, 1, (short) (p + 0x31 - g_aed32c), &b);
		cm_SendSetAttribute();
	}
	d2_DestroyForm(dlg);
	io_ClearInputState();
}
