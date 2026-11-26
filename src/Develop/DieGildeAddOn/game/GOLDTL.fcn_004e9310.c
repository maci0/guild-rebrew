


typedef struct {
	unsigned char c0;
	char pad1[3];
	int id;
	unsigned char kind;
	char pad9[3];
	int fc;
	unsigned char f10;
	char pad11[3];
	int f14;
} rec18;
// SIZE 0x18

typedef struct {
	int a;
	int id;
	char pad8[0x10];
} tbl18;
// SIZE 0x18

#define MIN(a, b) ((a) < (b) ? (a) : (b))

int __cdecl amt_GetRoleTemplate(int, rec18*);
#include "Develop/DieGildeAddOn/game/aemter.h"
unsigned char* __cdecl gm_LookupEntityRecordById(int);
int __cdecl fcn_004e9180(unsigned char*, int);

int __cdecl amt_CollectOfficeCandidates(int k, int max, unsigned char** out)
{
	rec18 a;
	OFFICE_SLOT list[6];
	int n;
	int i;
	int cnt;
	unsigned char* e;

	if (amt_GetRoleTemplate(k, &a) == 0)
		return 0;
	n = amt_FindOfficeSlotsByKind(a.id, MIN(max, 6), list);
	if (n == 0)
		return 0;
	n = MIN(n, max);
	cnt = 0;
	for (i = 0; i < n; i++) {
		e = gm_LookupEntityRecordById(list[i].mplayerid);
		if (e != 0 && fcn_004e9180(e, k) != 0)
			out[cnt++] = e;
	}
	return cnt;
}
