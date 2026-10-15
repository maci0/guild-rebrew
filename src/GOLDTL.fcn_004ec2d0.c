


#include "Develop/DieGildeAddOn/game/aemter.h"
void __cdecl fcn_004c54c0(int a, int b, int c, int d);

void __cdecl fcn_004ec2d0(char* p, int kind, int arg)
{
	OFFICE_SLOT recs[6];
	int n;
	int i;

	if (kind < 1 || kind > 7) {
		return;
	}
	n = fcn_004e8b80(kind, 6, recs);
	for (i = 0; i < n; i++) {
		if (recs[i].mplayerid != *(int*) (p + 4) && recs[i].mplayerid != -1) {
			fcn_004c54c0(*(int*) (p + 4), recs[i].mplayerid, arg, 1);
		}
	}
}
