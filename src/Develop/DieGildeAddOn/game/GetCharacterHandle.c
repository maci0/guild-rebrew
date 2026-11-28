#include "Develop/DieGildeAddOn/game/ch_script.h"
extern char str_GetCharacterHandle_not_found[];



int __cdecl ch_FindCharacterByName(int);
int __cdecl fcn_0064d41a(char*, char*, ...);
extern char* evt_CurrentScript;
void __cdecl evt_LogScriptError(void*, int, char*);

/* ADDRESS: GOLDDE 0x0040c060 */
int __cdecl GetCharacterHandle(int* id)
{
	char buf[0x80];
	int r;

	r = ch_FindCharacterByName(*id);
	if (r == 0) {
		fcn_0064d41a(buf, str_GetCharacterHandle_not_found, *id);
		evt_LogScriptError(evt_CurrentScript, *(int*) (evt_CurrentScript + 0x118), buf);
	}
	return r;
}
