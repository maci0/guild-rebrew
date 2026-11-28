#include "Develop/client_types.h"

typedef SOUND_VOICE Voice;

extern char* sb_Voices;
#include "Develop/DieGildeAddOn/game/game_data.h"
int __cdecl msx_GetSampleStatus(int h);

/* ADDRESS: GOLDTL 0x004258d0 */
int __cdecl msx_CountActiveVoices(void)
{
	int count;
	int i;

	count = 0;
	if (sb_Voices != 0) {
		for (i = 0; i < sb_VoiceCount; i++) {
			if (((Voice*) sb_Voices)[i].sample != 0) {
				if (msx_GetSampleStatus(((Voice*) sb_Voices)[i].h) == 4) {
					count++;
				} else if (((Voice*) sb_Voices)[i].f18 != 0 && ((Voice*) sb_Voices)[i].loop != 1 &&
				    (((Voice*) sb_Voices)[i].flags & 0xe) == 0) {
					count++;
				} else if ((((Voice*) sb_Voices)[i].flags & 0x10) != 0) {
					count++;
				}
			}
		}
	}
	return count;
}
