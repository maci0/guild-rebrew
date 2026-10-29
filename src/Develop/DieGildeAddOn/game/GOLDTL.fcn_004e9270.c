

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

int __cdecl fcn_004e8b40(int, rec18*);
#include "Develop/DieGildeAddOn/game/aemter.h"
unsigned char* __cdecl fcn_00508e40(int);
int __cdecl fcn_004e9180(unsigned char*, int);

int __cdecl fcn_004e9270(int k)
{
	rec18 a;
	OFFICE_SLOT list[6];
	int n;
	int i;
	unsigned char* e;

	if (fcn_004e8b40(k, &a) == 0)
		return 0;
	n = fcn_004e8b80(a.id, 6, list);
	if (n == 0)
		return 0;
	for (i = 0; i < n; i++) {
		e = fcn_00508e40(list[i].mplayerid);
		if (e != 0 && fcn_004e9180(e, k) != 0 && e[0x1b1] == 0)
			return 1;
	}
	return 0;
}
