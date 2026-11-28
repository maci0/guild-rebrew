#include "Develop/client_types.h"
extern Slot_779d00 g_779d00[];
extern Slot_779d00 g_779d00[];
#include "Develop/DieGildeAddOn/game/game_data.h"
extern char g_14cf72a[];
extern char g_14cf72a[];
extern char g_14cf950;
extern char g_14cf950;



void __cdecl d2_RunGebHotkeysDialog(void);
void __cdecl d2_FocusBookmarkSlot(void);
void __cdecl d2_SaveBookmarkSlot(int);

void __cdecl main_ProcessGameHotkeys(void)
{
	char c;
	int i;
	char* e;

	c = *(char*) ((char*)&g_14cf950);
	if (c != 0 && *(int*) ((char*)&g_7e2700) != 1) {
		if (c == 0x58) {
			d2_RunGebHotkeysDialog();
		}
		d2_FocusBookmarkSlot();
		i = 0;
		for (e = ((char*)g_779d00); (int) e < (int) g_779d00 + 0x84; e += 12) {
			if (*e == *(char*) ((char*)&g_14cf950) && *(char*) g_14cf72a != 0) {
				d2_SaveBookmarkSlot(i);
			}
			i++;
		}
	}
}
