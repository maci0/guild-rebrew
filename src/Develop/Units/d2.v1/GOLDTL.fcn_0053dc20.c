extern int __cdecl fcn_00470820(int a, int b, const char *name);
extern void __cdecl d2_CenterDialogWindows(int obj);
extern void __cdecl d2_SetForm(int obj, int a);
extern int __cdecl fcn_0051e070(void);
extern int __cdecl io_AppendText(int id, ...);
extern int __cdecl d2_GetWindowListItem(int obj, int a, int b);
extern int __cdecl d2_CreateRadioGroup(int a, int b, int c, int d);
extern void __cdecl d2_SelectRadioGroup(int obj, int a);
extern int __cdecl main_RunFrameLoop(int proc, int a);
extern void __cdecl d2_ClearRadioGroup(int obj);
extern void __cdecl d2_DestroyForm(int obj);
extern void __cdecl d2_UpdateRadioGroup(int obj);
extern void __cdecl fcn_004b20d0(int a);
extern void __cdecl d2_SetFormVisibility(int obj, int a);
extern int __cdecl fcn_004b41b0(void);
extern int __cdecl fcn_004e4470(const char *name);
extern void __cdecl cut_WaitForScript(int a);
extern int __cdecl gm_FindHeadIconIndex(const char *name);
extern int __cdecl d2_RunChoosePlayerDialog(int a, int b);
extern int __cdecl fcn_0053e8a0(int a);
extern int __cdecl d2_ShowChooseProfessionDialog(int a);
extern unsigned int *__cdecl gm_GetStatRecord(char *buf, unsigned char a);
extern void __cdecl d3_SelectSceneContext(int a, int b);
extern int __cdecl d2_OpenMessageBox(int a, int b);
extern int __cdecl d2_RunParentProfessionSelection(int a);
extern char g_14cf950;
extern int g_100f1dc;
#include "Develop/DieGildeAddOn/game/game_data.h"
extern int g_774654;
extern int g_7e242c;
extern int g_7e2468;
extern int main_LoopFlags;

