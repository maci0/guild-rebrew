// FUNCTION: GOLD 0x004168e0
// SIZE: 151
// FUNCTION: GOLDTL 0x004185a0
// SIZE: 151

#include <string.h>

// SIZE 0x4
typedef struct {
	unsigned char a;
	unsigned char b;
	unsigned char c;
	unsigned char d;
} Bytes4;

int* __cdecl fcn_004524e0(int n, const char* name, Bytes4 f, int a, int b, void (__cdecl* cb)(void));
void __cdecl fcn_004526d0(int* s, float* pos);
void __cdecl fcn_00418210(void);

int* __cdecl fcn_004185a0(int a1, float* pos, int n, int a4, int v0, int v1, int v2, int v3, int v4, int v5, int v6, int v7)
{
	Bytes4 f;
	int* s;

	memset(&f, 0, sizeof(f));
	f.c |= 2;
	f.a = 0x7f;
	s = fcn_004524e0(n, "Erdbrocken_an0", f, a4, a1, fcn_00418210);
	if (s != 0) {
		fcn_004526d0(s, pos);
		s[0] = v0;
		s[1] = v1;
		s[2] = v2;
		s[3] = v3;
		s[4] = v4;
		s[5] = v5;
		s[6] = v6;
		s[8] = 1;
		s[9] = v7;
	}
	return s;
}
