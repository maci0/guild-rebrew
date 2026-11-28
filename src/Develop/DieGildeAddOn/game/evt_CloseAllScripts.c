#include "Develop/DieGildeAddOn/game/game_data.h"



void __cdecl evt_FreeScript(void*);

/* ADDRESS: GOLDDE 0x00424300 */
void __cdecl evt_CloseAllScripts(void)
{
	int o;
	char* p;

	for (o = 0; o < 0x64c00; o += 0xc98) {
		p = (char*) (*(int*) ((char*)&evt_ScriptSlots) + o);
		if (*(unsigned char*) p != 0 || *(int*) (p + 0x100) != -1) {
			evt_FreeScript(p);
		}
	}
}
