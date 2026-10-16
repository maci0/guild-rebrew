extern unsigned char* g_868050;




#include <string.h>

void __cdecl SelectTextureSet(char*, int, int, int);

char __cdecl fcn_005165f0(char* o, unsigned char* e)
{
	unsigned char* t;
	int n;
	int st;
	int i;

	t = g_868050 + *e * 0x24d;
	n = t[0x247] - 1;
	if (*t == 2) {
		n++;
	}
	st = *(int*) (o + 0x220);
	if (st == 2 || st == 4 || st == 3) {
		return 1;
	}
	if (strncmp(o, "pfl_", 4) != 0 && strncmp(o, "vg_", 3) != 0 &&
	    strncmp(o, "!vg_", 4) != 0) {
		for (i = 0; i <= n; i++) {
			SelectTextureSet(o, *(int*) (o + 0x1cc), i, 1);
		}
	}
	return 1;
}
