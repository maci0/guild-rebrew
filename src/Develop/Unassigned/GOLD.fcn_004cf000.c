#include <math.h>

extern int g_6b7fac;
extern char* g_7e4260[32];
extern float g_662cf8;
extern double g_6640e8;

char* __cdecl fcn_004ce590(int);
unsigned int __cdecl cut_RandMod(unsigned int);
void __cdecl fcn_004c6880(int, int, int);
char* __cdecl fcn_004ce610(char*);
int __cdecl fcn_004cef70(int, char*);
unsigned char __cdecl fcn_00442d50(int, unsigned char);
void __cdecl fcn_0043d430(char*, char*, unsigned int);
int __cdecl fcn_004ce270(char*, char*);
float __cdecl fcn_004ce1b0(char*, char*);
char* __cdecl fcn_004ceb40(char*);
char* __cdecl gm_LookupEntityRecordIn32SlotTable(int);
int __cdecl CompareVector3WithinTolerance(float*, float*, float);
float __cdecl fcn_00448ac0(char*, float*);
void __cdecl fcn_00438d70(char*, int, float, int);
void __cdecl fcn_004cee20(void);

/* ADDRESS: GOLD 0x004cf000 */
void __cdecl fcn_004cf000(void)
{
	unsigned int color;
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

	if (*(int*) ((*(char**) 0x6f0d74) + 4) == (*(int*) 0x60cb3c)) {
		if ((unsigned int) g_6b7fac % 350 == 0) {
			for (p = g_7e4260; p < &g_7e4260[32]; p++) {
				e = *p;
				if (e == 0) {
					continue;
				}
				t = *(unsigned char*) (e + 8);
				if (t > 4 || t == 0) {
					continue;
				}
				t -= 1;
				*(unsigned char*) (e + 8) = (unsigned char) t;
				if (t == 1) {
					*(unsigned char*) (e + 8) = 100;
					continue;
				}
				d = fcn_004ce590(0x16e);
				num = cut_RandMod((unsigned int) ((unsigned char) d[6] - (unsigned char) d[5]));
				num += (unsigned char) d[5];
				fcn_004c6880(*(int*) (e + 4), (int) ((double) num * *(float*) (e + 0x1c) * g_6640e8), (int) *(unsigned char*) (e + 8));
			}
		}
	}
	for (p = g_7e4260; p < &g_7e4260[32]; p++) {
		e = *p;
		if (e == 0) {
			continue;
		}
		s = fcn_004ce610(e);
		if (s != 0 && *(int*) s == 0x172) {
			t = 0;
			if ((*(char**) 0x6f0d74) != 0) {
				t = fcn_004cef70((int) *(unsigned short*) (*(char**) 0x6f0d74), e);
			}
			o = *(char**) (e + 0x184);
			if (t & 0x800) {
				e34 = *(char**) (*(char**) (e + 0x184) + 0x34);
				fcn_00442d50((int) e34, 1);
				color = 0x80;
				e34 = *(char**) (*(char**) (e + 0x184) + 0x34);
				*(unsigned char*) (e34 + 0x212) &= 0xfd;
				e34 = *(char**) (*(char**) (e + 0x184) + 0x34);
				fcn_0043d430(e34, *(char**) (e34 + 0x1cc), color);
			} else {
				best = 999999.0f;
				found = 0;
				for (q = g_7e4260; q < &g_7e4260[32]; q++) {
					if (*q == 0) {
						continue;
					}
					if (fcn_004ce270(e, *q) == 0) {
						continue;
					}
					if (*(char*) (*q + 8) == 0) {
						continue;
					}
					v = fcn_004ce1b0(e, *(char**) (*(char**) (*q + 0x184) + 0x34));
					if (v < g_662cf8) {
						found = 1;
						if (v < best) {
							best = v;
						}
					}
				}
				e34 = *(char**) (*(char**) (e + 0x184) + 0x34);
				fcn_00442d50((int) e34, (unsigned char) found);
				if (found) {
					t = (int) ((*(float*) 0x5eb784) - best * (*(float*) 0x5eb7f0) * (*(float*) 0x5eb784));
					color = (unsigned char) t;
					e34 = *(char**) (*(char**) (e + 0x184) + 0x34);
					*(unsigned char*) (e34 + 0x212) &= 0xfd;
					e34 = *(char**) (*(char**) (e + 0x184) + 0x34);
					fcn_0043d430(e34, *(char**) (e34 + 0x1cc), color);
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
				e34 = *(char**) (*(char**) (e + 0x184) + 0x34);
				g34 = *(char**) (*(char**) (g + 0x184) + 0x34);
				if (CompareVector3WithinTolerance((float*) (e34 + 0x4c), (float*) (g34 + 0x4c), 10.0f) == 0) {
					e34 = *(char**) (*(char**) (e + 0x184) + 0x34);
					g34 = *(char**) (*(char**) (g + 0x184) + 0x34);
					v = fcn_00448ac0(e34, (float*) (g34 + 0x4c));
					o = *(char**) (e + 0x184);
					s = (char*) *(int*) (o + 0x128);
					if (s == 0 || (*(char*) (s + 9) != 0x2d && *(char*) (s + 9) != 0x3a)) {
						if ((*(double*) 0x5edc48) < (double) fabs(v)) {
							e34 = *(char**) (*(char**) (e + 0x184) + 0x34);
							fcn_00438d70(e34, *(int*) (e34 + 0x84), *(float*) (e34 + 0x88) + v * (*(double*) 0x5eb9b0), *(int*) (e34 + 0x8c));
						}
					}
				}
			}
		}
	}
	fcn_004cee20();
}
