typedef struct
{
	char pad[0x100];
	int id;
	int state;
	char mid[0x1c];
	unsigned char flags;
	char tail[0xb73];
} Obj;
// SIZE 0xc98

#include "Develop/DieGildeAddOn/game/game_data.h"

int __cdecl main_RunFrameLoop(int, int);

static __inline int any_pending(void)
{
	int i;

	for (i = 0; i < 128; i++) {
		if (((Obj*)evt_ScriptSlots)[i].id != -1 && ((Obj*)evt_ScriptSlots)[i].state == -2) {
			return 1;
		}
	}
	return 0;
}


/* ADDRESS: GOLDTL 0x004e4680 */
void __cdecl cut_WaitForPendingScripts(void)
{
	while (main_RunFrameLoop(0, 0x79706) != 0) {
		if (!any_pending()) {
			return;
		}
	}
}
