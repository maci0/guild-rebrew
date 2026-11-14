/* Select three random free building sites around the entity and report
 * their computed offsets. */

#include <string.h>
typedef struct { int values[3]; } SiteTriple;

extern unsigned char g_773d75;
extern double g_6628f0;
extern double g_6640e8, g_6629c8, g_662ad8, g_662908, g_6653f8, g_662a08;
extern float g_662914, g_662a98;

int __cdecl gm_QueryEntitySum(int, unsigned char);
int __cdecl gm_WalkEntityChain(unsigned short);
int __cdecl fcn_0050d640(int, int, int, char*);
float __cdecl fcn_0050f980(unsigned int, unsigned int, unsigned int);
int __cdecl fcn_004fa5b0(int, unsigned short*, unsigned int*);
void __cdecl fcn_004c5150(int, int, unsigned char, int);
int __cdecl gm_RandomMod(int);

/* ADDRESS: GOLDTL 0x0050d6d0 */
unsigned int __cdecl fcn_0050d6d0(int a0, unsigned short* a1, unsigned int a2,
                                  int* a3)
{
	char v15[36];
	unsigned int v16[136];
	int v4;
	int v6;
	unsigned int v8;
	int* v9;
	unsigned int v11;
	int* v12;
	int v21;
	int v17;
	int v18;
	char v2;
	double cap;
	double basis;
	float ratio;
	float offer;

	v17 = 0;
	if (a1 && a0 && *(short*) (a0 + 0x27) != -1 && a2) {
		v21 = gm_QueryEntitySum(*(int*) (a0 + 0x5d), g_773d75);
		if ((char) a1[1] == 6) {
			if (*(int*) 0x7f4c00 < 6) {
				v6 = (int) *(unsigned short*) (a0 + 0x27);
				v2 = *(char*) ((unsigned int) v6 * 0x21c + 0x7f4ca2);
				if (v2 != 6 && v2 != 7) {
					offer = gm_WalkEntityChain(*a1) * g_6628f0;
					ratio = (float) v21;
					if (ratio < offer) {
						if (!(offer < 64000.0f))
							offer = 64000.0f;
						v21 = (int) (ratio + offer);
						v8 = (int) offer;
						fcn_004c5150(*(int*) (a0 + 1), 0xffffffff,
						             g_773d75, v8);
					}
				}
			}
			v12 = (int*) (a0 + 0x71);
			v18 = 3;
			v9 = a3;
			do {
				v4 = *v12;
				if (v4 > 0) {
					if (v4 < v21) {
						*(SiteTriple*) v9 = *(SiteTriple*) v12;
						v17 = -1;
					} else {
						v17 = -1;
						*v9 = -1;
					}
				} else if (v4 == -1) {
					v17 = -1;
					*v9 = -1;
				} else {
					*v9 = -1;
				}
				v12 = (int*) ((char*) v12 + 0xc);
				v9 += 3;
				v18 -= 1;
			} while (v18);
			if (v17 == -1) {
				return 3;
			}
		}
		if (fcn_0050d640(*(unsigned short*) (a0 + 0x27), 0, 0xffff, v15) < 9) {
			memset(a3, 0, a2 * 12);
			v17 = gm_WalkEntityChain(*a1);
			memset(v16, 0, 0x220);
			v16[0] = 1;
			ratio = 0.3f;
			if (fcn_004fa5b0(0xf, a1, v16) & 2) {
				ratio = 0.6f;
			} else if (fcn_004fa5b0(0xb, a1, v16) & 2) {
				/* Preserve the native 0x3ee66667 coefficient. */
				ratio = 0.45000002f;
			}
			ratio = (float) ((double) ratio * v17);
			cap = (double) v21 * g_662908;
			v17 = (int) (ratio < cap ? ratio : cap);
			offer = (float) v17;
			for (v11 = 0; v11 < a2; v11++) {
				v17 = -(gm_RandomMod(0x1e) & 0xffff);
				v17 = (int) (((double) v17 * g_6640e8 + g_6629c8) * offer);
				if (v11 == 0) {
					v17 = (int) ((double) v17 * g_662ad8);
				} else if (v11 == 1) {
					v17 = (int) ((double) v17 * g_662908);
				}
				v6 = (gm_RandomMod(6) & 0xffff) + 2;
				basis = (double) *(int*) (a0 + 0x65);
				cap = basis * g_6653f8;
				v18 = (int) (cap + (basis * g_662a08 - cap)
				              * ((float) v6 * 0.16666667f));
				v2 = *(char*) ((unsigned int) *(unsigned short*) (a0 + 0x27) *
				                   0x21c +
				               0x7f4ca2);
				if (v2 != 6 && v2 != 7 &&
				    ((char) a1[1] == 6 || (char) a1[1] == 7)) {
					ratio = (float) v18;
					v18 = (int) (ratio -
					    (float) (((double) (fcn_0050f980(*a1,
					        *(unsigned short*) (a0 + 0x27), 1) - g_662914)
					    * g_6640e8) * g_662a98));
				}
				a3[v11 * 3 + 2] = v18;
				a3[v11 * 3] = v17;
				a3[v11 * 3 + 1] = v6;
			}
			if ((char) a1[1] == 6) {
				SiteTriple* src;
				SiteTriple* dst;
				v17 = 3;
				src = (SiteTriple*) a3;
				dst = (SiteTriple*) (a0 + 0x71);
				do {
					*dst++ = *src++;
				} while (--v17);
			}
			return 3;
		}
	}
	return 0;
}
