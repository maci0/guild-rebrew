#include <math.h>

/* Sky/time-of-day blend body: seeds the active slot from g_7f4c04, drives the
 * two host objects 0x7e453c/0x7e4538, then selects a sky texture class by the
 * slot limit and pushes the blended positions to the scene object 0x6b89c0. */

extern int g_7f4c04;
extern int g_7e4534;
extern int g_7e4538;
extern int g_7e453c;
extern int g_7e43a8[0x18];
extern float g_7e4470[];
extern float g_7e44d0[];
extern unsigned char* g_7e4540;
extern unsigned char* g_7e4544;
extern unsigned char* g_7e4548;
extern int g_6b89c0;

int __cdecl fcn_0065f220(const char*, const char*);
unsigned short __cdecl gm_RandomMod(int);
void __cdecl fcn_00416300(int, ...);
void __cdecl fcn_00415510(int, ...);
void __cdecl fcn_004599d0(void*, void*);
void __cdecl fcn_00459980(void*, void*, int, float);
void __cdecl fcn_00459940(void*, void*, float);

/* ADDRESS: GOLDTL 0x00536bb0 */
void __cdecl fcn_00536bb0(void)
{
	float f1;
	float f2;
	float f;
	int lim;
	int idx;
	int i;
	int v1;
	float v2;
	char* name;
	unsigned char* p;

	g_7e4534 = g_7f4c04 & 0xffff;
	idx = g_7e4534;
	if (g_7e453c != 0) {
		fcn_00416300(g_7e453c, 1, 1, g_7e43a8[idx], 1000);
	}
	if (g_7e4538 != 0) {
		i = g_7e43a8[idx];
		if (g_7e453c != 0) {
			if (i & 1) {
				i = i / 5;
			} else {
				i = 0;
			}
		}
		fcn_00415510(g_7e4538, 1, 1, i, 1000);
	}
	f1 = g_7e4470[idx];
	f2 = g_7e44d0[idx];
	lim = g_7e43a8[idx];
	i = g_7e43a8[(idx + 0x17) % 0x18];
	if (lim < i) {
		lim = i;
	}
	i = g_7e43a8[(idx + 1) % 0x18];
	if (lim < i) {
		lim = i;
	}
	if (g_7e453c != 0) {
		fcn_00416300(g_7e453c, 1, 2, (int) (4.0 * f1 * f2 * (double) lim),
		             (int) (-2.0 * f2 * (double) lim), 1000);
	}
	if (g_7e4538 != 0) {
		fcn_00415510(g_7e4538, 1, 2, (int) (0.25 * f1 * f2 * (double) lim),
		             (int) (-0.5 * f2 * (double) lim), 1000);
	}
	if (g_6b89c0 == 0) {
		return;
	}
	f = (float) (lim + 0x96) * (float) sqrt(f1 * f1 + f2 * f2) * 0.125f;
	p = g_7e4544;
	if (p[0x2a] == 0) {
		if (lim < 0x32) {
			i = (int) (unsigned int) gm_RandomMod(4);
			if (fcn_0065f220(*(char**) (p + 0x1c), (char*) (0x6a2600 + i * 0x4c)) == 0) {
				i++;
			}
			name = (char*) (0x6a2600 + i * 0x4c);
		} else if (lim < 0x96) {
			i = (int) (unsigned int) gm_RandomMod(3);
			if (fcn_0065f220(*(char**) (p + 0x1c), (char*) (0x6a2730 + i * 0x4c)) == 0) {
				i++;
			}
			name = (char*) (0x6a2730 + i * 0x4c);
		} else {
			i = (int) (unsigned int) gm_RandomMod(2);
			if (fcn_0065f220(*(char**) (p + 0x1c), (char*) (0x6a2818 + i * 0x4c)) == 0) {
				i++;
			}
			name = (char*) (0x6a2818 + i * 0x4c);
		}
		fcn_004599d0(p, name);
		*(int*) p = *(int*) (name + 0x40);
		((int*) p)[6] = *(int*) (name + 0x44);
		((int*) p)[5] = *(int*) (name + 0x48);
		fcn_00459980((void*) g_6b89c0, p, 0xff, 1500.0f);
	}
	if (p[0x2a] == 0xff) {
		p = g_7e4540;
		if (lim < 0x32) {
			i = (int) (unsigned int) gm_RandomMod(4);
			if (fcn_0065f220(*(char**) (p + 0x1c), (char*) (0x6a2600 + i * 0x4c)) == 0) {
				i++;
			}
			name = (char*) (0x6a2600 + i * 0x4c);
		} else if (lim < 0x96) {
			i = (int) (unsigned int) gm_RandomMod(3);
			if (fcn_0065f220(*(char**) (p + 0x1c), (char*) (0x6a2730 + i * 0x4c)) == 0) {
				i++;
			}
			name = (char*) (0x6a2730 + i * 0x4c);
		} else {
			i = (int) (unsigned int) gm_RandomMod(2);
			if (fcn_0065f220(*(char**) (p + 0x1c), (char*) (0x6a2818 + i * 0x4c)) == 0) {
				i++;
			}
			name = (char*) (0x6a2818 + i * 0x4c);
		}
		fcn_004599d0(p, name);
		*(int*) p = *(int*) (name + 0x40);
		((int*) p)[6] = *(int*) (name + 0x44);
		((int*) p)[5] = *(int*) (name + 0x48);
		fcn_00459980((void*) g_6b89c0, g_7e4544, 0, 1500.0f);
	}
	fcn_00459940((void*) g_6b89c0, g_7e4540, f * 0.75f);
	fcn_00459940((void*) g_6b89c0, g_7e4544, f);
	if (lim == 0) {
		v1 = 0;
		v2 = 2500.0f;
	} else {
		v1 = (lim << 6) / 1000 + 0x60;
		v2 = 1000.0f;
	}
	fcn_00459980((void*) g_6b89c0, g_7e4548, v1, v2);
	fcn_00459940((void*) g_6b89c0, g_7e4548, f * 1.5f);
}
