// FUNCTION: GOLDTL 0x00417180

#include <string.h>

// SIZE 0x4
typedef struct {
	unsigned char a;
	unsigned char b;
	unsigned char c;
	unsigned char d;
} Bytes4;

// SIZE 0xc
typedef struct {
	float x;
	float y;
	float z;
} V3;

// SIZE 0xd4
typedef struct {
	V3 pos;
	float h;
	int p[4];
	int pad20;
	int mode;
	char pad28[0xd0 - 0x28];
	int kind;
} System;

extern float g_662d70[4];
System* __cdecl fcn_004524e0(int n, const char* name, Bytes4 f, int a, char* e, void (__cdecl* cb)(void));
void __cdecl fcn_004526d0(System* s, float* pos);
void __cdecl fcn_00416d50(void);

System* __cdecl fcn_00417180(char* e, const char* name, unsigned char flag, int kind, V3* pos, int n, int unused, int a, int p0, int p1, int p2, int p3)
{
	System* s;
	Bytes4 f;

	s = 0;
	if (e != 0 && *(char**) (e + 0x1cc) != 0 && *(char**) (*(char**) (e + 0x1cc) + 0x318) != 0) {
		memset(&f, 0, sizeof(f));
		f.a = 0x7f;
		f.c = (flag & 1) | 2;
		s = fcn_004524e0(n, name, f, a, e, fcn_00416d50);
		if (s != 0) {
			fcn_004526d0(s, g_662d70);
			s->pos.x = pos->x;
			s->pos.y = pos->y;
			s->pos.z = pos->z;
			s->mode = 2;
			s->h = *(float*) (*(char**) (*(char**) (e + 0x1cc) + 0x318) + 0x1d4);
			s->pos.y = s->h + s->pos.y;
			s->p[0] = p0;
			s->p[1] = p1;
			s->p[2] = p2;
			s->p[3] = p3;
			s->kind = kind;
			s->h = s->h * 0.75f;
		}
	}
	return s;
}
