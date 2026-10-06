void __cdecl fcn_00546190(char*);

#include "client_types.h"
extern pos14_7f4c00 g_7f4c00;

// FUNCTION: GOLD 0x0054fda0
// FUNCTION: GOLDTL 0x557e50

void __cdecl fcn_005015e0(char**, int, int, int);
char* __cdecl fcn_005c61e0(int);
void __cdecl fcn_00500bb0(pos14_7f4c00*, int, int, int);

void __cdecl fcn_00557e50(char* o)
{
	char* e;
	char* t;

	fcn_005015e0(&e, 0, 0, *(int*) (o + 0xac));
	if (e != 0 && *(int*) (e + 0x61) != 0) {
		t = fcn_005c61e0(*(unsigned short*) (o + 0xc2));
		if (t != 0 && *(int*) (t + 4) != 0) {
			*(pos14_7f4c00*) (o + 0xb4) = g_7f4c00;
			fcn_00500bb0((pos14_7f4c00*) (o + 0xb4), 0, *(int*) (t + 4), 0);
			*(int*) (o + 0xb0) = 0;
			*(int*) (o + 0x70) = 0;
			return;
		}
	}
	fcn_00546190(o);
}
