#include "Develop/DieGildeAddOn/game/ch_script.h"
extern char ch_StepSampleName[];



#include <string.h>

/* ADDRESS: GOLDDE 0x0040cd90 */
int __cdecl SetCharacterStepSample(char** p)
{
	strcpy(ch_StepSampleName, *p);
	return 1;
}
