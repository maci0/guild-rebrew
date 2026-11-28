#include "Develop/DieGildeAddOn/game/game_data.h"
#include "Develop/Units/d2.v1/client_dialog_state.h"
extern int g_7e35c0[];

/* ADDRESS: GOLDTL 0x005356b0 */
void __cdecl main_ExitToFrameHandler(int handler_fn)
{
	int i;

	for (i = g_774650; i >= 0; i--) {
		if (g_7e35c0[i * 2] == handler_fn) {
			g_774654 = g_774650 - i;
			return;
		}
	}
}
