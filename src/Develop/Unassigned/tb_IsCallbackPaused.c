#include "Develop/DieGildeAddOn/game/client_timer.h"

/* ADDRESS: GOLDDE 0x00427d40 */
int __cdecl tb_IsCallbackPaused(TIMER_CALLBACK cb)
{
	int i;
	TIMER_CALLBACK_SLOT* a;

	/* Native uses a signed address comparison; the cursor stays a pointer. */
	for (i = 0, a = tb_TimerCallbacks; (int) a < (int) (tb_TimerCallbacks + 32); a++, i++) {
		if (a->funktion == cb) {
			return tb_TimerCallbacks[i].pausiert != 0;
		}
	}
	return 0;
}