/* ADDRESS: GOLDTL 0x0053dc20 */
int __cdecl fcn_0053dc20(void)
{
	char buf[8];
	int retry;
	int again;
	int firstOption;
	int lastOption;
	int v12;
	int v13;
	int mode;
	int v2;
	int r;
	int obj;
	int v4;
	int dlg;
	unsigned int *p;

	retry = 0;
	again = 0;
	v12 = -1;
	v13 = 0xff;
	v2 = 0;
	obj = fcn_00470820(0, 0, (const char *) 0x68116c);
	d2_CenterDialogWindows(obj);
	d2_SetForm(obj, 0);
	if (fcn_0051e070()) {
		v4 = io_AppendText(0x1ac0, 0x1ac2, 0x1ac4, 0x1ac2, 0x1ac4, 1);
		firstOption = d2_GetWindowListItem(obj, 0, v4);
		lastOption = d2_GetWindowListItem(obj, 0, v4 + 1);
		dlg = d2_CreateRadioGroup(3, firstOption, lastOption, d2_GetWindowListItem(obj, 0, v4 + 2));
	} else {
		v4 = io_AppendText(0x1ac0, 0x1ac2, 0x1ac3, 0x1ac4, 0x1ac2, 0x1ac3,
		    0x1ac4, 1);
		firstOption = d2_GetWindowListItem(obj, 0, v4);
		v12 = d2_GetWindowListItem(obj, 0, v4 + 1);
		lastOption = d2_GetWindowListItem(obj, 0, v4 + 2);
		dlg = d2_CreateRadioGroup(4, firstOption, v12, lastOption, d2_GetWindowListItem(obj, 0, v4 + 3));
	}
	if (*(int *) 0x7766fc == 0) {
		mode = 2;
	} else if (*(int *) 0x7766fc == 1) {
		mode = 0;
	} else if (*(int *) 0x7766fc == 2) {
		mode = 1;
	} else {
		goto label_53dd68;
	}
	d2_SelectRadioGroup(dlg, mode);
label_53dd68:
	r = main_RunFrameLoop(0x53dc20, 0xc6);
	for (;;) {
		if (!r) {
			d2_ClearRadioGroup(dlg);
			d2_DestroyForm(obj);
			if (again) {
				*(int *) 0x7747b0 |= 8;
				return again;
			}
			*(int *) 0x7747b0 = 0;
			return 0;
		}
		d2_UpdateRadioGroup(dlg);
		if (g_14ce8e0 || g_14cf950 == 1) {
			g_774654 = 1;
		}
		if (g_100f1dc == 2 || g_14cf950 == 0x1c || retry) {
			if (v2) {
				goto label_53de5c;
			}
			if (d2_CurrentElementId != firstOption) {
				if (d2_CurrentElementId == v12) {
					mode = 2;
					goto label_53de0b;
				}
				if (d2_CurrentElementId == lastOption || g_14cf950 == 0x1c) {
					mode = 0;
					fcn_004b20d0(mode);
				}
			} else {
				mode = 1;
label_53de0b:
				fcn_004b20d0(mode);
			}
			*(int *) 0x7766fc = *(int *) 0x7728d4;
			if (*(int *) 0x7766fc == 0) {
				mode = 2;
label_53de37:
				d2_SelectRadioGroup(dlg, mode);
			} else if (*(int *) 0x7766fc == 1) {
				mode = 0;
				goto label_53de37;
			} else if (*(int *) 0x7766fc == 2) {
				mode = 1;
				d2_SelectRadioGroup(dlg, mode);
			}
			d2_SetFormVisibility(obj, 0);
			v13 = fcn_004b41b0();
			d2_SetFormVisibility(obj, 1);
label_53de5c:
			d2_SetFormVisibility(obj, 0);
			retry = 0;
			if (v13 != 0xff || v2) {
				g_7e242c = v13;
				if (!v2) {
					main_LoopFlags = 0x12d6;
					cut_WaitForScript(fcn_004e4470((const char *) 0x6a4040));
				}
				v2 = 0;
				again = d2_RunChoosePlayerDialog(0xc6, 0);
				if (again == 0) {
					main_LoopFlags = 0x12d6;
					cut_WaitForScript(fcn_004e4470((const char *) 0x6a4024));
					retry = 1;
				} else {
					v4 = fcn_0053e8a0(0);
					if (v4 == 1) {
						d2_SuppressOverlay = v4;
						*(int *) 0x6a37f8 = d2_OpenMessageBox(*(int *) 0x14abf04, 0);
						if (d2_RunParentProfessionSelection(0)) {
label_53df85:
							again = 1;
							g_774654 = 1;
						} else {
							d3_SelectSceneContext(0, 0);
							v2 = 1;
						}
					} else {
						if (v4 == 0) {
							if (d2_ShowChooseProfessionDialog(0xc6)) {
								p = gm_GetStatRecord(buf, *(unsigned char *) 0x7e23e3);
								*(int *) 0x7e2430 = *p;
								*(char *) 0x7e2434 = (char) *(unsigned short *) &p[1];
								g_7e2468 =
								    gm_FindHeadIconIndex((const char *) 0x6a3db4) + 0x639;
								goto label_53df85;
							}
							d3_SelectSceneContext(0, 0);
							again = 0;
							retry = 1;
						} else {
							if (v4 == -1) {
								again = 0;
								v2 = 1;
							}
						}
					}
				}
			}
			d2_SetFormVisibility(obj, 1);
		} else {
			if (v2) {
				goto label_53de5c;
			}
			retry = 0;
			if (g_100f1dc == 1) {
				g_774654 = 1;
			}
		}
		r = main_RunFrameLoop(0x53dc20, 0xc6);
	}
}
