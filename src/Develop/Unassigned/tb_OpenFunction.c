#include "Develop/DieGildeAddOn/game/client_timer.h"
extern char g_679e00[];
#include "Develop/Units/Error/error_message.h"

int __cdecl tb_OpenFunction(TIMER_CALLBACK a, unsigned int b)
{
	int i;

	i = 0;
	while (tb_TimerCallbacks[i++].funktion != 0 && i < 32) {
	}
	if (i > 32) {
		ReportClientMessage(g_679e00);
		return 0;
	}
	i--;
	tb_TimerCallbacks[i].funktion = a;
	tb_TimerCallbacks[i].periode = b;
	tb_TimerCallbacks[i].pausiert = 0;
	return 1;
}
