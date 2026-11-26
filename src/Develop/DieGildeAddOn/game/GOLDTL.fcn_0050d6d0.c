/* Select three random free building sites around the entity and report
 * their computed offsets. */

#include <string.h>
#include "Develop/DieGildeAddOn/game/game_timestamp.h"
typedef struct { int values[3]; } SiteTriple;

extern unsigned char g_773d75;
extern double g_6628f0;
extern double g_6640e8, g_6629c8, g_662ad8, g_662908, g_6653f8, g_662a08;
extern float g_662914, g_662a98;

int __cdecl gm_QueryEntitySum(int, unsigned char);
int __cdecl gm_WalkEntityChain(unsigned short);
int __cdecl fcn_0050d640(int, int, int, char*);
float __cdecl fcn_0050f980(unsigned int, unsigned int, unsigned int);
int __cdecl gm_CheckPrivilege(int, unsigned short*, unsigned int*);
void __cdecl fcn_004c5150(int, int, unsigned char, int);
unsigned short __cdecl gm_RandomMod(int);

/* ADDRESS: GOLDTL 0x0050d6d0 */
unsigned int __cdecl fcn_0050d6d0(int a0, unsigned short* a1, unsigned int a2,
                                  int* a3)
{
	char v15[36];
	unsigned int v16[136];
	float ratio;
	int v4;
	int v6;
	unsigned int v8;
	int* v9;
	unsigned int loopIndex;
	int* v12;
	int v21;
	int total;
	int price;
	int flag;
	int v18;
	char v2;
	double cap;
	float offer;

	flag = 0;
	if (a1 && a0 && *(unsigned short*) (a0 + 0x27) != 0xffff && a2) {
		v21 = gm_QueryEntitySum(*(int*) (a0 + 0x5d), g_773d75);
		if ((char) a1[1] == 6) {
			if (gm_GameTime.a < 6) {
				v6 = (int) *(unsigned short*) (a0 + 0x27);
				v2 = *(char*) ((unsigned int) v6 * 0x21c + 0x7f4ca2);
				if (v2 != 6 && v2 != 7) {
					float have;

					offer = gm_WalkEntityChain(*a1) * 0.2;
					have = (float) v21;
					if (have < offer) {
						if (!(offer < 64000.0f))
							offer = 64000.0f;
						v21 = (int) (have + offer);
						v8 = (int) offer;
						fcn_004c5150(*(int*) (a0 + 1), 0xffffffff,
						             g_773d75, v8);
					}
				}
			}
			v12 = (int*) (a0 + 0x71);
			v9 = a3;
			for (v18 = 0; v18 < 3; v18++, v12 += 3, v9 += 3) {
				v4 = *v12;
				if (v4 > 0) {
					if (v4 < v21) {
						*(SiteTriple*) v9 = *(SiteTriple*) v12;
						flag = -1;
					} else {
						flag = -1;
						*v9 = -1;
					}
				} else if (v4 == -1) {
					flag = -1;
					*v9 = -1;
				} else {
					*v9 = -1;
				}
			}
			if (flag == -1) {
				return 3;
			}
		}
		if (fcn_0050d640(*(unsigned short*) (a0 + 0x27), 0, 0xffff, v15) < 9) {
			memset(a3, 0, a2 * 12);
			total = gm_WalkEntityChain(*a1);
			memset(v16, 0, 0x220);
			ratio = 0.3f;
			v16[0] = 1;
			if (gm_CheckPrivilege(0xf, a1, v16) & 2) {
				ratio = 0.6f;
			} else if (gm_CheckPrivilege(0xb, a1, v16) & 2) {
				/* Preserve the native 0x3ee66667 coefficient. */
				ratio = 0.45000002f;
			}
			ratio = (float) total * ratio;
			cap = (double) v21 * g_662908;
			total = (int) (ratio < cap ? ratio : cap);
			for (loopIndex = 0; loopIndex < a2; loopIndex++) {
				price = -gm_RandomMod(0x1e);
				price = (int) (((double) price * 0.01 + g_6629c8) * (float) total);
				if (loopIndex == 0) {
					price = (int) ((double) price * 0.25);
				} else if (loopIndex == 1) {
					price = (int) ((double) price * g_662908);
				}
				v6 = gm_RandomMod(6) + 2;
				cap = *(int*) (a0 + 0x65) * g_6653f8;
				v18 = (int) (cap + (*(int*) (a0 + 0x65) * g_662a08 - cap)
				              * ((float) v6 * 0.16666667f));
				v2 = *(char*) ((unsigned int) *(unsigned short*) (a0 + 0x27) *
				                   0x21c +
				               0x7f4ca2);
				if (v2 != 6 && v2 != 7 &&
				    ((char) a1[1] == 6 || (char) a1[1] == 7)) {
					offer = (float) v18;
					v18 = (int) (offer -
					    (float) (((double) (fcn_0050f980(*a1, *(unsigned short*) (a0 + 0x27), 1) - g_662914)
					    * 0.01) * g_662a98));
				}
				a3[loopIndex * 3 + 2] = v18;
				a3[loopIndex * 3] = price;
				a3[loopIndex * 3 + 1] = v6;
			}
			if ((char) a1[1] == 6) {
				SiteTriple* src;
				SiteTriple* dst;
				v18 = 3;
				src = (SiteTriple*) a3;
				dst = (SiteTriple*) (a0 + 0x71);
				do {
					*dst++ = *src++;
				} while (--v18);
			}
			return 3;
		}
	}
	return 0;
}
