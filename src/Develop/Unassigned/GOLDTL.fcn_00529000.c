#include "Develop/DieGildeAddOn/game/entity_record.h"


extern char g_7f4ca0[];

void __cdecl fcn_00529000(int idx, char* o)
{
	char* p;
	int i;

	p = ((char *)&((ENTITY_RECORD_VIEW *)g_7f4ca0)[idx]);
	for (i = 0; i < 8; i++) {
		if (*(int*) (o + 0x8c + i * 4) == *(int*)&((ENTITY_RECORD_VIEW*)p)->entity_id) {
			break;
		}
	}
	if (i >= 8) {
		for (i = 0; i < 8; i++) {
			if (*(int*) (o + 0x8c + i * 4) == -1) {
				*(int*) (o + 0x8c + i * 4) = *(int*)&((ENTITY_RECORD_VIEW*)p)->entity_id;
				break;
			}
		}
	}
}
