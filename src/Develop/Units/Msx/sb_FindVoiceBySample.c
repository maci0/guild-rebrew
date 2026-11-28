extern int sb_WaveDriver;

// SIZE 0x30
typedef struct {
	int a;
	int key;
	char pad[0x28];
} VOICE_ENTRY;

#include "Develop/client_types.h"
extern SOUND_VOICE sb_DummyVoice;
extern char* sb_Voices;
#include "Develop/DieGildeAddOn/game/game_data.h"


/* ADDRESS: GOLD 0x004262f0 */
/* ADDRESS: GOLDTL 0x00422760 */
/* ADDRESS: GOLDDE 0x0041f5e0 */
VOICE_ENTRY* __cdecl sb_FindVoiceBySample(int key, int* idx)
{
	VOICE_ENTRY* result = 0;
	VOICE_ENTRY* voices;
	int i;
	int count;

	if (sb_WaveDriver == 0) {
		return &(*(VOICE_ENTRY*)&sb_DummyVoice);
	}
	voices = ((VOICE_ENTRY*)sb_Voices);
	if (voices != 0) {
		count = sb_VoiceCount;
		for (i = *idx; i < count; i++) {
			if (voices[i].key == key) {
				*idx = i;
				result = &voices[i];
				break;
			}
		}
	}
	return result;
}
