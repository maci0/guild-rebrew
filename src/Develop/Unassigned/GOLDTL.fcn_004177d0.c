

#include <string.h>

// SIZE 0x4
typedef struct {
	unsigned char a;
	unsigned char b;
	unsigned char c;
	unsigned char d;
} Bytes4;

int* __cdecl fcn_004524e0(int n, const char* name, Bytes4 f, float a, int b, void (__cdecl* cb)(void));
void __cdecl d3_SetEffectPosition(int* s, float* pos);
void __cdecl d3_InitLensFlareParticles(int* s, float a, float b, float c);
void __cdecl fcn_004172e0(void);

int* __cdecl d3_CreateLensFlareEmitter(int a1, int n)
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
		d3_InitLensFlareParticles(s, 0.9f, 4.0f, -5.0f);
		d3_SetEffectPosition(s, v);
	}
	return s;
}
