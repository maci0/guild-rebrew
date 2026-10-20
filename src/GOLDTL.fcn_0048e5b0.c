#include <string.h>

typedef struct F8 {
	int mask;
	int b;
} F8;
// SIZE 0x8

typedef struct Msg {
	char kind;
	int a;
	int b;
	int c;
	int d;
	float f;
} Msg;
// SIZE 0x18

int __cdecl fcn_00503fe0(int, int, int, int, int);
char* __cdecl fcn_00502cd0(int, int, int, int, int);
int __cdecl fcn_00495400(int, int, int, void*, void*);
int __cdecl fcn_004efd30(int);
void __cdecl fcn_004c5420(int, int, int, int, int);
void __cdecl fcn_004f08d0(void*);
int __cdecl fcn_0042e410(int);
int __cdecl fcn_004a5e60(char*, int, F8, int, float, int*);
void __cdecl fcn_005015e0(void**, int, int, int);
int __cdecl fcn_004a6210(char*, char*, int);

/* ADDRESS: GOLDTL 0x0048e5b0 */
int __cdecl fcn_0048e5b0(int a0, char* a1, int a2, char* a3, char* a4)
{
	char* p;
	char* e;
	Msg m1;
	Msg m2;
	F8 f;
	int out;
	int r;

	p = a1;
	if (*(char*) (p + 2) == 3) {
		return 0;
	}
	if (a0 != 0x42 && a0 != 0) {
		return 0;
	}
	e = (char*) fcn_00503fe0(2, 5, 0x1e, 4, *(unsigned short*) p);
	if (e == 0) {
		return 0;
	}
	if (fcn_00502cd0(*(int*) (e + 0x5d), 2, 6, 0, 0x256) == 0) {
		m1.kind = 2;
		m1.a = 0x256;
		m1.b = 1;
		m1.f = 0.22f;
		m2.kind = 4;
		m2.a = *(int*) (e + 1);
		m2.b = 1;
		r = fcn_00495400(0x42, *(unsigned short*) p, 1, &m1, &m2);
		if (r != 0) {
			memcpy(a3, &m1, 24);
			memcpy(a4, &m2, 24);
			return r;
		}
		return 0;
	}
	if (fcn_004efd30(*(int*) (e + 1)) == 0 && *(int*) (p + 0x1cc) >= 0) {
		fcn_004c5420(*(int*) (p + 4), 0x1e8, 4, 0x80000000, 0);
		fcn_004f08d0(e);
		return 0;
	}
	a0 = (fcn_0042e410(0x20) & 0xffff) + 0x20;
	f.mask = 0xe07c43b4;
	f.b = 1;
	if (fcn_004a5e60(p, 6, f, 0, (float) a0, &out) == 0) {
		return 0;
	}
	fcn_005015e0((void**) &a1, 0, 0, out);
	if (a1 == 0) {
		return 0;
	}
	if (fcn_004a6210(p, e, a1) == 0) {
		return 0;
	}
	*(char*) a3 = 4;
	*(int*) (a3 + 4) = *(int*) (e + 1);
	*(char*) a4 = 4;
	*(int*) (a4 + 4) = *(int*) (a1 + 1);
	return 0x42;
}
