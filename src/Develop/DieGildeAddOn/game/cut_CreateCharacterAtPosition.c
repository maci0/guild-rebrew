extern char cut_SkipMode[];


#include "Develop/DieGildeAddOn/game/ch_motion.h"

/* ADDRESS: GOLDDE 0x004d1420 */
char* __cdecl cut_CreateCharacterAtPosition(char* resource, float* position)
{
	if (*(int*) &cut_SkipMode != 0) {
		return 0;
	}
	return ch_CreateAtPosition(resource, position);
}
