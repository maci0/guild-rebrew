#include <math.h>
#include <string.h>

char* __cdecl gm_StartFilteredEntitySearch(int, int, int);
char* __cdecl gm_FindNextFilteredEntity(void);
void __cdecl fcn_004fac80(int, int*);
void __cdecl fcn_00455350(int, int, float*);
int __cdecl gm_RandomMod(int);

/* ADDRESS: GOLDTL 0x004ffff0 */
char* __cdecl fcn_004ffff0(int a0, int a1)
{
	char* e;
	char* best;
	char* list[0x10];
	float p1[3];
	float p2[3];
	float bestd;
	float d;
	int n;
	int v6;
	int v7;
	int v8;
	int v17;
	int v18;

	best = 0;
	bestd = 1e8f;
	fcn_004fac80(1, &v7);
	e = gm_StartFilteredEntitySearch(1, 5, 1);
	if (e != 0) {
		v6 = v7;
		do {
			fcn_004fac80(*(unsigned char*) e, &v8);
			n = v8;
			if ((unsigned short) *(unsigned char*) (e + 0x65) < (unsigned short) v8
			    && (*(unsigned char*) (e + 0x5a) & 1) == 0) {
				if (a1 != 0 && *(int*) (a1 + 0x61) != 0 && *(int*) (e + 0x61) != 0) {
					fcn_00455350(*(int*) (e + 0x61), *(int*) (e + 0x61) + 0x4c, p1);
					fcn_00455350(*(int*) (a1 + 0x61), *(int*) (a1 + 0x61) + 0x4c, p2);
					p1[0] = p1[0] - p2[0];
					p1[1] = p1[1] - p2[1];
					p1[2] = p1[2] - p2[2];
					d = sqrt(p1[0] * p1[0] + p1[1] * p1[1] + p1[2] * p1[2]);
					if (d < bestd) {
						v17 = v18;
						v6 = n;
						best = e;
						bestd = d;
					}
				} else if (best != 0) {
					if ((float) *(unsigned char*) (e + 0x65) / (float) (n & 0xffff)
					    < (float) *(unsigned char*) (best + 0x65) / (float) (v6 & 0xffff)) {
						best = e;
					}
				} else {
					v17 = v18;
					v6 = n;
					best = e;
				}
			}
			e = gm_FindNextFilteredEntity();
		} while (e != 0);
		if (best != 0) {
			return best;
		}
	}
	e = gm_StartFilteredEntitySearch(1, 5, 0x16);
	memset(list, 0, sizeof(list));
	n = 0;
	while (e != 0 && (*(unsigned char*) (e + 0x5a) & 1) == 0 && n < 0x10) {
		list[n] = e;
		n++;
		e = gm_FindNextFilteredEntity();
	}
	return list[gm_RandomMod(n) & 0xffff];
}
