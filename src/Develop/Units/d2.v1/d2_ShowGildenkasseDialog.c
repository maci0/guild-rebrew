


extern unsigned char gm_ActiveTownIndex;
#include "Develop/DieGildeAddOn/game/game_data.h"
#include "Develop/Units/d2.v1/client_dialog_state.h"
extern char g_6aae08[];

char* __cdecl gm_QueryEntities(int, int, int, int, int);
int __cdecl gm_SumQueryEntryValues(int, char);
int __cdecl d2_LoadForm(int, int, char*);
void __cdecl d2_CenterDialogWindows(int);
void __cdecl d2_SetForm(int, int);
int __cdecl io_AppendText(int, ...);
int __cdecl main_RunFrameLoop(void*, int);
void __cdecl d3_EndCameraAndUiMode(void);
void __cdecl d2_DestroyForm(int);

/* ADDRESS: GOLDDE 0x0058db80 */
void __cdecl d2_ShowGildenkasseDialog(char* e)
{
	char* r;
	int v;
	int h;

	r = gm_QueryEntities(*(int*) (e + 0x5d), 2, 6, 0, 0x115);
	v = gm_SumQueryEntryValues(*(int*) (r + 0x14), (*(char*)&gm_ActiveTownIndex));
	h = d2_LoadForm(0, 0, g_6aae08);
	d2_CenterDialogWindows(h);
	d2_SetForm(h, 1);
	io_AppendText(0x1a0f, v);
	while (main_RunFrameLoop(d2_ShowGildenkasseDialog, 0x677c7) != 0) {
		if (io_RightButtonReleased != 0) {
			d2_DialogCloseRequested = 1;
		}
	}
	d3_EndCameraAndUiMode();
	d2_DestroyForm(h);
}
