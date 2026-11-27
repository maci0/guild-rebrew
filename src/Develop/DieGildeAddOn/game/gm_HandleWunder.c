#include "Develop/DieGildeAddOn/game/game_data.h"
#include "client_dialog_state.h"

void __cdecl cm_RequestModifyHealth(int, int);
unsigned short __cdecl gm_RandomMod(int);
void __cdecl gm_ApplyMiracleEffect(char*, int);
int __cdecl d2_LoadForm(int, int, char*);
void __cdecl d2_SetOverlayAnimation(int, int);
void __cdecl d2_CenterDialogWindows(int);
void __cdecl d2_SetForm(int, int);
int __cdecl io_AppendText(int, ...);
int __cdecl d2_CheckActionBlocker(char*, int);
int __cdecl main_RunFrameLoop(void*, int);
void __cdecl d2_DestroyForm(int);

#if defined(REBREW_GOLD)
/* ADDRESS: GOLD 0x005cd430 */
int __cdecl gm_HandleWunder(char* e)
{
	int r;
	int dlg;

	if (e[2] != 6 && e[2] != 7) {
		if (*(int*) (e + 0x194) < 4) {
			return 0x20;
		}
		cm_RequestModifyHealth(*(int*) (e + 4), -4);
		gm_ApplyMiracleEffect(e, gm_RandomMod(6));
		return 0x10;
	}
	if (e[2] == 6) {
		r = 0;
		dlg = d2_LoadForm(0, 0, "privillegien\\wunder");
		d2_SetOverlayAnimation(0, 0);
		d2_CenterDialogWindows(dlg);
		d2_SetForm(dlg, 1);
		io_AppendText(0x1df6, 4);
		g_100f1dc = -1;
		do {
			if (g_100f1dc != -1) {
				if (g_100f1dc == 0) {
					if (d2_CheckActionBlocker(e, 4) != 0) {
						cm_RequestModifyHealth(*(int*) (e + 4), -4);
						gm_ApplyMiracleEffect(e, gm_RandomMod(6));
						r = 1;
						g_774654 = 1;
					}
				} else if (g_100f1dc == 1) {
					g_774654 = 1;
				}
			}
			if (g_14ce8e0 != 0) {
				g_774654 = 1;
			}
		} while (main_RunFrameLoop((void*) gm_HandleWunder, 0x657c7) != 0);
		d2_DestroyForm(dlg);
		return r;
	}
	return 0;
}
#else
/* ADDRESS: GOLDTL 0x005d96d0 */
int __cdecl gm_HandleWunder(char* e)
{
	int r;
	int dlg;

	if (e[2] != 6 && e[2] != 7) {
		if (*(int*) (e + 0x194) < 4) {
			return 0x20;
		}
		cm_RequestModifyHealth(*(int*) (e + 4), -4);
		gm_ApplyMiracleEffect(e, gm_RandomMod(6));
		return 0x10;
	}
	if (e[2] == 6) {
		r = 0;
		dlg = d2_LoadForm(0, 0, "privillegien\\wunder");
		d2_SetOverlayAnimation(0, 0);
		d2_CenterDialogWindows(dlg);
		d2_SetForm(dlg, 1);
		io_AppendText(0x1df6, 4);
		g_100f1dc = -1;
		do {
			if (g_100f1dc != -1) {
				if (g_100f1dc == 2) {
					if (d2_CheckActionBlocker(e, 4) != 0) {
						cm_RequestModifyHealth(*(int*) (e + 4), -4);
						gm_ApplyMiracleEffect(e, gm_RandomMod(6));
						r = 1;
						g_774654 = 1;
					}
				} else if (g_100f1dc == 1) {
					g_774654 = 1;
				}
			}
			if (g_14ce8e0 != 0) {
				g_774654 = 1;
			}
		} while (main_RunFrameLoop((void*) gm_HandleWunder, 0x657c7) != 0);
		d2_DestroyForm(dlg);
		return r;
	}
	return 0;
}
#endif
