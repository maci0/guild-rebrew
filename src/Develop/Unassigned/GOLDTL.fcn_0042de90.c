#include "client_timer.h"
extern char g_679e00[];
#include "Develop/Units/Error/error_message.h"

int __cdecl tb_OpenFunction(TIMER_CALLBACK a, unsigned int b)
{
	int i;

	i = 0;
	while (g_1052c60[i++].funktion != 0 && i < 32) {
	}
	if (i > 32) {
		fcn_0041d9e0(g_679e00);
		return 0;
	}
	i--;
	g_1052c60[i].funktion = a;
	g_1052c60[i].periode = b;
	g_1052c60[i].pausiert = 0;
	return 1;
}
