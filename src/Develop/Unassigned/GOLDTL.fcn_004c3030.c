


#include "Develop/DieGildeAddOn/game/game_data.h"
extern float g_681750;
extern float g_664e80;

int __cdecl fcn_004c2de0(int, int, int, int);
void __cdecl fcn_00423670(int, int, int);
void __cdecl sb_SetVoiceVolume(int, int);

int __cdecl d3snd_PlaySoundEffect(int a, int b, int c, int d)
{
	int h;

	if (g_774934 == 0)
		return 0;
	if (g_772d34 != 0 && *(int*) (g_772d34 + 8) != 0)
		return 0;
	h = fcn_004c2de0(a, b, c, d);
	if (h != 0) {
		fcn_00423670(h, 0, 0);
		sb_SetVoiceVolume(h, (int) (g_681750 * g_664e80));
	}
	return h;
}
