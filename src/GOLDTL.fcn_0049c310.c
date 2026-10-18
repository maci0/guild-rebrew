#include "client_types.h"
extern pos14_7f4c00 g_7f4c00;
extern unsigned short g_7f4c04;
extern unsigned char g_773d75;

int __cdecl fcn_004f5dd0(int);
int __cdecl fcn_004f5da0(int);
unsigned short __cdecl gm_RandomMod(int);
char* __cdecl gm_StartFilteredEntitySearch(int, int, int);
char* __cdecl gm_AddObjekt(void);
int __cdecl fcn_0050d320(char*, unsigned char);
#include "Develop/DieGildeAddOn/game/spiel.h"
float __cdecl fcn_0050f980(int, int, int);
int __cdecl fcn_005c6270(void*, int);

#define MAXV(a, b) ((a) > (b) ? (a) : (b))
#define MINV(a, b) ((a) < (b) ? (a) : (b))

/* ADDRESS: GOLDTL 0x0049c310 */
int __cdecl fcn_0049c310(int unused, char* e, int busy, char* out, char* kind)
{
	int v1;
	int v3;
	char* list[8];
	int v2;
	int n;
	int h;
	int amt;
	char* p;
	char* t;
	float f1;

	if (busy == 0 && (*(unsigned int*) (e + 4) & 3) == (unsigned int)((*(int*)&g_7f4c00) % 4) &&
	    (*(unsigned int*) (e + 4) & 7) == (unsigned int)(((*(int*)&g_7f4c04) & 0xffff) % 8)) {
		v1 = fcn_004f5dd0(*(int*) (e + 4));
		v2 = fcn_004f5da0(*(int*) (e + 4));
		if (gm_RandomMod(8) + 8 <= v1) {
			n = 0;
			p = gm_StartFilteredEntitySearch(1, 5, 7);
			if (p != 0) {
				do {
					if (*(unsigned short*) (p + 0x27) != 0xffff &&
					    *(unsigned short*) (p + 0x27) != *(unsigned short*) e && !(p[0x5a] & 1)) {
						list[n] = p;
						n++;
					}
					p = gm_AddObjekt();
				} while (p != 0);
				if (n != 0) {
					t = list[gm_RandomMod(n)];
					if (*(int*) (e + 0x194) < 4) {
						v3 = fcn_0050d320(e, g_773d75);
						f1 = gm_WalkEntityChain(*(unsigned short*) e) * 0.005f;
						amt = (int) (v1 * ((200.0f - fcn_0050f980(*(unsigned short*) e,
							*(unsigned short*) (t + 0x27), 1)) * 0.01f) * f1);
						amt = (int) MINV(MAXV(amt * 0.01, 3200.0), 320000.0);
						if (fcn_005c6270(e, 0x2c6) != 0) {
							amt /= 2;
						}
						if (!(amt > v3 * 0.44f)) {
							if (v2 <= 1) {
								v2 = 1;
							}
							out[0] = 4;
							*(int*) (out + 4) = *(int*) (t + 1);
							*(int*) (out + 0x10) = amt;
							*(float*) (out + 0x14) = (float) v2;
							*kind = 0x12;
							return 0x26;
						}
					} else {
						h = *(int*) (e + 0x194) / 2;
						h += h & 1;
						amt = h / 2;
						if (amt > v2) {
							amt = v2;
							h = v2 * 2;
						}
						out[0] = 4;
						*(int*) (out + 4) = *(int*) (t + 1);
						*(int*) (out + 0x10) = h;
						*(float*) (out + 0x14) = (float) amt;
						*kind = 0xf;
						return 0x26;
					}
				}
			}
		}
	}
	return 0;
}
