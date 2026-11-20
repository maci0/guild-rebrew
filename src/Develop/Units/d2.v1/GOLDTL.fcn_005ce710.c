


#include "Develop/DieGildeAddOn/game/game_data.h"
#include "client_dialog_state.h"
extern char g_6aca14[];

int __cdecl fcn_00470820(int, int, char*);
void __cdecl d2_CenterDialogWindows(int);
void __cdecl d2_SetForm(int, int);
void __cdecl fcn_005340f0(int);
void __cdecl d2_SetOverlayAnimation(int, int);
int __cdecl io_AppendText(char*, ...);
int __cdecl fcn_005373e0(void*, int);
void __cdecl fcn_00471e30(int);

void __cdecl d2_RunGesetzbuchInfoDialog(int textId, int value)
{
	int h;

	h = fcn_00470820(0, 0, g_6aca14);
	d2_CenterDialogWindows(h);
	d2_SetForm(h, 1);
	io_AppendText((char*) (textId + 1), textId, value);
	d2_SetForm(h, 2);
	io_AppendText((char*) (textId + 2));
	do {
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
		}
	} while (fcn_005373e0(d2_RunGesetzbuchInfoDialog, 0x677c7) != 0);
	fcn_00471e30(h);
}
