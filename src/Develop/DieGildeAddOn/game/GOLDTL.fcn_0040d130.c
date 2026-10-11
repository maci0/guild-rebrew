#include <string.h>

extern char* g_6b7ebc;
extern char* g_6b7e98;
extern int g_6791c8;

void __cdecl fcn_0040d0f0();
char* __cdecl fcn_0040c230(char*, void (__cdecl*)(), unsigned char, int, ...);
void __cdecl fcn_00425bf0(char*, int, const char*);
void __cdecl fcn_0041d9e0(const char*);

// FUNCTION: GOLD 0x0040c210
// FUNCTION: GOLDTL 0x40d130

/* PlayCharacterAniScriptInt(): like PlayCharacterAniScript() with an
 * integer parameter handed to the script. */
int __cdecl PlayCharacterAniScriptInt(char** ch, char** script, int* kind, unsigned char* level, char** func, int* param)
{
	char* task;

	if (g_6b7ebc != 0 && *(int (__cdecl**)()) (g_6b7ebc + 0x44) == (int (__cdecl*)()) PlayCharacterAniScriptInt) {
		if (*(int*) (*ch + 0x128) != 0) {
			*(int (__cdecl**)()) (g_6b7e98 + 0xc60) = (int (__cdecl*)()) PlayCharacterAniScriptInt;
		}
		return 0;
	}
	if (*ch == 0) {
		fcn_00425bf0(g_6b7e98, *(int*) (g_6b7e98 + 0x118), "PlayCharacterAniScriptInt(): invalid character");
		return 1;
	}
	task = fcn_0040c230(*ch, fcn_0040d0f0, *level, 0x2e, *kind);
	if (task != 0) {
		if (strlen(*script) >= 0x5f) {
			fcn_0041d9e0("PlayCharacterAniScript(): script name too long");
			return 1;
		}
		strncpy(task + 0xf0, *script, 0x3f);
		strncpy(task + 0x90, *func, 0x5f);
		*(int*) (task + 0x17c) = g_6791c8;
		*(int*) (task + 0x180) = *param;
	}
	if (*(int*) (g_6b7e98 + 0xc84) == 1) {
		*(int (__cdecl**)()) (g_6b7e98 + 0xc60) = (int (__cdecl*)()) PlayCharacterAniScriptInt;
	}
	return 0;
}
