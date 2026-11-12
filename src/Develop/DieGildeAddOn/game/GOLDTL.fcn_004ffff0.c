#include <math.h>
#include <string.h>
typedef struct { int word[2]; } QUERY_LIMIT;
char* __cdecl gm_StartFilteredEntitySearch(int, int, int);
char* __cdecl gm_FindNextFilteredEntity(void);
int __cdecl fcn_004fac80(int, int*);
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
	QUERY_LIMIT selected, current;





	best = 0;
	bestd = 1e8f;
	fcn_004fac80(1, selected.word);
	e = gm_StartFilteredEntitySearch(1, 5, 1);
	if (e != 0) {

		do {
			fcn_004fac80(*(unsigned char*) e, current.word);
			n = current.word[0];
			if ((unsigned short) *(unsigned char*) (e + 0x65) < (unsigned short) current.word[0]
			    && (*(unsigned char*) (e + 0x5a) & 1) == 0) {
				if (a1 != 0 && *(int*) (a1 + 0x61) != 0 && *(int*) (e + 0x61) != 0) {
					fcn_00455350(*(int*) (e + 0x61), *(int*) (e + 0x61) + 0x4c, p1);
					fcn_00455350(*(int*) (a1 + 0x61), *(int*) (a1 + 0x61) + 0x4c, p2);
					p1[0] = p1[0] - p2[0];
					p1[1] = p1[1] - p2[1];
					p1[2] = p1[2] - p2[2];
					d = sqrt(p1[0] * p1[0] + p1[1] * p1[1] + p1[2] * p1[2]);
					if (d < bestd) {
						selected = current;

						best = e;
						bestd = d;
					}
				} else if (best != 0) {
					if ((float) *(unsigned char*) (e + 0x65) / (float) (n & 0xffff)
					    < (float) *(unsigned char*) (best + 0x65) / (float) (selected.word[0] & 0xffff)) {
						best = e;
					}
				} else {
					selected = current;

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
