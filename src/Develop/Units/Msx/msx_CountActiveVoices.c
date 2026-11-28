#include "Develop/client_types.h"

typedef SOUND_VOICE Voice;

extern char* g_6b7e88;
#include "Develop/DieGildeAddOn/game/game_data.h"
int __cdecl msx_GetSampleStatus(int h);

/* ADDRESS: GOLDTL 0x004258d0 */
int __cdecl msx_CountActiveVoices(void)
{
	int count;
	int i;

	count = 0;
	if (g_6b7e88 != 0) {
		for (i = 0; i < g_6b7e8c; i++) {
			if (((Voice*) g_6b7e88)[i].sample != 0) {
				if (msx_GetSampleStatus(((Voice*) g_6b7e88)[i].h) == 4) {
					count++;
				} else if (((Voice*) g_6b7e88)[i].f18 != 0 && ((Voice*) g_6b7e88)[i].loop != 1 &&
				    (((Voice*) g_6b7e88)[i].flags & 0xe) == 0) {
					count++;
				} else if ((((Voice*) g_6b7e88)[i].flags & 0x10) != 0) {
					count++;
				}
			}
		}
	}
	return count;
}
