


void __cdecl msx_CloseAllStreams(void);
void __cdecl msx_ReleaseAllWaveSamples(void);
void __cdecl msx_CloseAllWaveDrivers(void);
__declspec(dllimport) void __stdcall AIL_shutdown(void);
#include "Develop/DieGildeAddOn/game/game_data.h"

/* ADDRESS: GOLDDE 0x00424a40 */
int __cdecl msx_ShutdownAIL(void)
{
	int r = 0;

	if (msx_Initialized != 0) {
		msx_CloseAllStreams();
		msx_ReleaseAllWaveSamples();
		msx_CloseAllWaveDrivers();
		AIL_shutdown();
		msx_Initialized = r;
	} else {
		r = -1;
	}
	return r;
}
