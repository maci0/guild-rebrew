


#include <math.h>
#include <string.h>

#include "client_types.h"
extern pos14_7f4c00 g_7f4c00;

char* __cdecl gm_StartFilteredEntitySearch();
char* __cdecl gm_AddObjekt(void);
char* __cdecl gm_FindNextFilteredEntity(void);
void __cdecl fcn_00508cf0(int, int*);
int __cdecl fcn_0064d41a(char*, char*, ...);
void __cdecl fcn_00500bb0(pos14_7f4c00*, int, int, int);
int __cdecl fcn_004c5620(int, char*);

void __cdecl fcn_0054d840(char* e)
{
	int cand[8];
	int order[8];
	char buf[0x100];
	char* me;
	char* o;
	char* a;
	char* b;
	float dx;
	float dy;
	float dz;
	int n;
	int i;

	n = 0;
	if ((e[0x78] & 4) != 0) {
		return;
	}
	*(pos14_7f4c00*) (e + 0x44) = g_7f4c00;
	memset(cand, 0xff, sizeof(cand));
	me = gm_StartFilteredEntitySearch(1, 1, *(int*) (e + 0xac));
	for (o = gm_StartFilteredEntitySearch(1, 6); o != 0; o = gm_FindNextFilteredEntity()) {
		if (n >= 8) {
			break;
		}
		a = *(char**) (o + 0x61);
		if (a != 0 && *(int*) (o + 1) != *(int*) (me + 1) && *(int*) (o + 1) != *(int*) (e + 0xb0) && *o != 0x47) {
			b = *(char**) (me + 0x61);
			dx = *(float*) (a + 0x4c) - *(float*) (b + 0x4c);
			dy = *(float*) (a + 0x50) - *(float*) (b + 0x50);
			dz = *(float*) (a + 0x54) - *(float*) (b + 0x54);
			if ((float) sqrt(dz * dz + dy * dy + dx * dx) <= 950.0f) {
				cand[n++] = *(int*) (o + 1);
			}
		}
	}
	if (n != 0) {
		memset(e + 0xb4, 0xff, 16);
		fcn_00508cf0(n, order);
		for (i = 0; i < n; i++) {
			if (i >= 4) {
				break;
			}
			((int*) (e + 0xb4))[i] = cand[order[i]];
		}
	}
	fcn_0064d41a(buf, "STREIFE_INIT: Target: %i, Way: %i, %i, %i, %i, Start: %i", *(int*) (e + 0xac), *(int*) (e + 0xb4),
	    *(int*) (e + 0xb8), *(int*) (e + 0xbc), *(int*) (e + 0xc0), *(int*) (e + 0xb0));
	*(pos14_7f4c00*) (e + 0x52) = g_7f4c00;
	fcn_00500bb0((pos14_7f4c00*) (e + 0x52), 0, 0, 1);
	*(int*) (e + 0xd8) = 0;
	e[0xdc] = 0;
	*(int*) (e + 0xd4) = -1;
	*(int*) (e + 0x84) = fcn_004c5620(0, e);
}
