#include <string.h>

extern int d2_CurrentWindowId;
extern char* g_77255c;
extern char* g_1015ea0;
extern int g_100f1dc;
#include "client_dialog_state.h"
#include "Develop/DieGildeAddOn/game/game_data.h"
extern char g_14cf950;

extern char s_6a3bd4[];
extern char s_6a3bcc[];
extern char s_6a3bc4[];

int __cdecl fcn_00470820(int, int, char*);
void __cdecl d2_CenterDialogWindows(int);
void __cdecl fcn_00471e30(int);
int __cdecl d2_GetWindowListItem(int, int, int);
void __cdecl fcn_00472640(int, int);
int __cdecl d2_SetForm(int, int);
int __cdecl d2_AddElementToWindow(int, int, int, int);
int __cdecl io_AppendText(int, ...);
void __cdecl fcn_005340f0(int);
void __cdecl fcn_00534160(int, int, int, int);
int __cdecl main_RunFrameLoop(void*, int);
#include "Develop/Units/d2.v1/d2_gui.h"
/* ADDRESS: GOLDTL 0x0053b1b0 */
int __cdecl fcn_0053b1b0(void)
{
	int v_len;
	int v_id;
	int v_first;
	int dlg;
	int v_ret;
	int id;
	int st[11];
	int ids[14];
	int i;
	int j;
	int y;

	v_ret = 0;
	memset((void*) 0x7e1fd8, 0, 24);
	v_first = 1;
	v_len = 0x7e;
	memcpy(st, (void*) 0x7e1fc0, 44);
	v_id = -1;
	for (i = 4; i < 6; i++) {
		if (i < 4)
			st[6 + st[i]] = (int) (st[6 + st[i]] + 21.0f);
		else
			st[6 + st[i]] = (int) (st[6 + st[i]] + 63.0);
	}
	memcpy((void*) 0x7e1fc0, st, 44);
	dlg = fcn_00470820(0, 0, s_6a3bd4);
	d2_CenterDialogWindows(dlg);
	d2_SetForm(dlg, 0);
	fcn_005340f0(d2_CurrentWindowId);
	d2_SetForm(dlg, 2);
	io_AppendText(0x1ae2);
	if (main_RunFrameLoop((void*) fcn_0053b1b0, 0x12d6) != 0) {
		do {
			if (g_14ce8e0 != 0)
				g_774654 = 1;
			if (v_first != 0) {
				d2_SetForm(dlg, 1);
				io_AppendText((int) s_6a3bcc);
				i = 0;
				y = 0x1c;
				for (; i < 5; i++, y += 0x25) {
					io_AppendText((int) s_6a3bc4, i + 0x16b7);
					fcn_00534160(0xd2, y, st[6 + i], 0x4d9);
					id = d2_AddElementToWindow(*(int*) (g_77255c + 0xc) - 0x2c, y, 0x519, d2_CurrentWindowId);
					ids[2 * i] = id;
					((D2_CONTROL_TL*) (g_1015ea0))[id].value_05c = 1;
					((D2_CONTROL_TL*) (g_1015ea0))[id].flags_1d0 = 3;
					id = d2_AddElementToWindow(*(int*) (g_77255c + 0xc) - 0x18, y, 0x51a, d2_CurrentWindowId);
					ids[2 * i + 1] = id;
					((D2_CONTROL_TL*) (g_1015ea0))[id].value_05c = 1;
					((D2_CONTROL_TL*) (g_1015ea0))[id].flags_1d0 = 3;
				}
				io_AppendText(0x1ae3);
				fcn_00534160(0xd2, 0xec, v_len, 0x4d9);
				v_id = d2_GetWindowListItem(dlg, 1, io_AppendText(0x1ae4));
				for (i = 0; i < 5; i++) {
					if (st[6 + i] > ((int*)0x7e1fd8)[i]) {
						id = ids[2 * i];
						((D2_CONTROL_TL*) (g_1015ea0))[id].disabled = 0;
						((D2_CONTROL_TL*) (g_1015ea0))[id].value_060 = 0;
					} else {
						id = ids[2 * i];
						((D2_CONTROL_TL*) (g_1015ea0))[id].disabled = 1;
						((D2_CONTROL_TL*) (g_1015ea0))[id].value_060 = 1;
					}
					if (v_len > 0 && st[6 + i] < 126.0f) {
						id = ids[2 * i + 1];
						((D2_CONTROL_TL*) (g_1015ea0))[id].disabled = 0;
						((D2_CONTROL_TL*) (g_1015ea0))[id].value_060 = 0;
					} else {
						id = ids[2 * i + 1];
						((D2_CONTROL_TL*) (g_1015ea0))[id].disabled = 1;
						((D2_CONTROL_TL*) (g_1015ea0))[id].value_060 = 1;
					}
				}
				v_first = 0;
			}
			if (v_len != 0)
				fcn_00472640(v_id, 0);
			else
				fcn_00472640(v_id, 1);
			if (g_100f1dc != -1) {
				if (g_100f1dc == 2 || g_14cf950 == 0x1c) {
					v_ret = 1;
					for (i = 0; i < 5; i++)
						((char*) 0x7e2430)[i] = (char) st[6 + i];
					switch (st[4]) {
					case 0:
						*(char*) 0x7e23e0 = 0x1c;
						break;
					case 1:
						*(char*) 0x7e23e0 = 0x31;
						break;
					case 2:
						*(char*) 0x7e23e0 = 4;
						break;
					case 3:
						*(char*) 0x7e23e0 = 0x37;
						break;
					case 4:
						*(char*) 0x7e23e0 = 0x10;
						break;
					}
					switch (st[5]) {
					case 0:
						*(char*) 0x7e23e1 = 0x1c;
						break;
					case 1:
						*(char*) 0x7e23e1 = 0x25;
						break;
					case 2:
						*(char*) 0x7e23e1 = 4;
						break;
					case 3:
						*(char*) 0x7e23e1 = 0;
						break;
					case 4:
						*(char*) 0x7e23e1 = 0x49;
						break;
					}
					memcpy((void*) 0x7e1fc0, st, 44);
					g_774654 = 1;
				} else if (g_100f1dc == 1) {
					g_774654 = 1;
					continue;
				}
				if (g_100f1dc == 0x519 || g_100f1dc == 0x51a) {
					v_first = 1;
					for (j = 0; j < 0xc; j++) {
						if (d2_CurrentElementId != ids[j])
							continue;
						if (j % 2 != 0) {
							if (v_len > 0) {
								st[6 + j / 2] = (int) (st[6 + j / 2] + 21.0f);
								v_len = (int) (v_len - 21.0f);
							}
						} else if (st[6 + j / 2] > ((int*) 0x7e1fd8)[j / 2]) {
							st[6 + j / 2] = (int) (st[6 + j / 2] - 21.0f);
							v_len = (int) (v_len + 21.0f);
						}
					}
				}
			}
		} while (main_RunFrameLoop((void*) fcn_0053b1b0, 0x12d6) != 0);
	}
	fcn_00471e30(dlg);
	return v_ret;
}
