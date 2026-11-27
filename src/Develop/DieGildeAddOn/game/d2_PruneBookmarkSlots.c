


// SIZE 0xc
#include "client_types.h"
typedef Slot_779d00 Slot;

extern Slot_779d00 g_779d00[];
#include "Develop/DieGildeAddOn/game/game_player.h"

int __cdecl gm_SearchTable67(int);
int __cdecl gm_FindRecordById(int);
char __cdecl gm_GetEntityUiFlags(int, int, int, int);
void __cdecl d2_ClearBookmarkSlot(Slot*);

void __cdecl d2_PruneBookmarkSlots(void)
{
	int i;
	int x;
	int r;

	for (i = 0; i < 11; i++) {
		if (g_779d00[i].b != -1) {
			x = gm_SearchTable67(g_779d00[i].b);
			if (x == 0) {
				d2_ClearBookmarkSlot(&g_779d00[i]);
			}
			else {
				r = gm_FindRecordById(g_779d00[i].c);
				if (r == 0 && g_779d00[i].c != -1) {
					d2_ClearBookmarkSlot(&g_779d00[i]);
				}
				else if (!(gm_GetEntityUiFlags(g_774970, x, r, 0) & 1)) {
					d2_ClearBookmarkSlot(&g_779d00[i]);
				}
			}
		}
	}
}
unsigned char _dpad_779d00[16544];
