#include "Develop/DieGildeAddOn/game/ch_script.h"
#include <string.h>

extern char* g_6b7ebc;
extern char* g_6b7e98;

#include "../../../client_sound.h"
char* __cdecl fcn_0040c230(char*, void (__cdecl*)(), unsigned char, int, ...);
void __cdecl fcn_00425bf0(char*, int, const char*);

/* ADDRESS: GOLD 0x0040bfc0 */
/* ADDRESS: GOLDTL 0x0040cee0 */

/* PlayCharacterAniSound(): queues a character animation task with a sound;
 * the calling script waits for it when it blocks. */
int __cdecl PlayCharacterAniSound(char** ch, char** ani, int* kind, unsigned char* level, char** sound)
{
	char* task;

	if (g_6b7ebc != 0 && *(int (__cdecl**)()) (g_6b7ebc + 0x44) == (int (__cdecl*)()) PlayCharacterAniSound) {
		if (*(int*) (*ch + 0x128) != 0) {
			*(int (__cdecl**)()) (g_6b7e98 + 0xc60) = (int (__cdecl*)()) PlayCharacterAniSound;
		}
		return 0;
	}
	if (*ch == 0) {
		fcn_00425bf0(g_6b7e98, *(int*) (g_6b7e98 + 0x118), "PlayCharacterAniSound(): invalid character");
		return 1;
	}
	task = fcn_0040c230(*ch, (void (__cdecl*)())PlayEntitySound, *level, 0x2e, *kind);
	if (task != 0) {
		strcpy(task + 0xf0, *ani);
		strcpy(task + 0x130, *sound);
	}
	if (*(int*) (g_6b7e98 + 0xc84) == 1) {
		*(int (__cdecl**)()) (g_6b7e98 + 0xc60) = (int (__cdecl*)()) PlayCharacterAniSound;
	}
	return 0;
}
