#include "msx.h"

void __cdecl StopTrackByName(const char* name, int a2)
{
	Chan_14cc460* p;

	if (msx_TrackDriver != 0) {
		EnterCriticalSection(&msx_TrackLock);
		p = FindTrackByName(name);
		LeaveCriticalSection(&msx_TrackLock);
		if (p != 0) {
			msx_StopTrack(p, a2);
		}
	}
}
