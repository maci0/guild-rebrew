extern unsigned char* lpGebaeudePROT;
#include "Develop/DieGildeAddOn/game/building_prototype.h"



#include <string.h>

int __cdecl init_GetGebaeudeSceneName(int idx, char* out)
{
	unsigned char* t;

	t = ((unsigned char*)&((BUILDING_PROTOTYPE*)lpGebaeudePROT)[idx]);
	if (*t == 0x1d) {
		strcpy(out, "FRIEDHOF");
		return 1;
	}
	if (*t == 0x1f) {
		strcpy(out, "ZIGEUNERLAGER");
		return 1;
	}
	strcpy(out, (char*) t + 1);
	return 1;
}
