


extern volatile int g_6b7fac;
extern int g_772f3c;
#include "Develop/DieGildeAddOn/game/game_data.h"
#include "client_dialog_state.h"

int __cdecl fcn_005373e0(void*, int);
void __cdecl fcn_004cfca0(void);
void __cdecl d2_AppendPendingPlayerNames(int);
void __cdecl fcn_004e4de0(int);

int __cdecl cut_WaitForTimeoutOrInput(int secs, int(__cdecl* cb)(int), int arg)
{
	int start;
	int res;

	start = (*(unsigned int*)&g_6b7fac);
	res = 0;
	if (g_772f3c != 0)
		return 0;
	if (fcn_005373e0(fcn_004e4de0, cut_EventLoopFlags | 0x8000) != 0) {
		do {
			if (g_14ce8e0 != 0) {
				if (cb != 0)
					res = cb(arg);
				else
					res = 1;
				g_774654 = 1;
			} else if ((*(unsigned int*)&g_6b7fac) >= secs * (1.0 / 14.0) + start) {
				g_774654 = 1;
			}
			fcn_004cfca0();
			d2_AppendPendingPlayerNames((*(int*)&cut_ActiveCutscene));
		} while (fcn_005373e0(fcn_004e4de0, cut_EventLoopFlags | 0x8000) != 0);
	}
	return res;
}
