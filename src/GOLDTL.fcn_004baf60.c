// GLOBAL: GOLDTL 0x664e78
extern double g_664e78;
// GLOBAL: GOLD 0x5edbe0
extern double g_664e78;
// GLOBAL: GOLDTL 0x662cf8
extern float g_662cf8;
// GLOBAL: GOLD 0x5ebb40
extern float g_662cf8;
/* Owned (both targets) by src/GOLDTL.fcn_004b6f00.c. */
extern double g_6640e8;

#include <string.h>

int __cdecl fcn_0042e410(int);
void* __cdecl fcn_00508e40(int);
int __cdecl fcn_005c6270(void*, int);
int __cdecl fcn_004bac00(void*, int*, float);
void* __cdecl fcn_00503fe0(int, int, int);
void __cdecl fcn_0051af00(void*, int, int, void*);
void __cdecl fcn_00545e80(int, int, void*, int, int, int, int, int, void*);

// FUNCTION: GOLDTL 0x4baf60
// SIZE: 282
// FUNCTION: GOLD 0x4bab90
// SIZE: 282

int __cdecl fcn_004baf60(void* a1)
{
	float f;
	int v;
	char buf[0x200];
	int n;
	unsigned char* p;
	void* e;
	int r;
	unsigned int len;

	n = fcn_0042e410(0x14) & 0xffff;
	f = (float) (((double) n + g_664e78) * g_6640e8);
	p = fcn_00508e40(*(int*) a1);
	if (p == 0) {
		return 1;
	}
	if (fcn_005c6270(p, 0x290) == 0) {
		if (fcn_004bac00(p, &v, f) != 0) {
			e = fcn_00503fe0(1, 1, v);
			if (e != 0) {
				float t;

				t = f;
				r = (int) (t * g_662cf8);
				fcn_0051af00(buf, *(unsigned short*) ((char*) a1 + 4) + 0x12e7, r, e);
				len = strlen(buf);
				fcn_00545e80(*(int*) ((char*) p + 4), *(int*) ((char*) p + 4),
				    buf, 0x100 < len, 0x603, *(int*) ((char*) e + 1), -1, 0, 0);
				return 0;
			}
		}
	}
	return 0x400;
}
