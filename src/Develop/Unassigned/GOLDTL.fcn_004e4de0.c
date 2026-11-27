


extern volatile int g_6b7fac;
extern int g_772f3c;
#include "Develop/DieGildeAddOn/game/game_data.h"
#include "client_dialog_state.h"

int __cdecl main_RunFrameLoop(void*, int);
void __cdecl fcn_004cfca0(void);
void __cdecl d2_AppendPendingPlayerNames(int);

void __cdecl cut_WaitSeconds(int secs)
{
	int start;
	double end;

	start = (*(unsigned int*)&g_6b7fac);
	if (g_772f3c != 0)
		return;
	if (main_RunFrameLoop(cut_WaitSeconds, cut_EventLoopFlags | 0x8000) == 0)
		return;
	end = secs * (1.0 / 14.0) + start;
	do {
		if ((*(unsigned int*)&g_6b7fac) >= end)
			g_774654 = 1;
		fcn_004cfca0();
		d2_AppendPendingPlayerNames((*(int*)&cut_ActiveCutscene));
	} while (main_RunFrameLoop(cut_WaitSeconds, cut_EventLoopFlags | 0x8000) != 0);
}
