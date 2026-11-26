extern char g_68ce48[];
extern unsigned short* g_772f24;
extern char g_6b5c60[];
extern int d2_CurrentWindowId;
extern char* g_77255c;
extern int g_68bfbc;
extern int cut_EventLoopFlags;
#include "client_dialog_state.h"
extern int g_100f1dc;

int __cdecl fcn_00470820(int, int, char*);
void __cdecl fcn_00471d80(int, int);
void __cdecl d2_SetForm(int, int);
int __cdecl io_AppendText(int, ...);
int __cdecl fcn_004677e0(int, int, int, int, int, int, int, int);
int __cdecl d2_UpdateProgressBar(int, int, int);
int __cdecl main_RunFrameLoop(void*, int);
void __cdecl fcn_00471e30(int);
extern int g_772f2c;
extern int d2_CurrentElementId;

char* __cdecl gm_LookupEntityRecordById(int);
int __cdecl fcn_00470820(int, int, char*);
void __cdecl fcn_00471d80(int, int);
void __cdecl d2_SetForm(int, int);
int __cdecl io_AppendText(int, ...);
int __cdecl d2_GetWindowListItem(int, int, int);
int __cdecl fcn_004677e0(int, int, int, int, int, int, int, int);
int __cdecl d2_UpdateProgressBar(int, int, int);
int __cdecl main_RunFrameLoop(void*, int);
void __cdecl fcn_004cfca0(void);
void __cdecl fcn_00471e30(int);

void __cdecl fcn_004e15c0(void);
void __cdecl fcn_004e16e0(void);

/* ADDRESS: GOLDTL 0x004e15c0 */
void __cdecl fcn_004e15c0(char* state)
{
	int h;
	int w;

	h = fcn_00470820(0, 0, g_68ce48);
	fcn_00471d80(h, 3);
	d2_SetForm(h, 0);
	io_AppendText(0x10de, *g_772f24);
	state[0x94] = 0;
	state[0x14] = (*(char*)g_6b5c60);
	w = fcn_004677e0((*(int*) (g_77255c + 0xc) - 300) / 2 - 8, 8, 300, 0, 100, 0x75, 0x42, d2_CurrentWindowId);
	d2_UpdateProgressBar(w, g_68bfbc * 75, 1);
	while (main_RunFrameLoop(fcn_004e15c0, cut_EventLoopFlags) != 0) {
		if (d2_UpdateProgressBar(w, 0, 0) == 0)
			g_774654 = 1;
		if (g_100f1dc == 2) {
			state[0x94] = 1;
			g_774654 = 1;
		} else if (g_100f1dc == 1) {
			state[0x94] = 0;
			g_774654 = 1;
		}
	}
	fcn_00471e30(h);
}

/* ADDRESS: GOLDTL 0x004e16e0 */
void __cdecl fcn_004e16e0(char* state, int* event)
{
	int b2;
	char* x;
	char* y;
	char* who;
	int h;
	int t;
	int b0;
	int b1;
	int w;

	x = gm_LookupEntityRecordById(event[13]);
	y = gm_LookupEntityRecordById(event[14]);
	if (*(int*) (x + 4) == ((int*)g_772f24)[1])
		who = y;
	else
		who = x;
	h = fcn_00470820(0, 0, g_68ce48);
	fcn_00471d80(h, 3);
	d2_SetForm(h, 0);
	t = io_AppendText(0x10e6, g_772f2c, *(unsigned short*) ((int*)g_772f24), *(unsigned short*) who);
	b0 = d2_GetWindowListItem(h, 0, t);
	b1 = d2_GetWindowListItem(h, 0, t + 1);
	b2 = d2_GetWindowListItem(h, 0, t + 2);
	state[0x94] = 4;
	state[0x14] = (*(char*)g_6b5c60);
	w = fcn_004677e0((*(int*) (g_77255c + 0xc) - 300) / 2 - 8, 8, 300, 0, 100, 0x75, 0x42, d2_CurrentWindowId);
	d2_UpdateProgressBar(w, g_68bfbc * 75, 1);
	while (main_RunFrameLoop(fcn_004e16e0, cut_EventLoopFlags) != 0) {
		fcn_004cfca0();
		if (g_100f1dc != -1) {
			if (d2_CurrentElementId == b0)
				state[0x94] = 2;
			else if (d2_CurrentElementId == b1)
				state[0x94] = 3;
			else if (d2_CurrentElementId == b2)
				state[0x94] = 4;
			g_774654 = 1;
		}
		if (d2_UpdateProgressBar(w, 0, 0) == 0)
			g_774654 = 1;
	}
	fcn_00471e30(h);
}

/* ADDRESS: GOLDTL 0x004e1900 */
void __cdecl fcn_004e1900(void)
{
	if (g_772f2c == 0) {
		fcn_004e15c0();
	} else {
		fcn_004e16e0();
	}
}
