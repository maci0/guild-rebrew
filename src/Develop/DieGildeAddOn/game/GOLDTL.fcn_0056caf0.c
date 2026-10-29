#include <math.h>

#include "client_types.h"

extern pos14_7f4c00 g_7f4c00;
extern int g_7f4c04;
extern int g_7f4c08;
extern short g_7f4c0c;
extern char g_7f4ca4[];

int* __cdecl fcn_004c30a0(int, int, char*, int, int);
char* __cdecl gm_StartFilteredEntitySearch(int, int, int);
void __cdecl fcn_00455350(char*, char*, float*);
char* __cdecl he_fn_Handlung(void);
char* __cdecl fcn_005463a0(int, ...);
int __cdecl fcn_00546190(char*);
void __cdecl fcn_00500bb0(pos14_7f4c00*, int, int, int);
void __cdecl fcn_004c5530(char*);

/* ADDRESS: GOLDTL 0x0056caf0 */
/* Five-state job machine. State 1 picks the nearest of the sixteen stored
 * entity ids and stores it as the new target; state 2 drops that target and
 * reports the removal; state 3 re-resolves an existing target and copies its
 * clock position. States -2 and -1 just release the item. */
void __cdecl fcn_0056caf0(char* a0)
{
	float best;
	char* found;
	int i;
	float p1[4];
	float p2[4];
	float d;
	char m[0xf8];
	char* rec;
	char* cand;
	char* e;

	found = 0;
	best = 1.0e8f;
	switch (*(int*) (a0 + 0x70)) {
	case 0:
		fcn_004c30a0(-8, 0, (char*) 0x6a6ac0, -1, 100);
		*(int*) (a0 + 0x70) += 1;
		return;
	case 1:
		rec = gm_StartFilteredEntitySearch(1, 1, *(int*) (a0 + 0xec));
		for (i = 0x10, e = a0 + 0xac; i != 0; i--, e += 4) {
			if (rec == 0) {
				continue;
			}
			if (*(int*) e == -1) {
				continue;
			}
			if (*(int*) e == *(int*) (rec + 1)) {
				continue;
			}
			cand = gm_StartFilteredEntitySearch(1, 1, *(int*) e);
			if (cand == 0) {
				continue;
			}
			fcn_00455350((char*) *(int*) (rec + 0x61), (char*) (*(int*) (rec + 0x61) + 0x4c), p1);
			fcn_00455350((char*) *(int*) (cand + 0x61), (char*) (*(int*) (cand + 0x61) + 0x4c), p2);
			d = (float) sqrt((p1[2] - p2[2]) * (p1[2] - p2[2]) + (p1[1] - p2[1]) * (p1[1] - p2[1])
			                 + (p1[0] - p2[0]) * (p1[0] - p2[0]));
			if (d < best) {
				best = d;
				found = cand;
			}
		}
		if (found != 0) {
			*(int*) (a0 + 0xec) = *(int*) (found + 1);
		} else {
			*(int*) (a0 + 0xec) = -1;
		}
		*(pos14_7f4c00*) (a0 + 0x52) = g_7f4c00;
		*(int*) (a0 + 0x70) += 1;
		return;
	case 2:
		if (*(int*) (a0 + 0xec) != -1) {
			rec = gm_StartFilteredEntitySearch(1, 1, *(int*) (a0 + 0xec));
			i = 0;
			if (rec != 0) {
				for (e = a0 + 0xac; i < 0x10; i++, e += 4) {
					if (*(int*) e != *(int*) (rec + 1)) {
						continue;
					}
					*(int*) e = -1;
					*(int*) (m + 0x28) = *(int*) &g_7f4c00;
					*(int*) (m + 0x30) = g_7f4c08;
					m[4] = 0x4f;
					m[0x36] = 2;
					*(int*) (m + 0x5c) = 0x19;
					m[0xb0] = 1;
					*(int*) (m + 8) = *(int*) (g_7f4ca4 + *(unsigned short*) (a0 + 8) * 0x21c);
					*(int*) (m + 0xc) = *(int*) (rec + 1);
					*(int*) (m + 0x2c) = g_7f4c04;
					*(int*) (m + 0x58) = *(int*) (rec + 1);
					*(short*) (m + 0x34) = g_7f4c0c;
					*(int*) (m + 0xa4) = *(int*) (a0 + 4);
					fcn_004c5530(m);
				}
			}
			*(pos14_7f4c00*) (a0 + 0x52) = g_7f4c00;
			fcn_00500bb0((pos14_7f4c00*) (a0 + 0x52), 0, 10, 0);
			*(int*) (a0 + 0x70) = 1;
			return;
		}
		*(int*) (a0 + 0x70) += 1;
		return;
	case 3:
		rec = fcn_005463a0(1, 0, 0x4f);
		while (rec != 0 && *(int*) (rec + 0xf8) != *(int*) (a0 + 4)) {
			rec = he_fn_Handlung();
		}
		if (rec == 0) {
			fcn_004c30a0(-8, 0, (char*) 0x6a6ab4, -1, 100);
			fcn_00546190(a0);
			return;
		}
		*(pos14_7f4c00*) (a0 + 0x52) = g_7f4c00;
		fcn_00500bb0((pos14_7f4c00*) (a0 + 0x52), 0, 10, 0);
		return;
	case -1:
	case -2:
		fcn_00546190(a0);
		return;
	default:
		return;
	}
}
