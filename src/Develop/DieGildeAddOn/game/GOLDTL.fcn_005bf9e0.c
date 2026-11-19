int __cdecl gm_WalkEntityChain(unsigned short id);
int __cdecl fcn_004fa5b0(int, int, void*);
int __cdecl fcn_005463a0(int, int, int, int, int);
int __cdecl he_fn_Handlung(void);
void __cdecl io_FormatTextBuffer(char*, int, ...);
void __cdecl fcn_00526120(char*, int);
int __cdecl fcn_00526010(int, int, char);
int __cdecl fcn_0055c0f0(unsigned short*, int);
int __cdecl fcn_0055c0a0(unsigned short*, int);
int __cdecl fcn_00579640(unsigned short*, int);
int __cdecl fcn_00470820(int, int, char*);
void __cdecl d2_CenterDialogWindows(int);
void __cdecl d2_SetForm(int, int);
void __cdecl d2_SetOverlayAnimation(int, int);
int __cdecl fcn_00472250(int, int, int);
int __cdecl io_AppendText(int, int, int, int);
void __cdecl fcn_005c9220(int*);
int __cdecl fcn_005373e0(int, int);
void __cdecl fcn_00471e30(int);
int __cdecl fcn_004faaf0(unsigned short*);
void __cdecl fcn_004c4eb0(char*);
void __cdecl fcn_004c4ef0(char*);
void __cdecl fcn_004c5530(void*);
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
	if (fcn_004fa5b0(0x1b, *(unsigned short*) &g_774970 * 0x21c + 0x7f4ca0, data) & 2) {
		timeout /= 2;
	}
	query = fcn_005463a0(2, 2, *(unsigned short*) &g_774970, 0, 0x1a);
	while (query) {
		if (*(int*) (query + 0xb4) == *(int*) (entity + 2)) {
			io_FormatTextBuffer(text, 0x170a, *entity);
			fcn_00526120(text, 4);
			return 0;
		}
		query = he_fn_Handlung();
	}
	if (!fcn_00526010(*(unsigned short*) &g_774970 * 0x21c + 0x7f4ca0, timeout, *(char*) &g_773d75)) {
		return 0;
	}
	if (!fcn_0055c0f0(entity, *(unsigned short*) &g_774970 * 0x21c + 0x7f4ca0)) {
		io_FormatTextBuffer((char*) evt, 0x170b, *entity);
		fcn_00526120((char*) evt, 0);
		return 0;
	}
	if (!fcn_0055c0a0(entity, *(unsigned short*) &g_774970 * 0x21c + 0x7f4ca0)) {
		io_FormatTextBuffer((char*) evt, 0x170c, *entity);
		fcn_00526120((char*) evt, 0);
		return 0;
	}
	if (!fcn_00579640(entity, *(unsigned short*) &g_774970 * 0x21c + 0x7f4ca0)) {
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
		idx = fcn_00472250(hwnd, 1, io_AppendText(0x1708, 0x1711, timeout, *entity));
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
	while (fcn_005373e0(0x5bf9e0, 0x677c7)) {
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
			*(unsigned int*) (evt + 0x58) = fcn_004faaf0(entity);
			fcn_004c4eb0((char*) 0x6ac4c0);
			fcn_004c5530(evt);
			fcn_004c4ef0((char*) 0x6ac4c0);
			io_FormatTextBuffer(text, 0x1709, *entity);
			fcn_00526120(text, 0);
			g_774654 = 1;
			res = 1;
		}
	}
	fcn_00471e30(hwnd);
	return res;
}
