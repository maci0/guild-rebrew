typedef struct
{
	char pad0[0x5c];
	int x5c;
	char pad60[0x6c];
	char name[0x100];
	int x1cc;
	int x1d0;
	char pad1d4[0x2f4 - 0x1d4];
} Ctl;

extern int d2_CurrentWindowId;
#include "Develop/Units/d2.v1/d2_gui.h"
extern char* g_14a5ad8[];
extern int d2_DialogButtonAction;
extern int d2_CurrentElementId;
extern char g_7e23e3;
#include "Develop/Units/d2.v1/client_dialog_state.h"
extern char s_6a3f8c[];

int __cdecl d2_LoadForm(int, int, char*);
void __cdecl d2_CenterDialogWindows(int);
void __cdecl d2_SetForm(int, int);
int __cdecl io_AppendText(int, ...);
int __cdecl d2_CreateRadioGroup(int);
int __cdecl d2_AddElementToWindow(int, int, int, int);
void __cdecl d2_AddToRadioGroup(int, int);
int __cdecl main_RunFrameLoop(void*, int);
void __cdecl d2_ShowChooseProfessionDialog(void);
void __cdecl d2_UpdateRadioGroup(int);
char __cdecl gm_GetRangeStatId(int, int);
void __cdecl d2_ClearRadioGroup(int);
void __cdecl d2_DestroyForm(int);
#include "Develop/Units/d2.v1/d2_win.h"









extern int d2_NetLobbyForm;
#include "Develop/client_types.h"
extern Win_1015f40 d2_Windows[0x60];
extern int g_774a3c;
extern int g_774a38;
extern char* d2_LobbyLocalPlayerEntry;
extern char* g_14b5d58;

char* __cdecl d2_GetCurrentTextLogRecord(void);
char* __cdecl d2_NextTextLogRecord(void);
void __cdecl d2_SetForm(int, int);
int __cdecl io_AppendText(int, ...);
char* __cdecl d3_GetSceneEntry(int);
int __cdecl sprintf(char*, const char*, ...);
void __cdecl d2_UpdateWindowScroll(int);

/* ADDRESS: GOLDTL 0x00593ff0 */
int __cdecl d2_ChooseProfession(int a1)
{
	int grp;
	int r;
	int dlg;
	int types[11];
	int btns[11];
	int i;
	int t;
	int h;
	char* s;
	char* d;
	char c;

	r = 0;
	types[0] = 1;
	types[1] = 2;
	types[2] = 3;
	types[3] = 4;
	types[4] = 5;
	types[5] = 6;
	types[6] = 7;
	types[7] = 11;
	types[8] = 13;
	types[9] = 14;
	types[10] = 15;
	dlg = d2_LoadForm(0, 0, s_6a3f8c);
	d2_CenterDialogWindows(dlg);
	d2_SetForm(dlg, 0);
	io_AppendText(0x1afa);
	grp = d2_CreateRadioGroup(0);
	for (i = 0; i < 11; i++) {
		t = types[i];
		h = d2_AddElementToWindow(i % 3 * 96 + 100, (i / 3 + 1) * 80, t + 0x5a1, d2_CurrentWindowId);
		btns[i] = h;
		(*(int*)&((D2_CONTROL_TL*)d2_Controls)[h].value_05c) = 1;
		(*(int*)&((D2_CONTROL_TL*)d2_Controls)[h].flags_1d0) = 3;
		s = g_14a5ad8[t];
		d = ((char*)&((D2_CONTROL_TL*)d2_Controls)[h] + 0xcc);
		do {
			c = *s++;
			*d++ = c;
		} while (c != 0);
		(*(int*)&((D2_CONTROL_TL*)d2_Controls)[h].value_1cc) = 0x56;
		d2_AddToRadioGroup(grp, h);
	}
	d2_DialogButtonAction = -1;
	while (main_RunFrameLoop((void*) d2_ShowChooseProfessionDialog, a1) != 0) {
		d2_UpdateRadioGroup(grp);
		if (d2_DialogButtonAction != -1) {
			for (i = 0; i < 11; i++) {
				if (d2_CurrentElementId == btns[i]) {
					g_7e23e3 = gm_GetRangeStatId(types[i], 1);
					d2_DialogCloseRequested = 1;
					r = 1;
					break;
				}
			}
		}
	}
	d2_ClearRadioGroup(grp);
	d2_DestroyForm(dlg);
	return r;
}

/* ADDRESS: GOLDTL 0x005941e0 */
/* ADDRESS: GOLDDE 0x00579ca0 */
void __cdecl d2_RefreshNetLobbyChatLog(void)
{
	char buf[0x160];
	int last;
	int h;
	int n;
	char* e;
	char* p;

	last = -1;
	e = d2_GetCurrentTextLogRecord();
	d2_SetForm(d2_NetLobbyForm, 5);
	h = *(int*) &((D2_WIN*)d2_Windows)[d2_CurrentWindowId].pad3c[0x218];
	io_AppendText((int) "$C");
	g_774a3c = 0;
	while (e != 0) {
		g_774a3c++;
		p = d3_GetSceneEntry(*(int*) (e + 0x68));
		if (p != 0 && *(int*) p == *(int*) (e + 0x68)) {
			n = *(int*) (p + 0xc);
		} else {
			n = 9;
		}
		if (*(int*) (e + 0x64) != 0) {
			if ((((int*)d2_LobbyLocalPlayerEntry) != 0 && *(int*) (e + 0x64) == *((int*)d2_LobbyLocalPlayerEntry)) || *(int*) (e + 0x68) == *((int*)d2_LobbyLocalPlayerEntry)) {
				sprintf(buf, "$%dFF%s (%s): %s$A", n, e + 0x40, g_14b5d58, e);
			}
		} else {
			sprintf(buf, "$%dFF%s: %s$A", n, e + 0x40, e);
		}
		last = io_AppendText((int) buf);
		e = d2_NextTextLogRecord();
	}
	if (g_774a3c > g_774a38 && last >= 0 && h > ((D2_WIN*)d2_Windows)[d2_CurrentWindowId].height) {
		g_774a38 = g_774a3c;
		n = h + 0x18;
		*(int*) &((D2_WIN*)d2_Windows)[d2_CurrentWindowId].pad3c[0x218] = n;
		*(int*) &((D2_WIN*)d2_Windows)[d2_CurrentWindowId].pad3c[0x21c] = n - ((D2_WIN*)d2_Windows)[d2_CurrentWindowId].height;
		d2_UpdateWindowScroll(d2_CurrentWindowId);
	}
}
