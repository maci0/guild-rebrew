extern int g_7746d8;
extern char* g_14b5494;
extern int g_14ce8e0;
#include "client_dialog_state.h"
extern char* g_7746a0;

void __cdecl fcn_005338a0(void);
char* __cdecl RegisterStatusText(char* name, char* path, int arg);
int __cdecl main_RunFrameLoop(void* p, int mask);
void __cdecl d2_RunDomizilKabinettDialog(int unused, char* p);
void __cdecl d2_RunKanoneUI(int h);
void __cdecl d2_RunDomizilKanoneMenu(int dlg, char* msg);

/* ADDRESS: GOLDTL 0x0058ae60 */
void __cdecl d2_RunDomizilKanoneMenu(int dlg, char* msg)
{
	char* control;

	control = 0;
	fcn_005338a0();
	if (!main_RunFrameLoop((void*) d2_RunDomizilKanoneMenu, 0x67fff)) {
		return;
	}
	do {
		if (g_7746d8 & 0x400) {
			control = RegisterStatusText("contact_KANONE", g_14b5494, 0x16);
		}
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
		}
		if (g_7746a0 != 0) {
			if (*(int*) (msg + 0x1c) != 0) {
				d2_RunDomizilKabinettDialog(dlg, msg);
			} else if (g_7746a0 == control) {
				d2_RunKanoneUI(dlg);
			}
		}
	} while (main_RunFrameLoop((void*) d2_RunDomizilKanoneMenu, 0x67fff));
}
