void __cdecl fcn_00546190(char*);

#include "client_types.h"
extern pos14_7f4c00 g_7f4c00;




char* __cdecl gm_StartFilteredEntitySearch(int, int, int);
int __cdecl fcn_004c5620(int, char*);
void __cdecl fcn_0057aab0(char*, int, int, int);
void __cdecl fcn_00500bb0(pos14_7f4c00*, int, int, int);

void __cdecl fcn_0057ad50(char* o)
{
	pos14_7f4c00* p;
	char* e;

	if (*(int*) (o + 0x70) == -2 || *(int*) (o + 0x70) == -1) {
		fcn_00546190(o);
	}
	if (o[0x78] & 4) {
		return;
	}
	p = (pos14_7f4c00*) (o + 0x52);
	*p = g_7f4c00;
	e = gm_StartFilteredEntitySearch(1, 1, *(int*) (o + 0xac));
	if (e == 0) {
		fcn_004c5620(-1, o);
		return;
	}
	if (*(int*) (o + 0x70) != 0) {
		return;
	}
	if (*(int*) (o + 0xb8) < 4) {
		fcn_0057aab0(e, *(int*) (o + 0xb0), *(int*) (o + 0xb4), *(int*) (o + 0xb8));
		fcn_00500bb0(p, 0, 0x1e, 0);
		(*(int*) (o + 0xb8))++;
		fcn_004c5620(0, o);
	} else {
		*(int*) (o + 0x70) = -1;
		fcn_00500bb0(p, 0x16, 0, 0);
		fcn_004c5620(-1, o);
	}
}
