#include "Develop/Units/Msx/client_sound.h"

extern int msx_SavedTrackState;
extern int d3snd_AmbientEnabled;
extern int msx_MusicOverrideActive;
extern int msx_MusicEnabled;

void __cdecl msx_FadeMasterVolumeIfTrackActive(float, int);


/* ADDRESS: GOLDTL 0x004c2d50 */
/* ADDRESS: GOLDDE 0x004b0800 */
void __cdecl msx_RestoreMusicVolume(void)
{
	msx_MusicOverrideActive = 0;
	(*(char*)&d3snd_AmbientEnabled) = (*(char*)&msx_SavedTrackState);
	if (msx_MusicEnabled != 0 && tp_msx_CurrentTrack != tp_msx_MusicTrack)
		msx_FadeMasterVolumeIfTrackActive(1.0f, 3000);
}
