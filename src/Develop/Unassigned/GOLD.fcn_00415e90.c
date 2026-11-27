

#include <string.h>

// SIZE 0x4
typedef struct {
	unsigned char a;
	unsigned char b;
	unsigned char c;
	unsigned char d;
} Bytes4;

int* __cdecl d3_CreateParticleSystem(int n, const char* name, Bytes4 f, float a, int b, void (__cdecl* cb)(void));
void __cdecl d3_UpdateBloodSprayParticles(void);

int* __cdecl d3_SpawnBlutEffect(int unused, int mode, int v0, int v1, int v2, int v3)
{
	Bytes4 flags;
	int* result;
	int i;

	memset(&flags, 0, sizeof(flags));
	flags.c |= 2;
	flags.a = 0x7f;
	result = d3_CreateParticleSystem(200, "Blut", flags, 1.0f, unused, d3_UpdateBloodSprayParticles);
	if (result != 0) {
		result[8] = mode * 2 | 1;
		result[0] = v0;
		result[1] = v1;
		result[2] = v2;
		result[3] = v3;
		for (i = 0; i < result[0x34]; i++) {
			*((unsigned char*) result[10] + i * 0x54 + 0x51) &= 0xfe;
		}
	}
	return result;
}
