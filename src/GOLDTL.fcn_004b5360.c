#include "g_7f4ca2.h"

extern Slot7f4ca2 g_7f4ca2[768];

char* __cdecl gm_StartFilteredEntitySearch(int arg_count, ...);
char* __cdecl gm_AddObjekt(void);

// FUNCTION: GOLDTL 0x4b5360

int __cdecl fcn_004b5360(int owner)
{
	int n;
	char* p;
	unsigned short h;
	unsigned char kind;

	n = 0;
	for (p = gm_StartFilteredEntitySearch(1, 5, owner); p != 0; p = gm_AddObjekt()) {
		h = *(unsigned short*) (p + 0x27);
		if (h == 0xffff)
			return -1;
		kind = g_7f4ca2[h].kind;
		if (kind != 6 && kind != 7)
			return -1;
		n++;
	}
	return n;
}
