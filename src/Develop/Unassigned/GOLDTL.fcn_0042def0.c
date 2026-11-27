#include "client_timer.h"
/* ADDRESS: GOLDTL 0x0042def0 */
int __cdecl tb_CloseFunction(TIMER_CALLBACK callback)
{
	int i;
	TIMER_CALLBACK_SLOT* a;

	/* Native uses a signed address comparison; the cursor stays a pointer. */
	for (i = 0, a = g_1052c60; (int) a < (int) (g_1052c60 + 32); a++, i++) {
		if (a->funktion == callback) {
			g_1052c60[i].funktion = 0;
			return 1;
		}
	}
	return 0;
}
