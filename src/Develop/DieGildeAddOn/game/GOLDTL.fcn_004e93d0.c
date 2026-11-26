typedef struct {
	unsigned char c0;
	char pad1[3];
	int id;
	unsigned char kind;
	char pad9[3];
	int fc;
	int f10;
	int f14;
} rec18;
// SIZE 0x18

int __cdecl amt_GetRoleTemplate(int, rec18*);
#include "Develop/DieGildeAddOn/game/aemter.h"


/* ADDRESS: GOLDTL 0x004e93d0 */
int __cdecl amt_ListPromotionOffices(unsigned char* entity, int max, int* out)
{
	int want;
	int i;
	int n;
	rec18 r;
	OFFICE_SLOT arr[6];
	int cnt;
	int id;
	int v;

	if (entity[0x166] == 0)
		return 0;
	if (amt_GetRoleTemplate(entity[0x166], &r) == 0)
		return 0;
	n = amt_FindOfficeSlotsByKind(r.id, 6, arr);
	if (n == 0)
		return 0;
	if (r.kind % 3 == 1)
		want = 0;
	else
		want = r.kind - 1;
	cnt = 0;
	for (i = 0; i < n; i++) {
		if (cnt >= max)
			break;
		if (arr[i].status == 3) {
			id = arr[i].mamt;
			amt_GetRoleTemplate(id, &r);
			v = r.kind;
			if (v % 3 == 0) {
				out[cnt++] = id;
			} else if (want == v) {
				out[cnt++] = id;
				if (r.f10 != 0)
					break;
			}
		}
	}
	return cnt;
}
