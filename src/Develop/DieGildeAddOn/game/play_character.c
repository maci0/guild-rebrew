#include "Develop/DieGildeAddOn/game/ch_script.h"
#include <string.h>

extern char* g_6b7ebc;
extern char* evt_CurrentScript;

#include "../../../client_sound.h"
char* __cdecl ch_CreateQueuedAction(char*, void (__cdecl*)(), unsigned char, int, ...);
void __cdecl evt_LogScriptError(char*, int, const char*);
int __cdecl evt_LoadGfxScript(const char* name);
int __cdecl evt_RunScript(char* script);

extern int g_6791c8;

void __cdecl ch_RunAnimationScript();
char* __cdecl ch_CreateQueuedAction(char*, void (__cdecl*)(), unsigned char, int, ...);
void __cdecl evt_LogScriptError(char*, int, const char*);

void __cdecl ch_RunQueuedAniScript();
char* __cdecl ch_CreateQueuedAction(char*, void (__cdecl*)(), unsigned char, int, ...);
void __cdecl evt_LogScriptError(char*, int, const char*);
#include "Develop/Units/Error/error_message.h"

/* PlayCharacterAniSound(): queues a character animation task with a sound;
 * the calling script waits for it when it blocks. */
/* ADDRESS: GOLDTL 0x0040cee0 */
int __cdecl PlayCharacterAniSound(char** ch, char** ani, int* kind, unsigned char* level, char** sound)
{
	char* task;

	if (g_6b7ebc != 0 && *(int (__cdecl**)()) (g_6b7ebc + 0x44) == (int (__cdecl*)()) PlayCharacterAniSound) {
		if (*(int*) (*ch + 0x128) != 0) {
			*(int (__cdecl**)()) (evt_CurrentScript + 0xc60) = (int (__cdecl*)()) PlayCharacterAniSound;
		}
		return 0;
	}
	if (*ch == 0) {
		evt_LogScriptError(evt_CurrentScript, *(int*) (evt_CurrentScript + 0x118), "PlayCharacterAniSound(): invalid character");
		return 1;
	}
	task = ch_CreateQueuedAction(*ch, (void (__cdecl*)())PlayEntitySound, *level, 0x2e, *kind);
	if (task != 0) {
		strcpy(task + 0xf0, *ani);
		strcpy(task + 0x130, *sound);
	}
	if (*(int*) (evt_CurrentScript + 0xc84) == 1) {
		*(int (__cdecl**)()) (evt_CurrentScript + 0xc60) = (int (__cdecl*)()) PlayCharacterAniSound;
	}
	return 0;
}

/* Task callback for PlayCharacterAniScript(): loads the script named in the
 * task, runs it, and passes the task parameter to it. */
/* ADDRESS: GOLDTL 0x0040cfb0 */
void __cdecl ch_RunAnimationScript(char* task)
{
	char* script;

	script = (char*) evt_LoadGfxScript(task + 0x90);
	if (script != 0) {
		evt_RunScript(script);
		*(int*) (script + 0x104) = *(int*) (task + 0x17c);
	}
}

/* PlayCharacterAniScript(): queues a character animation task that runs a
 * script; the calling script waits for it when it blocks. */
/* ADDRESS: GOLDTL 0x0040cff0 */
int __cdecl PlayCharacterAniScript(char** ch, char** script, int* kind, unsigned char* level, char** func)
{
	char* task;

	if (g_6b7ebc != 0 && *(int (__cdecl**)()) (g_6b7ebc + 0x44) == (int (__cdecl*)()) PlayCharacterAniScript) {
		if (*(int*) (*ch + 0x128) != 0) {
			*(int (__cdecl**)()) (evt_CurrentScript + 0xc60) = (int (__cdecl*)()) PlayCharacterAniScript;
		}
		return 0;
	}
	if (*ch == 0) {
		evt_LogScriptError(evt_CurrentScript, *(int*) (evt_CurrentScript + 0x118), "PlayCharacterAniScript(): invalid character");
		return 1;
	}
	task = ch_CreateQueuedAction(*ch, ch_RunAnimationScript, *level, 0x2e, *kind);
	if (task != 0) {
		if (strlen(*script) >= 0x5f) {
			evt_LogScriptError(evt_CurrentScript, *(int*) (evt_CurrentScript + 0x118), "PlayCharacterAniScript(): script name too long");
			return 1;
		}
		strncpy(task + 0xf0, *script, 0x3f);
		strncpy(task + 0x90, *func, 0x5f);
		*(int*) (task + 0x17c) = g_6791c8;
	}
	if (*(int*) (evt_CurrentScript + 0xc84) == 1) {
		*(int (__cdecl**)()) (evt_CurrentScript + 0xc60) = (int (__cdecl*)()) PlayCharacterAniScript;
	}
	return 0;
}

/* PlayCharacterAniScriptInt(): like PlayCharacterAniScript() with an
 * integer parameter handed to the script. */
/* ADDRESS: GOLDTL 0x0040d130 */
int __cdecl PlayCharacterAniScriptInt(char** ch, char** script, int* kind, unsigned char* level, char** func, int* param)
{
	char* task;

	if (g_6b7ebc != 0 && *(int (__cdecl**)()) (g_6b7ebc + 0x44) == (int (__cdecl*)()) PlayCharacterAniScriptInt) {
		if (*(int*) (*ch + 0x128) != 0) {
			*(int (__cdecl**)()) (evt_CurrentScript + 0xc60) = (int (__cdecl*)()) PlayCharacterAniScriptInt;
		}
		return 0;
	}
	if (*ch == 0) {
		evt_LogScriptError(evt_CurrentScript, *(int*) (evt_CurrentScript + 0x118), "PlayCharacterAniScriptInt(): invalid character");
		return 1;
	}
	task = ch_CreateQueuedAction(*ch, ch_RunQueuedAniScript, *level, 0x2e, *kind);
	if (task != 0) {
		if (strlen(*script) >= 0x5f) {
			ReportClientMessage("PlayCharacterAniScript(): script name too long");
			return 1;
		}
		strncpy(task + 0xf0, *script, 0x3f);
		strncpy(task + 0x90, *func, 0x5f);
		*(int*) (task + 0x17c) = g_6791c8;
		*(int*) (task + 0x180) = *param;
	}
	if (*(int*) (evt_CurrentScript + 0xc84) == 1) {
		*(int (__cdecl**)()) (evt_CurrentScript + 0xc60) = (int (__cdecl*)()) PlayCharacterAniScriptInt;
	}
	return 0;
}
