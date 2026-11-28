extern char g_7f4ca0[];
extern int g_14ce8e0;
#include "Develop/Units/d2.v1/client_dialog_state.h"

int __cdecl fcn_00502cd0(int container_id, int arg_count, ...);
int __cdecl d2_LoadForm(int, int, char*);
void __cdecl d2_CenterDialogWindows(int);
void __cdecl d2_SetForm(int, int);
int __cdecl io_AppendText();
int __cdecl gm_IsActiveWithoutThievesGuild(char*);
int __cdecl main_RunFrameLoop(void*, int);
void __cdecl d3_EndCameraAndUiMode(void);
void __cdecl d2_DestroyForm(int);

/* ADDRESS: GOLDTL 0x005aceb0 */
void __cdecl d2_RunKerkerplanDialog(char* obj)
{
	char* entry;
	int h;
	int count;
	int next;

	count = 0;
	if (fcn_00502cd0(*(int*) (obj + 0x5d), 1, 0, 0xba) == 0) {
		return;
	}
	h = d2_LoadForm(0, 0, "locations\\kerker\\kerkerplan");
	d2_CenterDialogWindows(h);
	d2_SetForm(h, 1);
	io_AppendText(0x19ad);
	d2_SetForm(h, 1);
	entry = g_7f4ca0;
	do {
		if (gm_IsActiveWithoutThievesGuild(entry) != 0) {
			io_AppendText(0x19ae, count + 1, *(unsigned short*) entry);
			count++;
		}
		entry += 0x21c;
	} while ((int) entry < 0x85a0a0);
	if (count == 0) {
		io_AppendText(0x19af);
	}
	do {
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
		}
	} while (main_RunFrameLoop(d2_RunKerkerplanDialog, 0x677c7) != 0);
	d3_EndCameraAndUiMode();
	d2_DestroyForm(h);
}
