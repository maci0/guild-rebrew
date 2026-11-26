#include "Develop/DieGildeAddOn/game/entity_record.h"

typedef struct
{
	int x0;
	int x4;
	char pad8[0xc];
} Req;
// SIZE 0x14

extern int d2_CurrentWindowId;
#include "Develop/DieGildeAddOn/game/game_player.h"
extern char g_7f4ca0[];
extern int g_14ce8e0;
#include "client_dialog_state.h"
extern int g_100f1dc;
extern char s_6aaf90[];

int __cdecl fcn_00470820(int, int, char*);
void __cdecl d2_CenterDialogWindows(int);
void __cdecl d2_SetOverlayAnimation(int, int);
void __cdecl d2_SetForm(int, int);
void __cdecl fcn_005340f0(int);
int __cdecl io_AppendText(int, ...);
void __cdecl fcn_004eba60(char*, Req*);
int __cdecl main_RunFrameLoop(void*, int);
void __cdecl d2_DestroyForm(int);

void __cdecl fcn_005aa9a0(int a1)
{
	Req s;
	int dlg;
	int titleId;

	dlg = fcn_00470820(0, 0, s_6aaf90);
	d2_CenterDialogWindows(dlg);
	d2_SetOverlayAnimation(0, 0);
	d2_SetForm(dlg, 0);
	fcn_005340f0(d2_CurrentWindowId);
	d2_SetForm(dlg, 1);
	io_AppendText(0x166a);
	d2_SetForm(dlg, 2);
	if (((char *)&((ENTITY_RECORD_VIEW *)g_7f4ca0)[g_774970])[9] == 0) {
		titleId = (unsigned char) ((char *)&((ENTITY_RECORD_VIEW *)g_7f4ca0)[g_774970])[0x169] + 0x253;
	} else {
		titleId = (unsigned char) ((char *)&((ENTITY_RECORD_VIEW *)g_7f4ca0)[g_774970])[0x169] + 0x27b;
	}
	io_AppendText(0x166d, titleId, 8, a1 + 0x1663);
	do {
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
		}
		if (g_100f1dc == 2) {
			s.x0 = 4;
			s.x4 = a1;
			fcn_004eba60(((char *)&((ENTITY_RECORD_VIEW *)g_7f4ca0)[g_774970]), &s);
			g_774654 = 2;
		} else if (g_100f1dc == 1) {
			g_774654 = 1;
		}
	} while (main_RunFrameLoop((void*) fcn_005aa9a0, 0x677c7) != 0);
	d2_DestroyForm(dlg);
}
