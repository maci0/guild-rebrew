


// SIZE 0xc
#include "Develop/client_types.h"
typedef Slot_779d00 Slot;

extern Slot_779d00 main_CameraBookmarks[];
#include "Develop/DieGildeAddOn/game/game_player.h"

int __cdecl gm_SearchTable67(int);
int __cdecl gm_FindRecordById(int);
char __cdecl gm_GetEntityUiFlags(int, int, int, int);
void __cdecl d2_ClearBookmarkSlot(Slot*);

/* ADDRESS: GOLDDE 0x00577930 */
void __cdecl d2_PruneBookmarkSlots(void)
{
	int i;
	int x;
	int r;

	for (i = 0; i < 11; i++) {
		if (main_CameraBookmarks[i].b != -1) {
			x = gm_SearchTable67(main_CameraBookmarks[i].b);
			if (x == 0) {
				d2_ClearBookmarkSlot(&main_CameraBookmarks[i]);
			}
			else {
				r = gm_FindRecordById(main_CameraBookmarks[i].c);
				if (r == 0 && main_CameraBookmarks[i].c != -1) {
					d2_ClearBookmarkSlot(&main_CameraBookmarks[i]);
				}
				else if (!(gm_GetEntityUiFlags(gm_LocalPlayerSlot, x, r, 0) & 1)) {
					d2_ClearBookmarkSlot(&main_CameraBookmarks[i]);
				}
			}
		}
	}
}
unsigned char _dpad_779d00[16544];
