#include <string.h>

#include "Develop/client_types.h"

char* __cdecl he_StartHandlungSearch(int n, ...);
char* __cdecl he_fn_Handlung(void);
char* __cdecl gm_LookupEntityRecordById(int a1);
char* __cdecl io_FormatTextBuffer(char* buf, int id, ...);
char* __cdecl io_AppendText(int fmt, ...);
int __cdecl d2_LoadForm(int a, int b, char* name);
int __cdecl d2_CenterDialogWindows(int);
int __cdecl d2_SetOverlayAnimation(int, int);
int __cdecl d2_SetForm(int, int);
int __cdecl d2_GetWindowListItem(char*, int, char*);
int __cdecl d2_DestroyForm(int);
int __cdecl main_RunFrameLoop(void*, int);
int __cdecl gm_RandomMod(unsigned short n);
void __cdecl cm_SendCopyEntityData(char* a);
void __cdecl cm_RequestMoveCredits(int a1, int a2, char a3, int a4);
int __cdecl cm_SendSetHE(char a1, unsigned char* e);
void __cdecl gm_AddTime(char*, int, int, int);
int __cdecl gm_CheckEntityStock(char*, int, char);
int __cdecl d2_ShowModalMessageBox(char*, int);
int __cdecl d2_RunWerbungSelectDialog(char*, int*);

extern float flt_0_0;
#include "Develop/DieGildeAddOn/game/game_data.h"
#include "Develop/Units/d2.v1/client_dialog_state.h"
#include "Develop/DieGildeAddOn/game/game_player.h"
extern unsigned char gm_ActiveTownIndex;
extern pos14_7f4c00 gm_GameTime;
extern char gm_EntitySlotTable[];

