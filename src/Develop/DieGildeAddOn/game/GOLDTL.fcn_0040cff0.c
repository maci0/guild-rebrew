#include "Develop/DieGildeAddOn/game/ch_script.h"
#include <string.h>

extern char* g_6b7ebc;
extern char* g_6b7e98;
extern int g_6791c8;

void __cdecl fcn_0040cfb0();
char* __cdecl fcn_0040c230(char*, void (__cdecl*)(), unsigned char, int, ...);
void __cdecl fcn_00425bf0(char*, int, const char*);


/* PlayCharacterAniScript(): queues a character animation task that runs a
 * script; the calling script waits for it when it blocks. */
/* ADDRESS: GOLDTL 0x0040cff0 */
int __cdecl PlayCharacterAniScript(char** ch, char** script, int* kind, unsigned char* level, char** func)
{
	char* task;

	if (g_6b7ebc != 0 && *(int (__cdecl**)()) (g_6b7ebc + 0x44) == (int (__cdecl*)()) PlayCharacterAniScript) {
		if (*(int*) (*ch + 0x128) != 0) {
			*(int (__cdecl**)()) (g_6b7e98 + 0xc60) = (int (__cdecl*)()) PlayCharacterAniScript;
		}
		return 0;
	}
	if (*ch == 0) {
		fcn_00425bf0(g_6b7e98, *(int*) (g_6b7e98 + 0x118), "PlayCharacterAniScript(): invalid character");
		return 1;
	}
	task = fcn_0040c230(*ch, fcn_0040cfb0, *level, 0x2e, *kind);
	if (task != 0) {
		if (strlen(*script) >= 0x5f) {
			fcn_00425bf0(g_6b7e98, *(int*) (g_6b7e98 + 0x118), "PlayCharacterAniScript(): script name too long");
			return 1;
		}
		strncpy(task + 0xf0, *script, 0x3f);
		strncpy(task + 0x90, *func, 0x5f);
		*(int*) (task + 0x17c) = g_6791c8;
	}
	if (*(int*) (g_6b7e98 + 0xc84) == 1) {
		*(int (__cdecl**)()) (g_6b7e98 + 0xc60) = (int (__cdecl*)()) PlayCharacterAniScript;
	}
	return 0;
}
