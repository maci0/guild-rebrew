#include <math.h>

/* SIZE 0x4 */
typedef struct {
	unsigned char r;
	unsigned char g;
	unsigned char f0 : 1;
	unsigned char f1 : 7;
	unsigned char x;
} V43a3f0;

extern char* g_772f24;
extern int g_68b79c;
extern volatile int g_6b7fac;
extern char* ch_ContextCharacters[32];
extern float g_6628a4;

extern float g_662cf8;
extern double g_6640e8;
extern double g_664ee8;
extern double g_662ad8;

char* __cdecl gm_LookupWeaponSpec(int);
unsigned int __cdecl cut_RandMod(unsigned int);
void __cdecl cm_RequestReduceLifespan(int, int, int);
char* __cdecl gm_GetEquippedCombatGear(char*);
int __cdecl gm_GetEntityControlMask(int, char*);
unsigned char __cdecl d3_SetSubtreeVisible(int, unsigned char);
void __cdecl fcn_0043a3f0(char*, char*, V43a3f0);
int __cdecl gm_EntitiesDifferByOwnerPtr(char*, char*);
float __cdecl fcn_004cefb0(char*, char*);
char* __cdecl gm_FindEntitySlot(char*);
char* __cdecl gm_LookupEntityRecordIn32SlotTable(int);
int __cdecl CompareVector3WithinTolerance(float*, float*, float);
float __cdecl d3_ComputeYawToTarget(char*, float*);
void __cdecl d3_SetObjectEulerRotation(char*, int, float, int);
void __cdecl fcn_004cfca0(void);


/* Ages the effect timers of the 32 tracked records, then drives their
   proximity/visibility states against the current selection. */
/* ADDRESS: GOLDTL 0x004d0070 */
void __cdecl cut_UpdateCombatEffects(void)
{
	V43a3f0 c;
	char** p;
	char** q;
	char* e;
	char* d;
	char* o;
	char* e34;
	char* g34;
	char* g;
	char* s;
	unsigned int num;
	float v;
	float best;
	int found;
	int t;

	if (*(int*) (g_772f24 + 4) == g_68b79c) {
		if ((unsigned int) g_6b7fac % 350 == 0) {
			for (p = ch_ContextCharacters; (int) p < (int) &ch_ContextCharacters[32]; p++) {
				e = *p;
				if (e == 0) {
					continue;
				}

				if (*(unsigned char*) (e + 8) > 4 || *(unsigned char*) (e + 8) <= 0) {
					continue;
				}


				if (--*(unsigned char*) (e + 8) == 1) {
					*(unsigned char*) (e + 8) = 100;
					continue;
				}
				d = gm_LookupWeaponSpec(0x16e);
				num = cut_RandMod((unsigned int) ((unsigned char) d[6] - (unsigned char) d[5]));
				num += (unsigned char) d[5];
				cm_RequestReduceLifespan(*(int*) (e + 4), (int) ((double) num * *(float*) (e + 0x1c) * 0.01), (int) *(unsigned char*) (e + 8));
			}
		}
	}
	for (p = ch_ContextCharacters; (int) p < (int) &ch_ContextCharacters[32]; p++) {
		e = *p;
		found = 0;
		if (e == 0) {
			continue;
		}
		s = gm_GetEquippedCombatGear(e);
		if (s != 0 && *(int*) s == 0x172) {
			t = 0;
			if (g_772f24 != 0) {
				t = gm_GetEntityControlMask((int) *(unsigned short*) g_772f24, e);
			}
			o = *(char**) (e + 0x184);
			if (t & 0x800) {
				e34 = *(char**) (*(char**) (e + 0x184) + 0x34);
				d3_SetSubtreeVisible((int) e34, 1);
				c.r = 0x80;
				c.g = 0;
				c.f0 = 0;
				c.f1 = 0;
				c.x = 0;
				e34 = *(char**) (*(char**) (e + 0x184) + 0x34);
				*(unsigned char*) (e34 + 0x215) &= 0x7f;
				e34 = *(char**) (*(char**) (e + 0x184) + 0x34);
				fcn_0043a3f0(e34, *(char**) (e34 + 0x1cc), c);
			} else {
				best = 999999.0f;
				for (q = ch_ContextCharacters; (int) q < (int) &ch_ContextCharacters[32]; q++) {
					g = *q;
					if (g == 0) {
						continue;
					}
					if (gm_EntitiesDifferByOwnerPtr(e, g) == 0) {
						continue;
					}
					if (*(char*) (g + 8) == 0) {
						continue;
					}
					v = fcn_004cefb0(e, *(char**) (*(char**) (g + 0x184) + 0x34));
					if (v < 100.0f) {
						found = 1;
						if (v < best) {
							best = v;
						}
					}
				}
				e34 = *(char**) (*(char**) (e + 0x184) + 0x34);
				d3_SetSubtreeVisible((int) e34, (unsigned char) found);
				if (found) {
					t = (int) (255.0f - best * 0.01f * 255.0f);
					c.r = (unsigned char) t;
					c.g = 0;
					c.f0 = 0;
					c.f1 = 0;
					c.x = 0;
					e34 = *(char**) (*(char**) (e + 0x184) + 0x34);
					*(unsigned char*) (e34 + 0x215) &= 0x7f;
					e34 = *(char**) (*(char**) (e + 0x184) + 0x34);
					fcn_0043a3f0(e34, *(char**) (e34 + 0x1cc), c);
				} else {
					goto other_effect;
				}
			}
			o = *(char**) (e + 0x184);
			*(unsigned char*) (*(char**) (o + 0x34) + 0x215) |= 0x80;
		}
	other_effect:
		s = gm_FindEntitySlot(e);
		if (s != 0 && *(int*) (s + 4) == 2 && *(char*) (s + 0x1d) != 0) {
			g = gm_LookupEntityRecordIn32SlotTable(*(int*) (s + 0x10));
			if (g != 0) {
				o = *(char**) (e + 0x184);
				e34 = *(char**) (*(char**) (e + 0x184) + 0x34);
				g34 = *(char**) (*(char**) (g + 0x184) + 0x34);
				if (CompareVector3WithinTolerance((float*) (e34 + 0x4c), (float*) (g34 + 0x4c), 10.0f) == 0) {
					e34 = *(char**) (*(char**) (e + 0x184) + 0x34);
					g34 = *(char**) (*(char**) (g + 0x184) + 0x34);
					v = d3_ComputeYawToTarget(e34, (float*) (g34 + 0x4c));
					o = *(char**) (e + 0x184);
					s = (char*) *(int*) (o + 0x128);
					if (s == 0 || (*(char*) (s + 9) != 0x2d && *(char*) (s + 9) != 0x3a)) {
						if (g_664ee8 < (double) fabs(v)) {
							e34 = *(char**) (*(char**) (e + 0x184) + 0x34);
							d3_SetObjectEulerRotation(e34, *(int*) (e34 + 0x84), *(float*) (e34 + 0x88) + v * 0.25, *(int*) (e34 + 0x8c));
						}
					}
				}
			}
		}
	}
	fcn_004cfca0();
}
unsigned char _dpad_7e3a58[2056];
#if defined(REBREW_SERVER) || defined(REBREW_GOLD)
unsigned char _dpad_7e4260[324];
#else
/* Reference gaps only; the emitted objects inside the span keep their own rows. */
unsigned char _dpad_7e42e4[28];
unsigned char _dpad_7e4324[92];
unsigned char _dpad_7e4384[28];
#endif
