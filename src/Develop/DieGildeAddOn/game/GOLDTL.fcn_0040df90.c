#include "Develop/DieGildeAddOn/game/ch_script.h"
extern char g_6752a8[];



#include <string.h>

int __cdecl SetCharacterStepSample(char** p)
{
	strcpy(g_6752a8, *p);
	return 1;
}
