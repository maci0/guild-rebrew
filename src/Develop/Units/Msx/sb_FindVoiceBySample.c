extern int g_6b7d7c;

// SIZE 0x30
typedef struct {
	int a;
	int key;
	char pad[0x28];
} VOICE_ENTRY;

#include "client_types.h"
extern SOUND_VOICE g_14cbbe0;
extern char* g_6b7e88;
#include "Develop/DieGildeAddOn/game/game_data.h"


/* ADDRESS: GOLD 0x004262f0 */
/* ADDRESS: GOLDTL 0x00422760 */
VOICE_ENTRY* __cdecl sb_FindVoiceBySample(int key, int* idx)
{
	VOICE_ENTRY* result = 0;
	VOICE_ENTRY* voices;
	int i;
	int count;

	if (g_6b7d7c == 0) {
		return &(*(VOICE_ENTRY*)&g_14cbbe0);
	}
	voices = ((VOICE_ENTRY*)g_6b7e88);
	if (voices != 0) {
		count = g_6b7e8c;
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
