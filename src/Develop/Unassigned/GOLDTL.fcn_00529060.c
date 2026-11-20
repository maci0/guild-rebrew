


#include "Develop/DieGildeAddOn/game/entity_record.h"

void __cdecl fcn_00529060(int idx, char* o)
{
	char* p;
	int i;

	p = ((char*)&((ENTITY_RECORD_VIEW*)g_7f4ca0)[idx]);
	for (i = 0; i < 8; i++) {
		if (*(int*) (o + 0x8c + i * 4) == *(int*) (p + 4)) {
			*(int*) (o + 0x8c + i * 4) = -1;
			return;
		}
	}
}
