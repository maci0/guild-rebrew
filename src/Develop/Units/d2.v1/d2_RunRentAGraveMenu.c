


typedef struct
{
	int x0;
	char pad4[0x14];
	int x18;
	int* x1c;
	int x20;
	unsigned char x24;
} Req;
// SIZE 0x28

extern int g_14b5780;
extern int g_14b5784;
extern int d2_DialogButtonAction;
#include "Develop/DieGildeAddOn/game/game_data.h"
#include "Develop/Units/d2.v1/client_dialog_state.h"

void __cdecl d2_CreateButtonRow(int, int, int*, int, int, int);
void __cdecl d2_SetElementEnabled(int, int);
void __cdecl d2_SetFormVisibility(int, int);
int __cdecl d2_ShowGraveyardConfirm(char*, int, unsigned char);
int __cdecl d2_RunRentGraveDialog(char*, int, unsigned char);
int __cdecl main_RunFrameLoop(void*, int);

/* ADDRESS: GOLDDE 0x00572950 */
void __cdecl d2_RunRentAGraveMenu(char* input, Req* s)
{
	int ids[2];
	int ok;
	int cancel;

	d2_CreateButtonRow(s->x18, 0, ids, 2, g_14b5780, g_14b5784);
	ok = ids[0];
	cancel = ids[1];
	if (*s->x1c == 3) {
		d2_SetElementEnabled(cancel, 0);
	}
	d2_DialogButtonAction = -1;
	do {
		if (io_RightButtonReleased != 0) {
			d2_DialogCloseRequested = 1;
		} else if (d2_DialogButtonAction != -1) {
			if (d2_CurrentElementId == ok) {
				d2_SetFormVisibility(s->x0, 0);
				if (d2_ShowGraveyardConfirm(input, s->x20, s->x24) == 1) {
					d2_DialogCloseRequested = 1;
				}
				d2_SetFormVisibility(s->x0, 1);
			} else if (d2_CurrentElementId == cancel) {
				d2_SetFormVisibility(s->x0, 0);
				if (d2_RunRentGraveDialog(input, s->x20, s->x24) == 1) {
					d2_DialogCloseRequested = 1;
				}
				d2_SetFormVisibility(s->x0, 1);
			}
		}
	} while (main_RunFrameLoop((void*) d2_RunRentAGraveMenu, 0x677c7) != 0);
}
