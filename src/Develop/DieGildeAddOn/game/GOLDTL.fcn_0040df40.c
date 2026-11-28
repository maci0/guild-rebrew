extern char g_6b7e98[];
#include "Develop/DieGildeAddOn/game/ch_script.h"
int __cdecl d3_FindSceneObject(int, int, int, int);
void __cdecl evt_LogScriptError(void*, int, char*);

/* ADDRESS: GOLDDE 0x0040cd00 */
int __cdecl CharacterSitting(char** object)
{
    unsigned char* p;

    p = (unsigned char*) *object;
    if (p == 0) {
        evt_LogScriptError(*(void**) &g_6b7e98,
            *(int*) ((char*) *(void**) &g_6b7e98 + 0x118),
            "CharacterSitting(): invalid character");
        return 0;
    }
    if ((p[0x8c] >> 4) & 1) {
        return 1;
    }
    return 0;
}



/* ADDRESS: GOLDDE 0x0040cd40 */
int __cdecl GetCharacterSubObjectHandle(char** character, int* selector)
{
	char* p;

	p = *character;
	if (p == 0) {
		evt_LogScriptError(*(void**) &g_6b7e98, *(int*) ((char*) *(void**) &g_6b7e98 + 0x118), "GetCharacterSubObjectHandle(): invalid character");
		return 0;
	}
	return d3_FindSceneObject(*(int*) (p + 0x34), 0x140, 0, *selector);
}
