typedef struct ACTIVE_VOICE_NODE ACTIVE_VOICE_NODE;
struct ACTIVE_VOICE_NODE {
	int* f0;
	int f4;
	int f8;
	ACTIVE_VOICE_NODE* next;
};
// SIZE 0x10

#include "Develop/DieGildeAddOn/game/game_data.h"

void __cdecl d3snd_SetVoiceFlag0x10(int*, int);
void __cdecl m_FreeTracked(void*);


/* ADDRESS: GOLDTL 0x004c0a10 */
void __cdecl d3snd_RemoveActiveVoice(int* key)
{
	ACTIVE_VOICE_NODE* prev;
	ACTIVE_VOICE_NODE* p;

	prev = 0;
	for (p = (*(ACTIVE_VOICE_NODE**)&g_772d34); p != 0; p = p->next) {
		if (p->f0 == key) {
			if (prev != 0)
				prev->next = p->next;
			else
				(*(ACTIVE_VOICE_NODE**)&g_772d34) = p->next;
			d3snd_SetVoiceFlag0x10(p->f0, 0);
			m_FreeTracked(p);
			return;
		}
		prev = p;
	}
}
