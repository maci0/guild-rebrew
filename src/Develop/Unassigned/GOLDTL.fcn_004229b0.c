


// SIZE 0x30
#include "client_types.h"
typedef SOUND_VOICE Voice;

extern int g_6b7d7c;
extern SOUND_VOICE g_14cbbe0;
extern char* g_6b7e88;
#include "Develop/DieGildeAddOn/game/game_data.h"
int __cdecl msx_GetSampleStatus(int h);
void __cdecl msx_InitSample(int h);

Voice* __cdecl sb_AllocVoice(void)
{
	Voice* best;
	int i;

	best = 0;
	if (g_6b7d7c == 0) {
		return &g_14cbbe0;
	}
	if (((Voice*)g_6b7e88) != 0) {
		for (i = 0; i < g_6b7e8c; i++) {
			if (msx_GetSampleStatus(((Voice*)g_6b7e88)[i].h) != 4 && (((Voice*)g_6b7e88)[i].flags & 0x10) == 0) {
				best = &((Voice*)g_6b7e88)[i++];
				break;
			}
		}
		if (best != 0) {
			for (; i < g_6b7e8c; i++) {
				if (((Voice*)g_6b7e88)[i].prio < best->prio && msx_GetSampleStatus(((Voice*)g_6b7e88)[i].h) != 4 &&
				    (((Voice*)g_6b7e88)[i].flags & 0x10) == 0) {
					best = &((Voice*)g_6b7e88)[i];
				}
			}
			msx_InitSample(best->h);
			best->flags = 0;
			best->f18 = 0;
			best->loop = 1;
		}
	}
	return best;
}
#if defined(REBREW_SERVER) || defined(REBREW_GOLD)
unsigned char _dpad_6b7d7c[268];
#else
/* Reference gaps only; the emitted objects inside the span keep their own rows. */
unsigned char _dpad_6b7d8c[252];
#endif
