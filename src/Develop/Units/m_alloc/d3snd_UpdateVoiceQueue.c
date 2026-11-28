#include <string.h>
extern int g_772d18;
extern volatile int gm_GameTicks;
extern int g_772d2c;
extern unsigned int g_772d38;

struct D3SND_VOICE_NODE {
	char** voice;
	unsigned int delay;
	int started;
	struct D3SND_VOICE_NODE* next;
};
// SIZE 0x10

#include "Develop/DieGildeAddOn/game/game_data.h"

void __cdecl msx_FadeMasterVolumeIfTrackActive(float, int);
int __cdecl sb_StartVoice(char**, int, int);
int __cdecl sb_CheckVoicePlaying(char**);
void __cdecl d3snd_SetVoiceFlag0x10(char**, int);
void __cdecl m_FreeTracked(struct D3SND_VOICE_NODE*);


/* ADDRESS: GOLDTL 0x004c0b40 */
void __cdecl d3snd_UpdateVoiceQueue(void)
{
	struct D3SND_VOICE_NODE* cur;
	struct D3SND_VOICE_NODE* next;
	unsigned int now;
	int one;

	if (g_772d18 != 0)
		return;
	now = gm_GameTicks + (gm_GameTicks + gm_GameTicks * 2) * 4;
	cur = (*(struct D3SND_VOICE_NODE**)&g_772d34);
	if (cur == 0)
		return;
	if (cur->started == 0) {
		if (cur->delay < now - g_772d38) {
			if (cur->voice != 0 && cur->voice[1] != 0) {
				one = 1;
				if (strstr(cur->voice[1] + 4, "Fanfare") != 0 && g_772d2c == 0) {
					msx_FadeMasterVolumeIfTrackActive(0.0f, 0x7d0);
					g_772d2c = one;
				}
				sb_StartVoice((*(struct D3SND_VOICE_NODE**)&g_772d34)->voice, 0, 0);
				(*(struct D3SND_VOICE_NODE**)&g_772d34)->started = one;
				g_772d38 = now;
				return;
			}
			cur->started = 1;
			g_772d38 = now;
			return;
		}
	}
	if (cur->started == 0)
		return;
	if (sb_CheckVoicePlaying(cur->voice) != 0)
		return;
	next = (*(struct D3SND_VOICE_NODE**)&g_772d34)->next;
	d3snd_SetVoiceFlag0x10((*(struct D3SND_VOICE_NODE**)&g_772d34)->voice, 0);
	m_FreeTracked((*(struct D3SND_VOICE_NODE**)&g_772d34));
	(*(struct D3SND_VOICE_NODE**)&g_772d34) = next;
	g_772d38 = now;
	if (next != 0 && next->voice != 0 && next->voice[1] != 0 && g_772d2c != 0
	    && strstr(next->voice[1] + 4, "MausclickLinks") != 0) {
		next = (*(struct D3SND_VOICE_NODE**)&g_772d34)->next;
		d3snd_SetVoiceFlag0x10((*(struct D3SND_VOICE_NODE**)&g_772d34)->voice, 0);
		m_FreeTracked((*(struct D3SND_VOICE_NODE**)&g_772d34));
		(*(struct D3SND_VOICE_NODE**)&g_772d34) = next;
		msx_FadeMasterVolumeIfTrackActive(1.0f, 0x7d0);
		g_772d2c = 0;
	}
}