/* ADDRESS: GOLDTL 0x005d3120 */
/* ADDRESS: GOLDDE 0x005b4980 */
int __cdecl d2_RunCourtshipDialog(int entity, int* request)
{
	int mode;
	int id;
	int h;
	int base;
	int q;
	int d;
	int lv[6];
	int ids[9];
	char buf[0xf8];
	char buf2[0x200];
	char buf3[0x200];
	char n;
	char* e;
	char* p;
	char* s;
	int i;
	int v;

	mode = 1;
	base = 0;
	id = -1;
	e = he_StartHandlungSearch(1, 0, 0x41);
	while (e != 0) {
		if (*(int*) (e + 0xac) == *(int*) (entity + 4)) {
			mode = 2;
			id = *(int*) (e + 0xb0);
			if (*(char*) (e + 0xbb) == 1) {
				mode = 3;
			}
			if (*(char*) (e + 0xba) == 1) {
				mode = 4;
			}
			break;
		}
		e = he_fn_Handlung();
	}
	if (*(char*) (entity + 2) != 6) {
		if (e != 0) {
			return 0x20;
		}
		p = gm_LookupEntityRecordById(*(int*) ((char*) request + 0x214));
		if (p == 0 || *(char*) (p + 8) == 0) {
			return 0x20;
		}
		memset(buf, 0, 0xf8);
		*(pos14_7f4c00*) (buf + 0x28) = gm_GameTime;
		*(int*) (buf + 0x08) = *(int*) (entity + 4);
		*(int*) (buf + 0x0c) = *(int*) (entity + 4);
		*(int*) (buf + 0x58) = *(int*) (entity + 4);
		buf[0x04] = 0x41;
		buf[0x36] = 2;
		*(int*) (buf + 0x5c) = *(int*) (p + 4);
		cm_SendCopyEntityData(buf);
		return 0x10;
	}
	if (mode == 1) {
		return d2_RunWerbungSelectDialog((char*) entity, request);
	}
	h = d2_LoadForm(0, 0, (char*) 0x6acbbc);
	d2_CenterDialogWindows(h);
	d2_SetOverlayAnimation(0, 0);
	d2_SetForm(h, 1);
	io_AppendText(0x1cf3);
	if (mode == 2) {
		p = gm_LookupEntityRecordById(id);
		d = (char) *(e + 0xb9);
		d -= (char) *(e + 0xb8);
		d = d < 0 ? 0 : d;
		io_AppendText(0x1ce7, *(unsigned short*) entity, *(unsigned short*) p, d, 0x5d);
	} else if (mode == 3) {
		p = gm_LookupEntityRecordById(id);
		io_AppendText(0x1ce3);
		io_AppendText(0x1d31, *(unsigned short*) p);
	} else if (mode == 4) {
		p = gm_LookupEntityRecordById(id);
		lv[0] = *(int*) (e + 0xc0);
		lv[1] = *(int*) (e + 0xc4);
		lv[2] = *(int*) (e + 0xc8);
		base = *(unsigned char*) (p + 0xd);
		s = e + 0xbc;
		for (i = 0; i < 0xc; i += 4) {
			*(int*) ((char*) &lv[3] + i) = *(unsigned char*) s;
			s++;
		}
		d = (char) *(e + 0xb9);
		d -= (char) *(e + 0xb8);
		io_AppendText(0x1cf4, *(unsigned short*) p, 0x5d, d, 0x5d);
		ids[0] = d2_GetWindowListItem((char*) h, 1,
		                      (char*) io_AppendText(0x1cf5, lv[3] + 0x1d11, lv[0]));
		ids[1] = d2_GetWindowListItem((char*) h, 1,
		                      (char*) io_AppendText(0x1cf6, lv[4] + 0x1d11, lv[1]));
		ids[2] = d2_GetWindowListItem((char*) h, 1,
		                      (char*) io_AppendText(0x1cf7, lv[5] + 0x1d11, lv[2]));
		ids[3] = d2_GetWindowListItem((char*) h, 1, (char*) io_AppendText(0x1cf8));
	}
	d2_DialogButtonAction = -1;
	do {
		if (io_RightButtonReleased != 0) {
			d2_DialogCloseRequested = 1;
		}
		if (d2_DialogButtonAction != -1 && mode == 4) {
			for (i = 0; i < 4; i++) {
				if (d2_CurrentElementId == ids[i]) {
					break;
				}
			}
			if (i < 3) {
				if (gm_CheckEntityStock(gm_EntitySlotTable + gm_LocalPlayerSlot * 540, lv[i], gm_ActiveTownIndex) != 0) {
					n = 0;
					p = gm_LookupEntityRecordById(id);
					q = lv[i];
					d = lv[3 + i] - base;
					{
						float f;

						f = (float) d * (1.0f / 9.0f);
						if (!(f > flt_0_0)) {
							f = flt_0_0;
						}
						v = (int) (f * g_6628b0 + g_6628cc);
					}
					if (v > 0) {
						if (v >= 3) {
							n = 3;
						} else {
							n = (char) v;
						}
						if (v == 1) {
							v = 0x1d02 + (gm_RandomMod(5) & 0xffff) + 5;
						} else if (v == 2) {
							v = 0x1d02 + (gm_RandomMod(4) & 0xffff) + 9;
						} else {
							v = 0x1d02 + (gm_RandomMod(3) & 0xffff) + 0xc;
						}
					} else {
						v = 0x1d02 + (gm_RandomMod(5) & 0xffff);
					}
					io_FormatTextBuffer(buf2, 0x1cf9, *(unsigned short*) p, v);
					*(char*) (e + 0xb8) += n;
					if (*(char*) (e + 0xb8) >= *(char*) (e + 0xb9)) {
						*(pos14_7f4c00*) (e + 0x52) = gm_GameTime;
						gm_AddTime(e + 0x52, 0, 1, 0);
					}
					*(char*) (e + 0xba) = 0;
					*(int*) (e + 0x84) = cm_SendSetHE(0, (unsigned char*) e);
					cm_RequestMoveCredits(-1, *(int*) (entity + 4), gm_ActiveTownIndex, q);
					d2_ShowModalMessageBox(buf2, 0);
					mode = mode;
					d2_DialogCloseRequested = 1;
				}
			} else if (i == 3) {
				p = gm_LookupEntityRecordById(id);
				io_FormatTextBuffer(buf3, 0x1cfa, *(unsigned short*) p);
				*(char*) (e + 0xba) = 0;
				*(int*) (e + 0x84) = cm_SendSetHE(0, (unsigned char*) e);
				d2_ShowModalMessageBox(buf3, 0);
				d2_DialogCloseRequested = 1;
			}
		}
	} while (main_RunFrameLoop((void*) d2_RunCourtshipDialog, 0x657c7) != 0);
	d2_DestroyForm(h);
	return 2;
}
