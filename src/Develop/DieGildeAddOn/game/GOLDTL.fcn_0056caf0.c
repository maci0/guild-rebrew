#include <math.h>

#include "client_types.h"

extern pos14_7f4c00 gm_GameTime;
extern int g_7f4c04;
extern int g_7f4c08;
extern short g_7f4c0c;
extern char g_7f4ca4[];

int* __cdecl fcn_004c30a0(int, int, char*, int, int);
char* __cdecl gm_StartFilteredEntitySearch(int, int, int);
void __cdecl d3_TransformPoint(char*, char*, float*);
char* __cdecl he_fn_Handlung(void);
char* __cdecl he_StartHandlungSearch(int, ...);
int __cdecl he_FreeAction(char*);
void __cdecl fcn_00500bb0(pos14_7f4c00*, int, int, int);
void __cdecl fcn_004c5530(char*);

/* ADDRESS: GOLDTL 0x0056caf0 */
/* Five-state job machine. State 0 queues the search request, state 1 picks
 * the nearest of the sixteen stored entity ids and stores it as the new
 * target, state 2 drops that target and reports the removal, state 3
 * re-resolves an existing target and copies its clock position. States -2
 * and -1 share the release body. */
void __cdecl he_RunFireEvent(char* a0)
{
	float best;
	char* found;
	int i;
	int n;
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
			d3_TransformPoint((char*) *(int*) (rec + 0x61), (char*) (*(int*) (rec + 0x61) + 0x4c), p1);
			d3_TransformPoint((char*) *(int*) (cand + 0x61), (char*) (*(int*) (cand + 0x61) + 0x4c), p2);
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
		*(pos14_7f4c00*) (a0 + 0x52) = gm_GameTime;
		*(int*) (a0 + 0x70) += 1;
		return;
	case 2:
		if (*(int*) (a0 + 0xec) != -1) {
			rec = gm_StartFilteredEntitySearch(1, 1, *(int*) (a0 + 0xec));
			n = 0;
			if (rec != 0) {
				e = a0 + 0xac;
				while (n < 0x10) {
					if (*(int*) e == *(int*) (rec + 1)) {
						*(int*) e = -1;
						*(int*) (m + 0x28) = *(int*) &gm_GameTime;
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
					n++;
					e += 4;
				}
			}
			*(pos14_7f4c00*) (a0 + 0x52) = gm_GameTime;
			fcn_00500bb0((pos14_7f4c00*) (a0 + 0x52), 0, 10, 0);
			*(int*) (a0 + 0x70) = 1;
			return;
		}
		*(int*) (a0 + 0x70) += 1;
		return;
	case 3:
		rec = he_StartHandlungSearch(1, 0, 0x4f);
		while (rec != 0 && *(int*) (rec + 0xf8) != *(int*) (a0 + 4)) {
			rec = he_fn_Handlung();
		}
		if (rec == 0) {
			fcn_004c30a0(-8, 0, (char*) 0x6a6ab4, -1, 100);
			he_FreeAction(a0);
			return;
		}
		*(pos14_7f4c00*) (a0 + 0x52) = gm_GameTime;
		fcn_00500bb0((pos14_7f4c00*) (a0 + 0x52), 0, 10, 0);
		return;
	case -2:
	case -1:
		he_FreeAction(a0);
		return;
	}
}
