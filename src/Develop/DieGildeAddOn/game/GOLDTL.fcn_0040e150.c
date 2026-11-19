#include <string.h>
#include "Develop/DieGildeAddOn/game/ch_script.h"
void __cdecl evt_LogScriptError(void*, int, char*);

int __cdecl CharacterSitsDown(char** object)
{
    unsigned char* p;

    p = (unsigned char*) *object;
    if (p == 0) {
        evt_LogScriptError(*(void**) 0x6b7e98,
            *(int*) ((char*) *(void**) 0x6b7e98 + 0x118),
            (char*) 0x67635c);
        return 0;
    }
    if ((p[0x8c] >> 4) & 1) {
        return 1;
    }
    return 0;
}



int __cdecl FindInCharacterName(char** character, int* needle)
{
	char* p;

	p = *character;
	if (p == 0) {
		evt_LogScriptError(*(void**) 0x6b7e98, *(int*) ((char*) *(void**) 0x6b7e98 + 0x118), (char*) 0x676384);
		return 0;
	}
	return strstr(p + 8, (char*) *needle) != 0;
}
