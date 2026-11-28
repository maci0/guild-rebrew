#include "Develop/DieGildeAddOn/game/game_data.h"
#include "Develop/Units/d2.v1/client_dialog_state.h"
extern int main_FrameHandlerStack[];

/* ADDRESS: GOLDTL 0x005356b0 */
/* ADDRESS: GOLDDE 0x0051df10 */
void __cdecl main_ExitToFrameHandler(int handler_fn)
{
	int i;

	for (i = g_774650; i >= 0; i--) {
		if (main_FrameHandlerStack[i * 2] == handler_fn) {
			d2_DialogCloseRequested = g_774650 - i;
			return;
		}
	}
}
