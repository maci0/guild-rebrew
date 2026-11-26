#include "client_dialog_state.h"
extern int g_14ce8e0, g_100f1dc, d2_CurrentElementId;
extern char g_14cf950;
extern int g_6a81dc[5];
#include "Develop/Units/d2.v1/d2_gui.h"
char* __cdecl fcn_00470820(int, int, char*);
void __cdecl d2_CenterDialogWindows(char*);
void __cdecl d2_DestroyForm(char*);
int __cdecl d2_GetWindowListItem(char*, int, char*);
void __cdecl fcn_00472640(int, int);
void __cdecl d2_SetForm(char*, int);
char* __cdecl io_AppendText(char*, int);
int __cdecl main_RunFrameLoop(char*, int);
typedef struct { int i[0x2f4 / 4]; } Row_5845e0;

/* ADDRESS: GOLDTL 0x005845e0 */
int __cdecl d2_ChooseTutorial(void)
{
	char* menu;
	char* item;
	int ids[5];
	int i;
	int k;
	int n;
	int index;
	int result;
	int result2;
	int flag;

	i = 0; flag = 0;
	menu = fcn_00470820(0, 0, (char*) 0x6a9298);
	d2_CenterDialogWindows(menu);
	d2_SetForm(menu, 1);
	io_AppendText((char*) 0x6a2f5c, 0x3f1a);
	d2_SetForm(menu, 2);
	for (; i < 5; i++) {
		item = io_AppendText((char*) 0x681140, 0x3f1b + i);
		item = d2_GetWindowListItem(menu, 2, item);
		ids[i] = (int) item;
		index = (int) item;
		(*(int*)&((D2_CONTROL_TL*)g_1015ea0)[index].value_058) = 1;
		(*(int*)&((D2_CONTROL_TL*)g_1015ea0)[index].value_038) = g_6a81dc[i];
		(*(int*)&((D2_CONTROL_TL*)g_1015ea0)[index].flags_1d0) &= -3;
	}
	item = io_AppendText((char*) 0x681140, 0x3f20);
	result = (int) d2_GetWindowListItem(menu, 2, item);
	item = io_AppendText((char*) 0x681140, 0x3f21);
	result2 = (int) d2_GetWindowListItem(menu, 2, item);
	d2_SetForm(menu, 2);

	if (main_RunFrameLoop((char*) 0x5845e0, 0x86) != 0) {
		do {
			n = k = 0;
			for (; k < 5; k++) {
				index = ids[k];
				index = index * 0x40 - index;
				index = index * 0xc;
				if (*(int*)&((D2_CONTROL_TL*)(g_1015ea0 + index))->value_038 != 0) {
					fcn_00472640((char*) result, 1);
					break;
				}
				n++;
			}
			if (n == 5) {
				fcn_00472640((char*) result, 0);
			}
			if (g_14ce8e0 != 0 || g_14cf950 == 1 || g_100f1dc == 1) {
				g_774654 = 1;
			}
			if (g_100f1dc != -1) {
				if (d2_CurrentElementId == result2) {
					g_774654 = 1;
				} else if (d2_CurrentElementId == result) {
					g_774654 = 1;
					n = 0;
					for (k = 0; k < 5; k++) {
						index = ids[k];
						index = index * 0x40 - index;
						index = index * 0xc;
						if (*(int*)&((D2_CONTROL_TL*)(g_1015ea0 + index))->value_038 != 0) {
							n++;
							g_6a81dc[k] = 1;
						} else {
							g_6a81dc[k] = 0;
						}
					}
					if (n != 0) {
						flag = 1;
					}
				}
			}
		} while (main_RunFrameLoop((char*) 0x5845e0, 0x86) != 0);
	}
	d2_DestroyForm(menu);
	return flag;
}
