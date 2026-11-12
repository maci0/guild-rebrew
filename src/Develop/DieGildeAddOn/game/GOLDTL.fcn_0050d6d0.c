/* Select three random free building sites around the entity and report
 * their computed offsets. */

#include <string.h>
typedef struct { int values[3]; } SiteTriple;

extern unsigned char g_773d75;
extern double g_6628f0;
extern double g_6640e8, g_6629c8, g_662ad8, g_662908, g_6653f8, g_662a08;
extern float g_662914, g_662a98;

int __cdecl gm_QueryEntitySum(int, int);
int __cdecl gm_WalkEntityChain(int);
int __cdecl fcn_0050d640(int, int, int, char*);
float __cdecl fcn_0050f980(unsigned int, unsigned int, unsigned int);
int __cdecl fcn_004fa5b0(int, unsigned short*, unsigned int*);
void __cdecl fcn_004c5150(int, int, int, int);
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
	int v17;
	int v18;
	int v21;
	unsigned int v20;
	unsigned int v5;
	unsigned short v3;
	char v2;
	double cap;
	double basis;
	float scratch;
	float ratio;
	float offer;

	v17 = 0;
	v5 = a2;
	if (a1 && a0 && *(short*) (a0 + 0x27) != -1 && a2) {
		v21 = gm_QueryEntitySum(*(int*) (a0 + 0x5d), g_773d75);
		if ((char) a1[1] == 6) {
			if (*(int*) 0x7f4c00 <= 5) {
				v6 = (int) *(unsigned short*) (a0 + 0x27);
				v2 = *(char*) ((unsigned int) v6 * 0x21c + 0x7f4ca2);
				if (v2 != 6 && v2 != 7) {
					cap = (double) gm_WalkEntityChain(*a1) * g_6628f0;
					scratch = (float) v21;
					if ((double) v21 < cap) {
						if (!(cap < 64000.0f))
							cap = 64000.0f;
						v21 = (int) ((double) scratch + cap);
						v8 = (int) cap;
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
				if (v4 >= 1) {
					if (v21 <= v4) {
						v17 = -1;
						*v9 = -1;
					} else {
						*(SiteTriple*) v9 = *(SiteTriple*) v12;
						v17 = -1;
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
			v5 = a2;
		}
		v3 = *(unsigned short*) (a0 + 0x27);
		if (fcn_0050d640((int) v3, 0, 0xffff, v15) <= 8) {
			memset(a3, 0, v5 * 12);
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
			offer = (float) ((double) v17 * ratio);
			cap = (double) v21 * g_662908;
			v17 = (int) (offer < cap ? offer : cap);
			v11 = 0;
			if (a2) {
				offer = (float) v17;
				do {
					v17 = (int) (((double) -(gm_RandomMod(0x1e) & 0xffff)
					              * g_6640e8 + g_6629c8) * offer);
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
						scratch = (float) v18;
						v18 = (int) ((double) scratch -
						    ((double) fcn_0050f980(*a1,
						        *(unsigned short*) (a0 + 0x27), 1) - g_662914)
						    * g_6640e8 * g_662a98);
					}
					v20 = v11 + 1;
					v12 = &a3[v11 * 3];
					v12[2] = v18;
					v12[0] = v17;
					v12[1] = v6;
					v11 = v20;
				} while (v20 < a2);
			}
			if ((char) a1[1] == 6) {
				v17 = 3;
				v12 = (int*) (a0 + 0x71);
				do {

					v17 -= 1;
					*(SiteTriple*) v12 = *(SiteTriple*) a3;
					a3 += 3;
					v12 = (int*) ((char*) v12 + 0xc);
				} while (v17);
			}
			return 3;
		}
	}
	return 0;
}
