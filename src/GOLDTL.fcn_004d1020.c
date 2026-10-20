#include <string.h>

/* SIZE 0x2c */
typedef struct {
	int f0;
	int f4;
	int f8;
	int fc;
	int f10;
	int f14;
	int f18;
	char f1c;
	char pad[0xf];
} Msg2c;

extern int g_67a370;
extern int g_14a9a04;
extern int g_14a9a08;
extern int g_14a9a0c;

char* __cdecl fcn_004ce610(char* x);
char* __cdecl fcn_004ce680(char* a1);
char* __cdecl fcn_004ceac0(char* rec, char* e);
char __cdecl fcn_0045b990(char* map, float* pos, int* col, int* row, float* height);
void __cdecl fcn_00533a40(char* a);
int __cdecl fcn_004c67c0(int a1, void* a2);

/* ADDRESS: GOLDTL 0x004d1020 */
int __cdecl fcn_004d1020(char* a1, char* e, char* obj, int unused4, int unused5)
{
	Msg2c m;
	int col;
	int row;
	float height;
	char* x;
	char* rec;
	char* map;
	int kind;
	int v;

	kind = *(int*) (g_67a370 + 0xb0);
	if (e == 0) {
		return -1;
	}
	x = fcn_004ce610(e);
	if (obj == 0) {
		return -1;
	}
	map = *(char**) (obj + 0x184);
	if (*(int*) (map + 0x34) == 0) {
		return -1;
	}
	if (fcn_0045b990((char*) kind, (float*) (*(int*) (map + 0x34) + 0x4c), &col, &row, &height) == 0) {
		return -1;
	}
	rec = fcn_004ceac0(a1, e);
	if (rec == 0) {
		return -1;
	}
	*(char*) (rec + 0x1c) = 0;
	*(char*) (rec + 0xc) = 0;
	memcpy(&m, rec, 0x2c);
	if (x == 0) {
		goto plain;
	}
	v = *(int*) x;
	if (v == 0x154 || v == 0x156 || v == 0x158 || v == 0x16e || v == 0x172 || v == 0) {
plain:
		m.f10 = *(int*) (unused4 + 4);
		m.f0 = *(int*) (e + 4);
		m.f4 = 2;
	} else if (v == 0x15e || v == 0x160) {
		rec = fcn_004ce680(e);
		if (rec != 0 && *(int*) (rec + 0x20) <= 0) {
			fcn_00533a40((char*) g_14a9a04);
			return -1;
		}
		m.f0 = *(int*) (e + 4);
		m.f10 = *(int*) (unused4 + 4);
		m.f14 = col;
		m.f18 = row;
		m.f4 = 2;
	} else if (v == 0x174) {
		rec = fcn_004ce680(e);
		if (rec != 0 && *(int*) (rec + 0x20) <= 0) {
			fcn_00533a40((char*) g_14a9a08);
			return -1;
		}
		m.f0 = *(int*) (e + 4);
		m.f10 = 0;
		m.f14 = col;
		m.f18 = row;
		m.f4 = 2;
	} else if (v == 0x176) {
		rec = fcn_004ce680(e);
		if (rec != 0 && *(int*) (rec + 0x20) <= 0) {
			fcn_00533a40((char*) g_14a9a0c);
			return -1;
		}
		m.f10 = 0;
		m.f14 = col;
		m.f18 = row;
		m.f0 = *(int*) (e + 4);
		m.f4 = 2;
	}
	if (*(char*) (e + 0x1c4) == 1 || *(char*) (e + 0x1c4) == 2 || *(char*) (e + 0x1c4) == 3) {
		m.f1c = 1;
	}
	return fcn_004c67c0(*(int*) (a1 + 0x10), &m);
}
