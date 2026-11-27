#include <string.h>
#include "Develop/DieGildeAddOn/game/game_data.h"
#pragma intrinsic(memset)

extern int g_100f1dc;
extern int g_774654;

int __cdecl d2_LoadForm(int, int, char*);
void __cdecl d2_SetOverlayAnimation(int, int);
void __cdecl d2_CenterDialogWindows(int);
void __cdecl d2_DestroyForm(int);
int __cdecl d2_GetControlValue(int);
int __cdecl d2_GetWindowListItem(int, int, int);
#include "d2_gui.h"
void __cdecl d2_SetElementEnabled(int, int);
void __cdecl d2_SetForm(int, int);
int __cdecl cm_GetCommandStatus(int);
void __cdecl cm_RequestChangeBits(int, int, int, int, int);
void __cdecl cm_RequestModifyHealth(int, int);
int __cdecl gm_GetLawEntry(int, void*);
int __cdecl gm_SetLawValue(char*, unsigned char, int);
int __cdecl io_AppendText(int, ...);
int __cdecl d2_CheckActionBlocker(char*, int);
void __cdecl cm_StepCommandQueue(void);
int __cdecl main_RunFrameLoop(void*, int);

/* ADDRESS: GOLDTL 0x005d6540 */
int __cdecl d2_ShowGesetzDialog(char* entity, int* request)
{
	int rec[9];
	int r;
	int limit;
	char* recp;
	int add;
	int keep;
	int ctl;
	int box;
	int id;
	int idx;
	int delta;
	int dlg;

	r = 0;
	if (request[0] == 3) {
		recp = entity;
	} else if (request[0] == 4) {
		recp = (char*) request[0x87];
		if (recp == 0) {
			return 0x60;
		}
	} else {
		return 0x60;
	}
	if (request[0x85] == 1) {
		limit = 0x80000;
	} else if (request[0x85] == 2) {
		limit = 0x100000;
	} else {
		return 0x60;
	}
	if (entity[2] != 6) {
		if (*(int*) (entity + 0x194) < 2) {
			return 0x20;
		}
		if (gm_GetLawEntry(request[1], rec) == 0) {
			return 0x60;
		}
		if (request[2] == rec[6]) {
			return 0x60;
		}
		if (request[2] > rec[2]) {
			return 0x60;
		}
		if (request[2] < rec[1]) {
			return 0x60;
		}
		gm_SetLawValue(entity, *(unsigned char*) rec, request[2]);
		cm_RequestModifyHealth(*(int*) (entity + 4), -2);
		cm_RequestChangeBits(*(int*) (recp + 4), 0x1c8, 4, limit, 0);
		if (entity[2] != 6) {
			return 0;
		}
	}
	*(unsigned char*)rec = 0;
	memset((char*)rec + 1, 0, 35);
	keep = 1;
	add = 0;
	box = -1;
	if (gm_GetLawEntry(request[1], rec) == 0) {
		return 0;
	}
	id = 0x13fd + *(unsigned char*) rec * 5;
	dlg = d2_LoadForm(0, 0, "privillegien\\gesetz");
	d2_SetOverlayAnimation(0, 0);
	d2_CenterDialogWindows(dlg);
	d2_SetForm(dlg, 1);
	io_AppendText(0x1ba9);
	switch (*(unsigned char*) ((char*) rec + 1)) {
	case 0:
		id = io_AppendText(0x13d0, id, 0x13d3);
		ctl = d2_GetWindowListItem(dlg, 1, id);
		box = d2_GetWindowListItem(dlg, 1, id + 1);
		d2_SetElementValue(ctl, rec[1], rec[2], rec[6]);
		break;
	case 1:
		id = io_AppendText(0x13da, id, 0x13dd, rec[6] + 0x13dd);
		ctl = d2_GetWindowListItem(dlg, 1, id);
		box = d2_GetWindowListItem(dlg, 1, id + 1);
		add = 0x13dd;
		break;
	case 2:
		ctl = d2_GetWindowListItem(dlg, 1, io_AppendText(0x13e3, id, id, 0x13e7 - rec[6]));
		keep = 0;
		break;
	case 3:
		id = io_AppendText(0x13e9, 0x13ec, rec[6] + 0x13ec);
		ctl = d2_GetWindowListItem(dlg, 1, id);
		box = d2_GetWindowListItem(dlg, 1, id + 1);
		add = 0x13ec;
		break;
	default:
		return 0;
	}
	g_100f1dc = -1;
	do {
		if (keep) {
			if (d2_GetControlValue(ctl) - add != rec[6] && box != -1) {
				d2_SetElementEnabled(box, 1);
			} else {
				d2_SetElementEnabled(box, 0);
			}
		}
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
		}
		if (g_100f1dc != -1) {
			if (g_100f1dc == 2) {
				if (d2_CheckActionBlocker(entity, 2) != 0) {
					if (*(unsigned char*) ((char*) rec + 1) == 2) {
						delta = 1 - rec[6];
					} else {
						delta = d2_GetControlValue(ctl) - add;
					}
					r = 0x80;
					idx = gm_SetLawValue(entity, *(unsigned char*) rec, delta);
					if (idx != -1) {
						while (cm_GetCommandStatus(idx) == 0) {
							cm_StepCommandQueue();
						}
						cm_RequestModifyHealth(*(int*) (entity + 4), -2);
						cm_RequestChangeBits(*(int*) (recp + 4), 0x1c8, 4, limit, 0);
					}
					g_774654 = 1;
				}
			} else if (g_100f1dc == 1) {
				g_774654 = 1;
			}
		}
	} while (main_RunFrameLoop((void*) d2_ShowGesetzDialog, 0x657c7) != 0);
	d2_DestroyForm(dlg);
	return r;
}
