typedef struct TRACKED_VOICE_NODE TRACKED_VOICE_NODE;
struct TRACKED_VOICE_NODE {
	int* f0;
	int f4;
	int f8;
	TRACKED_VOICE_NODE* next;
};
// SIZE 0x10

extern int g_772d2c;
#include "Develop/DieGildeAddOn/game/game_data.h"

void __cdecl msx_FadeMasterVolumeIfTrackActive(float, int);
void __cdecl d3snd_SetVoiceFlag0x10(int*, int);
void __cdecl m_FreeTracked(void*);


/* ADDRESS: GOLDTL 0x004c09b0 */
/* ADDRESS: GOLDDE 0x004ae530 */
void __cdecl d3snd_StopTrackedVoices(void)
{
	TRACKED_VOICE_NODE* next;

	if (g_772d2c != 0) {
		g_772d2c = 0;
		msx_FadeMasterVolumeIfTrackActive(1.0f, 2000);
	}
	while ((*(TRACKED_VOICE_NODE**)&g_772d34) != 0) {
		next = (*(TRACKED_VOICE_NODE**)&g_772d34)->next;
		d3snd_SetVoiceFlag0x10((*(TRACKED_VOICE_NODE**)&g_772d34)->f0, 0);
		m_FreeTracked((*(TRACKED_VOICE_NODE**)&g_772d34));
		(*(TRACKED_VOICE_NODE**)&g_772d34) = next;
	}
}
