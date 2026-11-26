#include <math.h>
#include <string.h>

typedef struct OBJECT_COLOR { unsigned char a, b, c, d; } OBJECT_COLOR;

extern volatile int g_6b7fac;
extern char* ch_ContextCharacters[32];
extern float g_662910;
extern float g_662cf8;
extern double g_6640e8;

char* __cdecl fcn_004ce590(int);
unsigned int __cdecl cut_RandMod(unsigned int);
void __cdecl cm_RequestReduceLifespan(int, int, int);
char* __cdecl gm_GetEquippedCombatGear(char*);
int __cdecl fcn_004cef70(int, char*);
unsigned char __cdecl d3_SetSubtreeVisible(int, unsigned char);
void __cdecl d3_ChangeObjectTransparency(char*, char*, OBJECT_COLOR);
int __cdecl gm_EntitiesDifferByOwnerPtr(char*, char*);
float __cdecl fcn_004ce1b0(char*, char*);
char* __cdecl fcn_004ceb40(char*);
char* __cdecl gm_LookupEntityRecordIn32SlotTable(int);
int __cdecl CompareVector3WithinTolerance(float*, float*, float);
float __cdecl d3_ComputeYawToTarget(char*, float*);
void __cdecl d3_SetObjectEulerRotation(char*, int, float, int);
void __cdecl fcn_004cee20(void);

/* ADDRESS: GOLD 0x004cf000 */
void __cdecl fcn_004cf000(void)
{
	OBJECT_COLOR color;
	int i;
	int j;
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
	unsigned char c;

	if (*(int*) ((*(char**) 0x6f0d74) + 4) == (*(int*) 0x60cb3c)) {
		if ((unsigned int) g_6b7fac % 350 == 0) {
			for (i = 0; i < 32; i++) {
				e = ch_ContextCharacters[i];
				if (e == 0) {
					continue;
				}
				c = *(unsigned char*) (e + 8);
				if (c > 4 || c <= 0) {
					continue;
				}
				c -= 1;
				*(unsigned char*) (e + 8) = c;
				if (c == 1) {
					*(unsigned char*) (e + 8) = 100;
					continue;
				}
				d = fcn_004ce590(0x16e);
				num = cut_RandMod((unsigned int) ((unsigned char) d[6] - (unsigned char) d[5])) + (unsigned char) d[5];
				t = (int) ((double) num * *(float*) (e + 0x1c) * 0.01);
				cm_RequestReduceLifespan(*(int*) (e + 4), t, (int) *(unsigned char*) (e + 8));
			}
		}
	}
	for (i = 0; i < 32; i++) {
		found = 0;
		e = ch_ContextCharacters[i];
		if (e == 0) {
			continue;
		}
		s = gm_GetEquippedCombatGear(e);
		if (s != 0 && *(int*) s == 0x172) {
			t = 0;
			if ((*(char**) 0x6f0d74) != 0) {
				t = fcn_004cef70((int) *(unsigned short*) (*(char**) 0x6f0d74), e);
			}
			o = *(char**) (e + 0x184);
			if (t & 0x800) {
				memset(&color, 0, sizeof(color));
				color.c = 0; color.a = 0x80;
				e34 = *(char**) (*(char**) (e + 0x184) + 0x34);
				d3_SetSubtreeVisible((int) e34, 1);
				e34 = *(char**) (*(char**) (e + 0x184) + 0x34);
				*(unsigned char*) (e34 + 0x212) &= 0xfd;
				e34 = *(char**) (*(char**) (e + 0x184) + 0x34);
				d3_ChangeObjectTransparency(e34, *(char**) (e34 + 0x1cc), color);
			} else {
				best = 999999.0f;
				for (j = 0; j < 32; j++) {
					g = ch_ContextCharacters[j];
					if (g == 0) {
						continue;
					}
					if (gm_EntitiesDifferByOwnerPtr(e, g) == 0) {
						continue;
					}
					if (*(char*) (g + 8) == 0) {
						continue;
					}
					v = fcn_004ce1b0(e, *(char**) (*(char**) (g + 0x184) + 0x34));
					if (v < g_662cf8) {
						found = 1;
						if (v < best) {
							best = v;
						}
					}
				}
				e34 = *(char**) (*(char**) (e + 0x184) + 0x34);
				d3_SetSubtreeVisible((int) e34, (unsigned char) found);
				if (found) {
					t = (int) (255.0f - g_662910 * best * 255.0f);
					memset(&color, 0, sizeof(color));
					color.c = 0; color.a = (unsigned char) t;
					e34 = *(char**) (*(char**) (e + 0x184) + 0x34);
					*(unsigned char*) (e34 + 0x212) &= 0xfd;
					e34 = *(char**) (*(char**) (e + 0x184) + 0x34);
					d3_ChangeObjectTransparency(e34, *(char**) (e34 + 0x1cc), color);
				} else {
					goto other_effect;
				}
			}
			o = *(char**) (e + 0x184);
			*(unsigned char*) (*(char**) (o + 0x34) + 0x212) |= 2;
		}
	other_effect:
		s = fcn_004ceb40(e);
		if (s != 0 && *(int*) (s + 4) == 2 && *(char*) (s + 0x1d) != 0) {
			g = gm_LookupEntityRecordIn32SlotTable(*(int*) (s + 0x10));
			if (g != 0) {
				o = *(char**) (e + 0x184);
				g34 = *(char**) (*(char**) (g + 0x184) + 0x34);
				e34 = *(char**) (*(char**) (e + 0x184) + 0x34);
				if (CompareVector3WithinTolerance((float*) (e34 + 0x4c), (float*) (g34 + 0x4c), 10.0f) == 0) {
					g34 = *(char**) (*(char**) (g + 0x184) + 0x34);
					e34 = *(char**) (*(char**) (e + 0x184) + 0x34);
					v = d3_ComputeYawToTarget(e34, (float*) (g34 + 0x4c));
					o = *(char**) (e + 0x184);
					s = (char*) *(int*) (o + 0x128);
					if (s == 0 || (*(char*) (s + 9) != 0x2d && *(char*) (s + 9) != 0x3a)) {
						if (0.08 < (double) fabs(v)) {
							double d;
							d = v * 0.25;
							e34 = *(char**) (o + 0x34);
							d3_SetObjectEulerRotation(e34, *(int*) (e34 + 0x84), d + *(float*) (e34 + 0x88), *(int*) (e34 + 0x8c));
						}
					}
				}
			}
		}
	}
	fcn_004cee20();
}
