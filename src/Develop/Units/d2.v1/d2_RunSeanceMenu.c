


extern int d2_DialogButtonAction;
#include "Develop/DieGildeAddOn/game/game_data.h"
#include "Develop/Units/d2.v1/client_dialog_state.h"

int __cdecl main_RunFrameLoop(void*, int);
void __cdecl d2_SetFormVisibility(int, int);
int __cdecl d2_OpenSeanceDialog(int, char*, int);

/* ADDRESS: GOLDDE 0x00574a80 */
int __cdecl d2_RunSeanceMenu(int entity, char* s, int resultOut)
{
	int r;
	int i;

	r = 0;
	d2_DialogButtonAction = -1;
	do {
		if (io_RightButtonReleased != 0) {
			d2_DialogCloseRequested = 1;
		}
		else if (d2_DialogButtonAction != -1) {
			for (i = 0; i < 8; i++) {
				if (d2_CurrentElementId == *(int*) (s + 0x28 + i * 0xc)) {
					*(int*) (s + 0x88) = i;
					d2_SetFormVisibility(*(int*) s, 0);
					r = d2_OpenSeanceDialog(entity, s, resultOut);
					d2_SetFormVisibility(*(int*) s, 1);
					break;
				}
			}
			if (r != 0) {
				r = 1;
				d2_DialogCloseRequested = 1;
			}
		}
	} while (main_RunFrameLoop(d2_RunSeanceMenu, 0x677c7) != 0);
	return r;
}
