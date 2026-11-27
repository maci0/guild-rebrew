


void __cdecl msx_CloseAllStreams(void);
void __cdecl msx_ReleaseAllWaveSamples(void);
void __cdecl msx_CloseAllWaveDrivers(void);
__declspec(dllimport) void __stdcall AIL_shutdown(void);
#include "Develop/DieGildeAddOn/game/game_data.h"

int __cdecl msx_ShutdownAIL(void)
{
	int r = 0;

	if (g_6b7f90 != 0) {
		msx_CloseAllStreams();
		msx_ReleaseAllWaveSamples();
		msx_CloseAllWaveDrivers();
		AIL_shutdown();
		g_6b7f90 = r;
	} else {
		r = -1;
	}
	return r;
}
