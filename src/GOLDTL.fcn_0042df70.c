#include "client_timer.h"

int __cdecl fcn_0042df70(TIMER_CALLBACK a1)
{
	int i;
	TIMER_CALLBACK_SLOT* a;

	/* Native uses a signed address comparison; the cursor stays a pointer. */
	for (i = 0, a = g_1052c60; (int) a < (int) (g_1052c60 + 32); a++, i++) {
		if (a->funktion == a1) {
			return g_1052c60[i].pausiert != 0;
		}
	}
	return 0;
}
