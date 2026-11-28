#include "Develop/client_types.h"
extern Slot_779d00 main_CameraBookmarks[];
extern Slot_779d00 main_CameraBookmarks[];
#include "Develop/DieGildeAddOn/game/game_data.h"
extern char io_ShiftKeyDown[];
extern char io_ShiftKeyDown[];
extern char io_LastKeyScancode;
extern char io_LastKeyScancode;



void __cdecl d2_RunGebHotkeysDialog(void);
void __cdecl d2_FocusBookmarkSlot(void);
void __cdecl d2_SaveBookmarkSlot(int);

void __cdecl main_ProcessGameHotkeys(void)
{
	char c;
	int i;
	char* e;

	c = *(char*) ((char*)&io_LastKeyScancode);
	if (c != 0 && *(int*) ((char*)&d2_InsideBuildingActive) != 1) {
		if (c == 0x58) {
			d2_RunGebHotkeysDialog();
		}
		d2_FocusBookmarkSlot();
		i = 0;
		for (e = ((char*)main_CameraBookmarks); (int) e < (int) main_CameraBookmarks + 0x84; e += 12) {
			if (*e == *(char*) ((char*)&io_LastKeyScancode) && *(char*) io_ShiftKeyDown != 0) {
				d2_SaveBookmarkSlot(i);
			}
			i++;
		}
	}
}
