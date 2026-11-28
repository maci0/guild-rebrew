#include "Develop/Units/Msx/client_sound.h"

extern int g_772d14;
extern int g_772d10;
extern int g_772d28;
extern int msx_MusicEnabled;

void __cdecl msx_FadeMasterVolumeIfTrackActive(float, int);


/* ADDRESS: GOLDTL 0x004c2d50 */
void __cdecl msx_RestoreMusicVolume(void)
{
	g_772d28 = 0;
	(*(char*)&g_772d10) = (*(char*)&g_772d14);
	if (msx_MusicEnabled != 0 && tp_msx_CurrentTrack != g_772d24)
		msx_FadeMasterVolumeIfTrackActive(1.0f, 3000);
}
