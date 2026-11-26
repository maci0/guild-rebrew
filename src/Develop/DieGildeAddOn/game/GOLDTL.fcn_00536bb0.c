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
void __cdecl d3_SetRainEffectOptions(int, ...);
void __cdecl fcn_004599d0(void*, void*);
void __cdecl fcn_00459980(void*, void*, unsigned char, float);
void __cdecl d3_SetSkyLayerScrollSpeed(void*, void*, float);

/* ADDRESS: GOLDTL 0x00536bb0 */
void __cdecl fcn_00536bb0(void)
{
	float f1;
	float f2;
	float f;
	int lim;
	int i;
	char* name;

	g_7e4534 = g_7f4c04 & 0xffff;
	if (g_7e453c != 0) {
		fcn_00416300(g_7e453c, 1, 1, g_7e43a8[g_7e4534], 1000);
	}
	if (g_7e4538 != 0) {
		if (g_7e453c != 0) {
			if (g_7e43a8[g_7e4534] & 1) {
				d3_SetRainEffectOptions(g_7e4538, 1, 1, g_7e43a8[g_7e4534] / 5, 1000);
			} else {
				d3_SetRainEffectOptions(g_7e4538, 1, 1, 0, 1000);
			}
		} else {
			d3_SetRainEffectOptions(g_7e4538, 1, 1, g_7e43a8[g_7e4534], 1000);
		}
	}
	f1 = g_7e4470[g_7e4534];
	f2 = g_7e44d0[g_7e4534];
	lim = g_7e43a8[(g_7e4534 + 0x17) % 0x18];
	if (lim <= g_7e43a8[g_7e4534]) {
		lim = g_7e43a8[g_7e4534];
	}
	if (lim <= g_7e43a8[(g_7e4534 + 1) % 0x18]) {
		lim = g_7e43a8[(g_7e4534 + 1) % 0x18];
	}
	if (g_7e453c != 0) {
		fcn_00416300(g_7e453c, 1, 2, (int) ((double) -f1 * (double) lim * 2.0),
		             (int) ((double) -f2 * (double) lim * 2.0), 1000);
	}
	if (g_7e4538 != 0) {
		d3_SetRainEffectOptions(g_7e4538, 1, 2, (int) ((double) -f1 * (double) lim * 0.5),
		             (int) ((double) -f2 * (double) lim * 0.5), 1000);
	}
	if (g_6b89c0 == 0) {
		return;
	}
	f = (float) (sqrt(f1 * f1 + f2 * f2) * (lim + 0x96) * 0.125);

	if (g_7e4544[0x2a] == 0) {
		if (lim < 0x32) {
			i = (int) (unsigned int) gm_RandomMod(4);
			if (fcn_0065f220(*(char**) (g_7e4544 + 0x1c), (char*) (0x6a2600 + i * 0x4c)) == 0) {
				i++;
			}
			name = (char*) (0x6a2600 + i * 0x4c);
		} else if (lim < 0x96) {
			i = (int) (unsigned int) gm_RandomMod(3);
			if (fcn_0065f220(*(char**) (g_7e4544 + 0x1c), (char*) (0x6a2730 + i * 0x4c)) == 0) {
				i++;
			}
			name = (char*) (0x6a2730 + i * 0x4c);
		} else {
			i = (int) (unsigned int) gm_RandomMod(2);
			if (fcn_0065f220(*(char**) (g_7e4544 + 0x1c), (char*) (0x6a2818 + i * 0x4c)) == 0) {
				i++;
			}
			name = (char*) (0x6a2818 + i * 0x4c);
		}
		fcn_004599d0(g_7e4544, name);
		*(int*) g_7e4544 = *(int*) (name + 0x40);
		((int*) g_7e4544)[6] = *(int*) (name + 0x44);
		((int*) g_7e4544)[5] = *(int*) (name + 0x48);
		fcn_00459980((void*) g_6b89c0, g_7e4544, 0xff, 1500.0f);
	}
	if (g_7e4544[0x2a] == 0xff) {
		if (lim < 0x32) {
			i = (int) (unsigned int) gm_RandomMod(4);
			if (fcn_0065f220(*(char**) (g_7e4540 + 0x1c), (char*) (0x6a2600 + i * 0x4c)) == 0) {
				i++;
			}
			name = (char*) (0x6a2600 + i * 0x4c);
		} else if (lim < 0x96) {
			i = (int) (unsigned int) gm_RandomMod(3);
			if (fcn_0065f220(*(char**) (g_7e4540 + 0x1c), (char*) (0x6a2730 + i * 0x4c)) == 0) {
				i++;
			}
			name = (char*) (0x6a2730 + i * 0x4c);
		} else {
			i = (int) (unsigned int) gm_RandomMod(2);
			if (fcn_0065f220(*(char**) (g_7e4540 + 0x1c), (char*) (0x6a2818 + i * 0x4c)) == 0) {
				i++;
			}
			name = (char*) (0x6a2818 + i * 0x4c);
		}
		fcn_004599d0(g_7e4540, name);
		*(int*) g_7e4540 = *(int*) (name + 0x40);
		((int*) g_7e4540)[6] = *(int*) (name + 0x44);
		((int*) g_7e4540)[5] = *(int*) (name + 0x48);
		fcn_00459980((void*) g_6b89c0, g_7e4544, 0, 1500.0f);
	}
	d3_SetSkyLayerScrollSpeed((void*) g_6b89c0, g_7e4540, (float) (f * 0.75));
	d3_SetSkyLayerScrollSpeed((void*) g_6b89c0, g_7e4544, f);
	if (lim == 0) {
		fcn_00459980((void*) g_6b89c0, g_7e4548, 0, 2500.0f);
	} else {
		fcn_00459980((void*) g_6b89c0, g_7e4548, (unsigned char) ((lim << 6) / 1000 + 0x60), 1000.0f);
	}
	d3_SetSkyLayerScrollSpeed((void*) g_6b89c0, g_7e4548, (float) (f * 1.5));
}
