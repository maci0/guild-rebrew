#include "Develop/DieGildeAddOn/game/client_timer.h"

int __cdecl tb_SetCallbackPaused(TIMER_CALLBACK callback, int paused)
{
	int i;
	TIMER_CALLBACK_SLOT* a;

	/* Native uses a signed address comparison; the cursor stays a pointer. */
	for (i = 0, a = g_1052c60; (int) a < (int) (g_1052c60 + 32); a++, i++) {
		if (a->funktion == callback) {
			g_1052c60[i].pausiert = paused;
			return 1;
		}
	}
	return 0;
}
