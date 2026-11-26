


#include "Develop/DieGildeAddOn/game/aemter.h"
void __cdecl cm_RequestCopyEntityData(int a, int b, int c, int d);

void __cdecl amt_AdjustOfficeHoldersFavor(char* p, int kind, int arg)
{
	OFFICE_SLOT recs[6];
	int n;
	int i;

	if (kind < 1 || kind > 7) {
		return;
	}
	n = amt_FindOfficeSlotsByKind(kind, 6, recs);
	for (i = 0; i < n; i++) {
		if (recs[i].mplayerid != *(int*) (p + 4) && recs[i].mplayerid != -1) {
			cm_RequestCopyEntityData(*(int*) (p + 4), recs[i].mplayerid, arg, 1);
		}
	}
}
