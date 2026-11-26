


extern int g_100f1dc;
#include "Develop/DieGildeAddOn/game/game_data.h"
#include "client_dialog_state.h"

int __cdecl main_RunFrameLoop(void*, int);
void __cdecl fcn_00471af0(int, int);
int __cdecl d2_OpenSeanceDialog(int, char*, int);

int __cdecl d2_RunSeanceMenu(int entity, char* s, int resultOut)
{
	int r;
	int i;

	r = 0;
	g_100f1dc = -1;
	do {
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
		}
		else if (g_100f1dc != -1) {
			for (i = 0; i < 8; i++) {
				if (d2_CurrentElementId == *(int*) (s + 0x28 + i * 0xc)) {
					*(int*) (s + 0x88) = i;
					fcn_00471af0(*(int*) s, 0);
					r = d2_OpenSeanceDialog(entity, s, resultOut);
					fcn_00471af0(*(int*) s, 1);
					break;
				}
			}
			if (r != 0) {
				r = 1;
				g_774654 = 1;
			}
		}
	} while (main_RunFrameLoop(d2_RunSeanceMenu, 0x677c7) != 0);
	return r;
}
