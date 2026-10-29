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
extern int g_6b7fac;
extern char* g_7e4260[32];
extern float g_6628a4;
extern float g_662910;
extern float g_662cf8;
extern double g_6640e8;
extern double g_664ee8;
extern double g_662ad8;

char* __cdecl fcn_004ce590(int);
int __cdecl fcn_004e6cb0(unsigned int);
void __cdecl fcn_004c6880(int, int, int);
char* __cdecl fcn_004ce610(char*);
int __cdecl fcn_004cef70(int, char*);
unsigned char __cdecl fcn_00442d50(int, unsigned char);
void __cdecl fcn_0043a3f0(char*, char*, V43a3f0);
int __cdecl fcn_004ce270(char*, char*);
float __cdecl fcn_004cefb0(char*, char*);
char* __cdecl fcn_004ceb40(char*);
char* __cdecl gm_LookupEntityRecordById(int);
int __cdecl fcn_00451840(float*, float*, float);
float __cdecl fcn_00444700(char*, float*);
void __cdecl fcn_00438d70(char*, int, float, int);
void __cdecl fcn_004cfca0(void);


/* Ages the effect timers of the 32 tracked records, then drives their
   proximity/visibility states against the current selection. */
/* ADDRESS: GOLDTL 0x004d0070 */
void __cdecl fcn_004d0070(void)
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
	__int64 num;
	float v;
	float best;
	int found;
	int t;

	if (*(int*) (g_772f24 + 4) == g_68b79c) {
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
				num = fcn_004e6cb0((unsigned int) ((unsigned char) d[6] - (unsigned char) d[5]));
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
			if (g_772f24 != 0) {
				t = fcn_004cef70((int) *(unsigned short*) g_772f24, e);
			}
			o = *(char**) (e + 0x184);
			if (t & 0x800) {
				e34 = o + 0x34;
				fcn_00442d50((int) e34, 1);
				c.r = 0x80;
				c.g = 0;
				c.f0 = 0;
				c.f1 = 0;
				c.x = 0;
				*(unsigned char*) (e34 + 0x215) &= 0x7f;
				fcn_0043a3f0(e34, *(char**) (e34 + 0x1cc), c);
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
					v = fcn_004cefb0(e, *(char**) (*q + 0x184) + 0x34);
					if (v < g_662cf8) {
						found = 1;
						if (v < best) {
							best = v;
						}
					}
				}
				e34 = o + 0x34;
				fcn_00442d50((int) e34, (unsigned char) found);
				if (found) {
					t = (int) (g_6628a4 - best * g_662910 * g_6628a4);
					c.r = (unsigned char) t;
					c.g = 0;
					c.f0 = 0;
					c.f1 = 0;
					c.x = 0;
					*(unsigned char*) (e34 + 0x215) &= 0x7f;
					fcn_0043a3f0(e34, *(char**) (e34 + 0x1cc), c);
				}
			}
			o = *(char**) (e + 0x184);
			*(unsigned char*) (o + 0x34 + 0x215) |= 0x80;
		}
		s = fcn_004ceb40(e);
		if (s != 0 && *(int*) (s + 4) == 2 && *(char*) (s + 0x1d) != 0) {
			g = gm_LookupEntityRecordById(*(int*) (s + 0x10));
			if (g != 0) {
				o = *(char**) (e + 0x184);
				e34 = o + 0x34;
				g34 = *(char**) (g + 0x184) + 0x34;
				if (fcn_00451840((float*) (e34 + 0x4c), (float*) (g34 + 0x4c), 10.0f) == 0) {
					v = fcn_00444700((char*) (e34 + 0x4c), (float*) (g34 + 0x4c));
					s = (char*) *(int*) (o + 0x128);
					if (s == 0 || (*(char*) (s + 9) != 0x2d && *(char*) (s + 9) != 0x3a)) {
						if (g_664ee8 < (double) fabs(v)) {
							fcn_00438d70(e34, *(int*) (e34 + 0x84), *(float*) (e34 + 0x88) + v * g_662ad8, *(int*) (e34 + 0x8c));
						}
					}
				}
			}
		}
	}
	fcn_004cfca0();
}
unsigned char _dpad_7e3a58[2056];
unsigned char _dpad_7e4260[324];
