// FUNCTION: GOLDTL 0x004177d0
// SIZE: 145

#include <string.h>

// SIZE 0x4
typedef struct {
	unsigned char a;
	unsigned char b;
	unsigned char c;
	unsigned char d;
} Bytes4;

int* __cdecl fcn_004524e0(int n, const char* name, Bytes4 f, float a, int b, void (__cdecl* cb)(void));
void __cdecl fcn_004526d0(int* s, float* pos);
void __cdecl fcn_00417270(int* s, float a, float b, float c);
void __cdecl fcn_004172e0(void);

int* __cdecl fcn_004177d0(int a1, int n)
{
	Bytes4 f;
	float v[4];
	int* s;

	memset(&f, 0, sizeof(f));
	f.c |= 2;
	f.a = 0x7f;
	s = fcn_004524e0(n, "Ref-Map-Linse", f, 7.0f, a1, fcn_004172e0);
	if (s != 0) {
		v[0] = -37.0f;
		v[1] = 35.0f;
		v[2] = 0.0f;
		v[3] = 0.0f;
		fcn_00417270(s, 0.9f, 4.0f, -5.0f);
		fcn_004526d0(s, v);
	}
	return s;
}
