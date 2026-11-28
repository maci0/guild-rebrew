#include "Develop/DieGildeAddOn/game/ch_script.h"
extern char ch_StepSampleName[];



#include <string.h>

int __cdecl SetCharacterStepSample(char** p)
{
	strcpy(ch_StepSampleName, *p);
	return 1;
}
