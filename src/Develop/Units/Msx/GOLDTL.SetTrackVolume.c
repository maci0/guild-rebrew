#include "msx.h"

void __cdecl SetTrackVolume(const char* name, int volume)
{
	Chan_14cc460* p;

	if (msx_TrackDriver != 0) {
		EnterCriticalSection(&msx_TrackLock);
		p = FindTrackByName(name);
		if (p != 0) {
			fcn_0041fc10(p, volume);
		}
		LeaveCriticalSection(&msx_TrackLock);
	}
}
