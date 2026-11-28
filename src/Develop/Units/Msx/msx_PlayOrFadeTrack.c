#include "Develop/Units/Msx/client_sound.h"
#include "Develop/Units/Msx/msx.h"



#include "Develop/DieGildeAddOn/game/game_data.h"
extern float g_6819b0;
extern float flt_0_0;

void __cdecl msx_FadeMasterVolumeIfTrackActive(float, int);

void __cdecl msx_PlayOrFadeTrack(char* snd)
{
	if (msx_MusicEnabled != 0 && g_6819b0 != flt_0_0) {
		if (snd != 0) {
			if (tp_msx_CurrentTrack != 0)
				msx_StopTrack(tp_msx_CurrentTrack, 1);
			tp_msx_CurrentTrack = tp_msx_MusicTrack = msx_StartTrack(snd, 0);
		} else {
			msx_FadeMasterVolumeIfTrackActive(0.4f, 2000);
		}
	}
}
