


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

int* __cdecl d3_SpawnRockDebrisEffect(int a1, float* pos, int n, int a4, int v0, int v1, int v2, int v3, int v4, int v5, int v6, int v7)
{
	Bytes4 effectFlags;
	int* effectState;

	memset(&effectFlags, 0, sizeof(effectFlags));
	effectFlags.c |= 2;
	effectFlags.a = 0x7f;
	effectState = fcn_004524e0(n, "Erdbrocken_an0", effectFlags, a4, a1, fcn_00418210);
	if (effectState != 0) {
		fcn_004526d0(effectState, pos);
		effectState[0] = v0;
		effectState[1] = v1;
		effectState[2] = v2;
		effectState[3] = v3;
		effectState[4] = v4;
		effectState[5] = v5;
		effectState[6] = v6;
		effectState[8] = 1;
		effectState[9] = v7;
	}
	return effectState;
}
