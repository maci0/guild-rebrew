// FUNCTION: GOLDTL 0x44cd20

#include <string.h>

// SIZE 0xc
typedef struct Ent {
	char* name;
	int a;
	int b;
} Ent;

int __cdecl fcn_0044cd20(char* name, Ent* tbl, int n)
{
	int i;

	if (name != 0 && tbl != 0 && n > 2) {
		for (i = 2; i < n; i++) {
			if (name[0] == tbl[i].name[0] && name[1] == tbl[i].name[1] && strcmp(name, tbl[i].name) == 0) {
				return i;
			}
		}
	}
	return -1;
}
