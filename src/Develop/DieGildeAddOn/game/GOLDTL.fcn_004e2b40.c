#include "Develop/DieGildeAddOn/game/event_callbacks.h"
char* __cdecl gm_LookupEntityRecordById(int);
float __cdecl fcn_004fef80(char*);


/* ADDRESS: GOLDTL 0x004e2b40 */
int __cdecl fcn_004e2b40(char* m)
{
	if (fcn_004fef80(gm_LookupEntityRecordById(*(int*) (m + 0x34))) > 0.0f)
		return 0;
	return 1;
}
