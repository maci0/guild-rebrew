__declspec(dllimport) unsigned long __stdcall timeGetTime(void);

extern int g_772f78;
extern int g_772f7c;
extern int g_772f80;
extern int g_772f84;
extern int g_772f88;
extern int g_772f8c;
extern int g_68dec0[];

void __cdecl srand(unsigned int seed);
unsigned short __cdecl gm_RandomMod(unsigned short n);
void __cdecl fcn_004ecb40(void);
#include "g_772f90.h"

extern int g_772fd8;
extern Draw772* g_772fdc;

unsigned short __cdecl gm_RandomMod(unsigned short n);

extern int g_772fe0;
extern Rec772fe4* g_772fe4;

unsigned short __cdecl gm_RandomMod(unsigned short n);
int __cdecl fcn_004ec9a0(int p);
int __cdecl fcn_004ec950(int p, int id);

/* ADDRESS: GOLD 0x004ead20 */
/* ADDRESS: GOLDTL 0x004ecaa0 */
void __cdecl fcn_004ecaa0(int reseed)
{
	if (reseed) {
		*(unsigned short*) &g_772f8c = (unsigned short) (timeGetTime() % 0x7fff + 1);
	}
	srand((unsigned short) g_772f8c);
	fcn_004ecb40();
	if (reseed) {
		g_772f78 = gm_RandomMod(0x19);
		g_772f7c = g_68dec0[gm_RandomMod(8)];
		g_772f80 = gm_RandomMod(0x19);
		g_772f84 = g_68dec0[gm_RandomMod(8)];
		g_772f88 = 0;
	}
}

/* ADDRESS: GOLD 0x004eadc0 */
/* ADDRESS: GOLDTL 0x004ecb40 */
void __cdecl fcn_004ecb40(void)
{
	int n;
	int i;
	int a;
	int b;
	Draw772 tmp;

	n = g_772fd8 * 2;
	for (i = 0; i < n; i++) {
		a = gm_RandomMod((unsigned short) g_772fd8);
		b = gm_RandomMod((unsigned short) g_772fd8);
		if (a != b) {
			tmp = g_772fdc[a];
			g_772fdc[a] = g_772fdc[b];
			g_772fdc[b] = tmp;
		}
	}
}

/* ADDRESS: GOLD 0x004eaea0 */
/* ADDRESS: GOLDTL 0x004ecc20 */
Rec772fe4* __cdecl fcn_004ecc20(int p)
{
	int step;
	int idx;
	int n;

	if (fcn_004ec9a0(p)) {
		step = gm_RandomMod((unsigned short) g_772fe0) + 1;
		while (step % g_772fe0 == 0) {
			step++;
		}
		idx = gm_RandomMod((unsigned short) g_772fe0);
		n = g_772fe0;
		while (n != 0) {
			if (!fcn_004ec950(p, g_772fe4[idx].key)) {
				return &g_772fe4[idx];
			}
			n--;
			idx = (idx + step) % g_772fe0;
		}
	}
	return 0;
}
