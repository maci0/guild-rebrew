


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
extern int g_100f1dc;
#include "Develop/DieGildeAddOn/game/game_data.h"
#include "client_dialog_state.h"

void __cdecl fcn_00533a60(int, int, int*, int, int, int);
void __cdecl fcn_00472640(int, int);
void __cdecl fcn_00471af0(int, int);
int __cdecl d2_ShowGraveyardConfirm(char*, int, unsigned char);
int __cdecl d2_RunRentGraveDialog(char*, int, unsigned char);
int __cdecl main_RunFrameLoop(void*, int);

void __cdecl d2_RunRentAGraveMenu(char* input, Req* s)
{
	int ids[2];
	int ok;
	int cancel;

	fcn_00533a60(s->x18, 0, ids, 2, g_14b5780, g_14b5784);
	ok = ids[0];
	cancel = ids[1];
	if (*s->x1c == 3) {
		fcn_00472640(cancel, 0);
	}
	g_100f1dc = -1;
	do {
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
		} else if (g_100f1dc != -1) {
			if (d2_CurrentElementId == ok) {
				fcn_00471af0(s->x0, 0);
				if (d2_ShowGraveyardConfirm(input, s->x20, s->x24) == 1) {
					g_774654 = 1;
				}
				fcn_00471af0(s->x0, 1);
			} else if (d2_CurrentElementId == cancel) {
				fcn_00471af0(s->x0, 0);
				if (d2_RunRentGraveDialog(input, s->x20, s->x24) == 1) {
					g_774654 = 1;
				}
				fcn_00471af0(s->x0, 1);
			}
		}
	} while (main_RunFrameLoop((void*) d2_RunRentAGraveMenu, 0x677c7) != 0);
}
