


#include <math.h>

// SIZE 0x10
struct search {
	char* who;
	float range;
	char* house;
	char* found;
};

#include "client_types.h"
extern pos14_7f4c00 g_7f4c00;

char* __cdecl fcn_005463a0(int, int, int, ...);
char* __cdecl fcn_005462a0(void);
char* __cdecl fcn_00508e40(int);
void __cdecl fcn_004c5c80(int);
void __cdecl fcn_004c5ed0(int, char*, int);
void __cdecl fcn_004c5da0(int, int, int, int, int, char*);
unsigned short __cdecl gm_RandomMod(int);
void __cdecl fcn_00500bb0(pos14_7f4c00*, int, int, int);
int __cdecl fcn_004c5620(int, char*);

int __cdecl fcn_0055be70(struct search* s)
{
	char* found;
	char* h;
	char* u;
	char* a;
	char* b;
	float dx;
	float dy;
	float dz;
	int j;

	found = 0;
	h = 0;
	if (s->who == 0 || *(char**) (s->who + 0x61) == 0) {
		return 0;
	}
	for (u = fcn_005463a0(1, 0, 0x43); u != 0; u = fcn_005462a0()) {
		if (found != 0) {
			break;
		}
		if (*(int*) (u + 0xd4) != -1 || *(int*) (u + 0xc) == *(int*) (s->house + 0xc)) {
			continue;
		}
		for (j = 0; j < 4; j++) {
			if (((int*) (u + 0xc4))[j] != -1 && (h = fcn_00508e40(((int*) (u + 0xc4))[j])) != 0) {
				a = *(char**) (s->who + 0x61);
				b = *(char**) (*(char**) (h + 0x184) + 0x34);
				dx = *(float*) (a + 0x4c) - *(float*) (b + 0x4c);
				dy = *(float*) (a + 0x50) - *(float*) (b + 0x50);
				dz = *(float*) (a + 0x54) - *(float*) (b + 0x54);
				if ((float) sqrt(dz * dz + dy * dy + dx * dx) < s->range) {
					found = u;
					break;
				}
			}
		}
	}
	if (found == 0) {
		return 0;
	}
	s->found = found;
	for (j = 0; j < 4; j++) {
		if (((int*) (found + 0xc4))[j] != -1 && fcn_00508e40(((int*) (found + 0xc4))[j]) != 0) {
			fcn_004c5c80(((int*) (found + 0xc4))[j]);
			if (*(int*) (h + 4) == ((int*) (found + 0xc4))[j]) {
				fcn_004c5ed0(((int*) (found + 0xc4))[j], "gestik/herranwinken", 2);
			}
			fcn_004c5da0(((int*) (found + 0xc4))[j], *(int*) (s->who + 1), -1, 0, 1, "Detected");
			fcn_004c5ed0(((int*) (found + 0xc4))[j], "gestik/abfaellig", gm_RandomMod(2) + 1);
		}
	}
	*(int*) (found + 0xd4) = *(int*) (s->house + 4);
	*(pos14_7f4c00*) (found + 0x52) = g_7f4c00;
	fcn_00500bb0((pos14_7f4c00*) (found + 0x52), 0, 8, 0);
	fcn_004c5620(0x400, found);
	return 1;
}
