

#include "Develop/DieGildeAddOn/game/aemter.h"
int __cdecl gm_LookupEntityRecordById(int);

int __cdecl fcn_005bd7c0(int max, int a, int* out)
{
	int n;
	int cnt;
	int i;
	int r;

	n = fcn_004e8b80(a, 6, (OFFICE_SLOT*) 0x775288);
	cnt = 0;
	for (i = 0; i < n; i++) {
		if (cnt >= max) {
			break;
		}
		r = gm_LookupEntityRecordById(((OFFICE_SLOT*) 0x775288)[i].mplayerid);
		if (r != 0) {
			out[cnt++] = r;
		}
	}
	return cnt;
}
