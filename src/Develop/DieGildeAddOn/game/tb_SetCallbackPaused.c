#include "Develop/DieGildeAddOn/game/client_timer.h"

/* ADDRESS: GOLDDE 0x00427d00 */
int __cdecl tb_SetCallbackPaused(TIMER_CALLBACK callback, int paused)
{
	int i;
	TIMER_CALLBACK_SLOT* a;

	/* Native uses a signed address comparison; the cursor stays a pointer. */
	for (i = 0, a = tb_TimerCallbacks; (int) a < (int) (tb_TimerCallbacks + 32); a++, i++) {
		if (a->funktion == callback) {
			tb_TimerCallbacks[i].pausiert = paused;
			return 1;
		}
	}
	return 0;
}
