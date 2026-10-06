extern char* g_773da8;

#include "client_types.h"
extern pos14_7f4c00 g_7f4c00;

// SIZE 0xf8
struct msg {
	int f0;
	char b4;
	char pad[3];
	int f8;
	int fc;
	char pad2[0x18];
	pos14_7f4c00 pos;
	char b36;
	char pad3[0x21];
	char b58;
	char pad4[3];
	char b5c;
	char pad5[0x9b];
};

// FUNCTION: GOLD 0x0053f3f0
// FUNCTION: GOLDTL 0x5471c0

#include <string.h>

char* __cdecl gm_StartFilteredEntitySearch(int, int, int);
char* __cdecl gm_AddObjekt(void);
char* __cdecl fcn_005463a0(int, int, int, ...);
char* __cdecl fcn_005462a0(void);
void __cdecl fcn_004c5530(struct msg*);

void __cdecl fcn_005471c0(void)
{
	struct msg m;
	char* e;
	char* p;
	int found;

	found = 0;
	memset(&m, 0, sizeof(m));
	for (e = gm_StartFilteredEntitySearch(1, 5, 7); e != 0; e = gm_AddObjekt()) {
		for (p = fcn_005463a0(1, 0, 0x2b); p != 0; p = fcn_005462a0()) {
			if (*(int*) (p + 0x10) == *(int*) (e + 1)) {
				found = 1;
				break;
			}
		}
		if (found == 0) {
			m.b4 = 0x2b;
			m.pos = g_7f4c00;
			m.b36 = 2;
			m.f8 = *(int*) (g_773da8 + 4);
			m.fc = *(int*) (e + 1);
			m.b5c = 0;
			fcn_004c5530(&m);
		}
	}
}
