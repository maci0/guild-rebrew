

#include <string.h>

// SIZE 0x2f4
struct gadget {
	char pad0[0x5c];
	int visible;
	char pad60[0x6c];
	char label[0x100];
	int font;
	int mode;
	char pad1d4[0x120];
};

#include "Develop/Units/d2.v1/d2_gui.h"
extern char* g_14a5ad8[];
extern int d2_CurrentWindowId;
extern char g_6a3f8c[];
extern int g_100f1dc;
#include "Develop/DieGildeAddOn/game/game_data.h"
extern char g_7e23e3;
#include "client_dialog_state.h"

int __cdecl fcn_00470820(int, int, char*);
void __cdecl d2_CenterDialogWindows(int);
void __cdecl d2_SetForm(int, int);
int __cdecl io_AppendText(int, ...);
int __cdecl d2_CreateRadioGroup(int);
int __cdecl fcn_0046f740(int, int, int, int);
void __cdecl fcn_00469470(int, int);
int __cdecl fcn_005373e0(int (__cdecl*)(int), int);
void __cdecl d2_UpdateRadioGroup(int);
unsigned char __cdecl fcn_00507400(int, int);
void __cdecl d2_ClearRadioGroup(int);
void __cdecl fcn_00471e30(int);

int __cdecl d2_ShowChooseProfessionDialog(int flags)
{
	int list;
	int result;
	int h;
	int types[11];
	int ids[11];
	int i;
	int t;
	int id;

	result = 0;
	types[0] = 1;
	types[1] = 2;
	types[2] = 3;
	types[3] = 4;
	types[4] = 5;
	types[5] = 6;
	types[6] = 7;
	types[7] = 0xb;
	types[8] = 0xd;
	types[9] = 0xe;
	types[10] = 0xf;
	h = fcn_00470820(0, 0, g_6a3f8c);
	d2_CenterDialogWindows(h);
	d2_SetForm(h, 0);
	io_AppendText(0x1afa);
	list = d2_CreateRadioGroup(0);
	for (i = 0; i < 11; i++) {
		t = types[i];
		id = fcn_0046f740((i % 3) * 0x60 + 0x64, (i / 3 * 5 + 5) * 0x10, t + 0x5a1, d2_CurrentWindowId);
		ids[i] = id;
		(*(int*)&((D2_CONTROL_TL*)g_1015ea0)[id].value_05c) = 1;
		(*(int*)&((D2_CONTROL_TL*)g_1015ea0)[id].flags_1d0) = 3;
		strcpy(((char*)&((D2_CONTROL_TL*)g_1015ea0)[id] + 0xcc), g_14a5ad8[t]);
		(*(int*)&((D2_CONTROL_TL*)g_1015ea0)[id].value_1cc) = 0x56;
		fcn_00469470(list, id);
	}
	g_100f1dc = -1;
	while (fcn_005373e0(d2_ShowChooseProfessionDialog, flags) != 0) {
		d2_UpdateRadioGroup(list);
		if (g_100f1dc != -1) {
			for (i = 0; i < 11; i++) {
				if (d2_CurrentElementId == ids[i]) {
					(*(unsigned char*)&g_7e23e3) = fcn_00507400(types[i], 1);
					g_774654 = 1;
					result = 1;
					break;
				}
			}
		}
	}
	d2_ClearRadioGroup(list);
	fcn_00471e30(h);
	return result;
}
