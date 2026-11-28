

extern char g_6a4144[];
extern int d2_CurrentWindowId;
extern char* d2_CurrentWindow;
extern char* g_14b5e38;
extern int g_14b5e3c;
extern int g_14b5e40;
extern int g_14b5e44;
extern int g_14b5e48;
extern int g_14b5e4c;
extern int g_7e1fa0[];
#include "Develop/DieGildeAddOn/game/game_data.h"
extern char io_LastKeyScancode;
#include "Develop/Units/d2.v1/client_dialog_state.h"
extern int d2_DialogButtonAction;
extern float g_6640cc;
extern float g_66292c;

int __cdecl d2_LoadForm(int, int, char*);
void __cdecl d2_CenterDialogWindows(int);
void __cdecl d2_SetForm(int, int);
void __cdecl d2_InitWindowBounds(int);
int __cdecl io_AppendText(int, ...);
int __cdecl sprintf(char*, const char*, ...);
int __cdecl d2_AddWindowValueGauge(int, int, int, int, int, int, int, int);
#include "Develop/Units/d2.v1/d2_gui.h"
void __cdecl d2_SetValueGaugeFlags(int, int);
void __cdecl d2_SetValueGaugeLabel(int, char*);
void __cdecl d2_SetValueGaugeStepLabels(int, int, int, int, int, int, int);
int __cdecl d2_GetWindowListItem(int, int, int);
int __cdecl main_RunFrameLoop(void (__cdecl*)(int), int);
int __cdecl d2_GetControlValue(int);
void __cdecl d2_DestroyForm(int);

/* ADDRESS: GOLDDE 0x00525680 */
void __cdecl d2_RunChooseOpponentsDialog(int n)
{
	int h;
	int ids[0x10];
	char buf[0x100];
	int w;
	int x;
	int i;
	int ok;

	h = d2_LoadForm(0, 0, g_6a4144);
	d2_CenterDialogWindows(h);
	d2_SetForm(h, 0);
	d2_InitWindowBounds(d2_CurrentWindowId);
	d2_SetForm(h, 1);
	io_AppendText(0x42c5);
	d2_SetForm(h, 3);
	w = (int) (g_6640cc / n * g_66292c);
	x = (*(int*) (d2_CurrentWindow + 0x10) - w * n) / 2 + 0xe;
	for (i = 0; i < n; i++) {
		sprintf(buf, "%s %c", g_14b5e38, i + 0x41);
		ids[i] = d2_AddWindowValueGauge(0x80, x + i * w, 0xc8, 0, 0x64, 0x7b, 0x802, d2_CurrentWindowId);
		d2_SetElementValue(ids[i], 0, 4, g_7e1fa0[i]);
		d2_SetValueGaugeFlags(ids[i], 0x82);
		d2_SetValueGaugeLabel(ids[i], buf);
		d2_SetValueGaugeStepLabels(ids[i], 5, g_14b5e3c, g_14b5e40, g_14b5e44, g_14b5e48, g_14b5e4c);
	}
	d2_SetForm(h, 2);
	ok = d2_GetWindowListItem(h, 2, io_AppendText(0x7d));
	while (main_RunFrameLoop(d2_RunChooseOpponentsDialog, 0xc6) != 0) {
		if (io_RightButtonReleased != 0 || io_LastKeyScancode == 1 || (d2_DialogButtonAction == 2 && d2_CurrentElementId == ok)) {
			d2_DialogCloseRequested = 1;
		}
	}
	for (i = 0; i < n; i++) {
		g_7e1fa0[i] = d2_GetControlValue(ids[i]);
	}
	d2_DestroyForm(h);
}
