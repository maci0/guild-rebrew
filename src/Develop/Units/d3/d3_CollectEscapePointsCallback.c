


#include "Develop/DieGildeAddOn/game/game_data.h"
extern char g_68b82c[];

int __cdecl fcn_0065f220(char*, char*);

/* ADDRESS: GOLDDE 0x004c07a0 */
char __cdecl d3_CollectEscapePointsCallback(char* name, char** arr)
{
	if (fcn_0065f220(name, g_68b82c) == 0) {
		arr[g_772f10] = name;
		g_772f10++;
	}
	return 1;
}
