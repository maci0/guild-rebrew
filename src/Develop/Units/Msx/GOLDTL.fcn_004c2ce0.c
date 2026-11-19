#include "client_sound.h"
#include "Develop/Units/Msx/msx.h"



#include "Develop/DieGildeAddOn/game/game_data.h"
extern float g_6819b0;
extern float g_6628a8;

void __cdecl fcn_004c24c0(float, int);

void __cdecl fcn_004c2ce0(char* snd)
{
	if (msx_MusicEnabled != 0 && g_6819b0 != g_6628a8) {
		if (snd != 0) {
			if (tp_msx_CurrentTrack != 0)
				msx_StopTrack(tp_msx_CurrentTrack, 1);
			tp_msx_CurrentTrack = g_772d24 = msx_StartTrack(snd, 0);
		} else {
			fcn_004c24c0(0.4f, 2000);
		}
	}
}
