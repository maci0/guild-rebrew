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

int __cdecl gm_StartFilteredEntitySearch(int, int, int, int, int);
char* __cdecl fcn_00502cd0(int, int, int, int, int);
int __cdecl ai_SelectBestMethod(int, int, int, void*, void*);
int __cdecl fcn_004efd30(int);
void __cdecl cm_RequestChangeBits(int, int, int, int, int);
void __cdecl cm_SendSlotAddNCta(void*);
int __cdecl gm_RandomMod(int);
int __cdecl fcn_004a5e60(char*, int, F8, int, float, int*);
void __cdecl gm_ResolveEntityById(void**, int, int, int);
int __cdecl gm_ComputeCannonShot(char*, char*, int);

/* ADDRESS: GOLDTL 0x0048e5b0 */
int __cdecl ai_StartCannonTower(int a0, char* a1, int a2, char* firstAction, char* a4)
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
	e = (char*) gm_StartFilteredEntitySearch(2, 5, 0x1e, 4, *(unsigned short*) p);
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
		r = ai_SelectBestMethod(0x42, *(unsigned short*) p, 1, &m1, &m2);
		if (r != 0) {
			memcpy(firstAction, &m1, 24);
			memcpy(a4, &m2, 24);
			return r;
		}
		goto result;
	}
	if (fcn_004efd30(*(int*) (e + 1)) == 0 && (*(int*) (p + 0x1cc) & 0x80000000) == 0) {
		cm_RequestChangeBits(*(int*) (p + 4), 0x1e8, 4, 0x80000000, 0);
		cm_SendSlotAddNCta(e);
		return 0;
	}

	f.mask = 0xe07c43b4;
	f.b = 1;
	if (fcn_004a5e60(p, 6, f, 0, (float) ((gm_RandomMod(0x20) & 0xffff) + 0x20), &out) == 0) {
		return 0;
	}
	gm_ResolveEntityById((void**) &a1, 0, 0, out);
	if (a1 == 0) {
		return 0;
	}
	if (gm_ComputeCannonShot(p, e, a1) == 0) {
		return 0;
	}
	*(char*) firstAction = 4;
	*(int*) (firstAction + 4) = *(int*) (e + 1);
	*(char*) a4 = 4;
	*(int*) (a4 + 4) = *(int*) (a1 + 1);
	r = 0x42;
result:
	return r;
}
