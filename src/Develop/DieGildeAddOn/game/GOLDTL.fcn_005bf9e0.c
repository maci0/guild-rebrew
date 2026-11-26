int __cdecl gm_WalkEntityChain(unsigned short id);
int __cdecl gm_CheckPrivilege(int, int, void*);
int __cdecl he_StartHandlungSearch(int, int, int, int, int);
int __cdecl he_fn_Handlung(void);
void __cdecl io_FormatTextBuffer(char*, int, ...);
void __cdecl fcn_00526120(char*, int);
int __cdecl gm_CheckEntityStock(int, int, char);
int __cdecl he_HasNoActiveEvent04b(unsigned short*, int);
int __cdecl he_HasNoActiveAction0x2e(unsigned short*, int);
int __cdecl he_HasNoActiveAction0x88(unsigned short*, int);
int __cdecl fcn_00470820(int, int, char*);
void __cdecl d2_CenterDialogWindows(int);
void __cdecl d2_SetForm(int, int);
void __cdecl d2_SetOverlayAnimation(int, int);
int __cdecl d2_GetWindowListItem(int, int, int);
int __cdecl io_AppendText(int, int, int, int);
void __cdecl fcn_005c9220(int*);
int __cdecl main_RunFrameLoop(int, int);
void __cdecl fcn_00471e30(int);
int __cdecl gm_SelectRandomEntityCandidate(unsigned short*);
void __cdecl cm_SendLogAction(char*);
void __cdecl cm_SendTraceEnd(char*);
void __cdecl cm_SendCopyEntityData(void*);
#include "Develop/DieGildeAddOn/game/game_data.h"
extern int g_14ce8e0;
extern int d2_CurrentElementId;
extern int g_774654;
/* ADDRESS: GOLDTL 0x005bf9e0 */
int __cdecl fcn_005bf9e0(unsigned short* entity)
{
	unsigned int data[136];
	unsigned char evt[0x100];
	char text[1024];
	int t[6];
	int idx;
	int res;
	int i;
	int timeout;
	int hwnd;
	int query;
	int r;

	for (i = 0; i < 136; i++) {
		data[i] = 0;
	}
	timeout = *(unsigned short*) &g_774970;
	idx = -1;
	res = 0;
	data[0] = 1;
	r = gm_WalkEntityChain(*(unsigned short*) (timeout * 0x21c + (unsigned long)&g_7f4ca0));
	timeout = (int) ((float) r * 0.0085f);
	if (gm_CheckPrivilege(0x1b, *(unsigned short*) &g_774970 * 0x21c + 0x7f4ca0, data) & 2) {
		timeout /= 2;
	}
	query = he_StartHandlungSearch(2, 2, *(unsigned short*) &g_774970, 0, 0x1a);
	while (query) {
		if (*(int*) (query + 0xb4) == *(int*) (entity + 2)) {
			io_FormatTextBuffer(text, 0x170a, *entity);
			fcn_00526120(text, 4);
			return 0;
		}
		query = he_fn_Handlung();
	}
	if (!gm_CheckEntityStock(*(unsigned short*) &g_774970 * 0x21c + 0x7f4ca0, timeout, *(char*) &g_773d75)) {
		return 0;
	}
	if (!he_HasNoActiveEvent04b(entity, *(unsigned short*) &g_774970 * 0x21c + 0x7f4ca0)) {
		io_FormatTextBuffer((char*) evt, 0x170b, *entity);
		fcn_00526120((char*) evt, 0);
		return 0;
	}
	if (!he_HasNoActiveAction0x2e(entity, *(unsigned short*) &g_774970 * 0x21c + 0x7f4ca0)) {
		io_FormatTextBuffer((char*) evt, 0x170c, *entity);
		fcn_00526120((char*) evt, 0);
		return 0;
	}
	if (!he_HasNoActiveAction0x88(entity, *(unsigned short*) &g_774970 * 0x21c + 0x7f4ca0)) {
		io_FormatTextBuffer((char*) evt, 0x409f);
		fcn_00526120((char*) evt, 0);
		return 0;
	}
	hwnd = fcn_00470820(0, 0, (char*) 0x6ac494);
	d2_CenterDialogWindows(hwnd);
	d2_SetForm(hwnd, 1);
	d2_SetOverlayAnimation(0, 0);
	if (entity) {
		d2_SetForm(hwnd, 1);
		idx = d2_GetWindowListItem(hwnd, 1, io_AppendText(0x1708, 0x1711, timeout, *entity));
	}
	for (i = 0; i < 6; i++) {
		t[i] = -1;
	}
	t[0] = hwnd;
	t[1] = 2;
	t[2] = 3;
	t[3] = 4;
	t[4] = 3;
	t[5] = 0x15;
	fcn_005c9220(t);
	while (main_RunFrameLoop(0x5bf9e0, 0x677c7)) {
		if (g_14ce8e0 || *(int*) &g_100f1dc == 1) {
			g_774654 = 1;
		}
		if (*(int*) &g_100f1dc == 2 && idx != -1 && d2_CurrentElementId == idx) {
			*(unsigned char*) (evt + 4) = 0x1a;
			*(unsigned int*) (evt + 8) = *(unsigned int*) (*(unsigned short*) &g_774970 * 0x21c + (unsigned long)&g_7f4ca4);
			*(unsigned int*) (evt + 0x0c) = *(unsigned int*) (g_7746c4 + 1);
			*(unsigned char*) (evt + 0x36) = 1;
			*(unsigned int*) (evt + 0x84) = timeout;
			*(unsigned int*) (evt + 0x60) = *(unsigned int*) (entity + 2);
			*(unsigned int*) (evt + 0x58) = gm_SelectRandomEntityCandidate(entity);
			cm_SendLogAction((char*) 0x6ac4c0);
			cm_SendCopyEntityData(evt);
			cm_SendTraceEnd((char*) 0x6ac4c0);
			io_FormatTextBuffer(text, 0x1709, *entity);
			fcn_00526120(text, 0);
			g_774654 = 1;
			res = 1;
		}
	}
	fcn_00471e30(hwnd);
	return res;
}
