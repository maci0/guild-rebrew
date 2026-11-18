

#include <string.h>

// SIZE 0x4
typedef struct {
	unsigned char a;
	unsigned char b;
	unsigned char c;
	unsigned char d;
} Bytes4;

int* __cdecl fcn_004524e0(int n, const char* name, Bytes4 f, float a, int b, void (__cdecl* cb)(void));
void __cdecl fcn_00417870(void);

int* __cdecl fcn_00415e90(int a1, int a2, int v0, int v1, int v2, int v3)
{
	Bytes4 flags;
	int* result;
	int i;

	memset(&flags, 0, sizeof(flags));
	flags.c |= 2;
	flags.a = 0x7f;
	result = fcn_004524e0(200, "Blut", flags, 1.0f, a1, fcn_00417870);
	if (result != 0) {
		result[8] = a2 * 2 | 1;
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
