extern char g_6b7e98[];
#include <string.h>
#include "Develop/DieGildeAddOn/game/ch_script.h"
void __cdecl evt_LogScriptError(void*, int, char*);

/* ADDRESS: GOLDDE 0x0040cf10 */
int __cdecl CharacterSitsDown(char** object)
{
    unsigned char* p;

    p = (unsigned char*) *object;
    if (p == 0) {
        evt_LogScriptError(*(void**) &g_6b7e98,
            *(int*) ((char*) *(void**) &g_6b7e98 + 0x118),
            "CharacterSitsDown(): invalid character");
        return 0;
    }
    if ((p[0x8c] >> 4) & 1) {
        return 1;
    }
    return 0;
}



/* ADDRESS: GOLDDE 0x0040cf50 */
int __cdecl FindInCharacterName(char** character, int* needle)
{
	char* p;

	p = *character;
	if (p == 0) {
		evt_LogScriptError(*(void**) &g_6b7e98, *(int*) ((char*) *(void**) &g_6b7e98 + 0x118), "FindInCharacterName(): invalid character");
		return 0;
	}
	return strstr(p + 8, (char*) *needle) != 0;
}
