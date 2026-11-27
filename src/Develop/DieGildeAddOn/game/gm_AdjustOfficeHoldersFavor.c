#include "Develop/DieGildeAddOn/game/entity_record.h"


extern char g_7f4ca0[];

void __cdecl cm_RequestCopyEntityData(int a, int b, int c, int d);

void __cdecl gm_AdjustOfficeHoldersFavor(unsigned short entityId, int delta)
{
	int i;

	for (i = 0; i < 768; i++) {
		if (((unsigned char *)&((ENTITY_RECORD_VIEW *)g_7f4ca0)[i])[0x166] != 0) {
			cm_RequestCopyEntityData(entityId, i, delta, 1);
		}
	}
}
