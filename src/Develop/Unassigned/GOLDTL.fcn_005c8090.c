#include "Develop/DieGildeAddOn/game/game_data.h"
#include "Develop/Units/d2.v1/client_dialog_state.h"
int __cdecl main_RunFrameLoop(void*, const char*);

/* ADDRESS: GOLDTL 0x005c8090 */
void __cdecl fcn_005c8090(void)
{
retry:
	if (io_RightButtonReleased != 0) {
		d2_DialogCloseRequested = 1;
	}
	if (main_RunFrameLoop((void*)fcn_005c8090, (const char*)0x677c7) != 0) {
		goto retry;
	}
}
