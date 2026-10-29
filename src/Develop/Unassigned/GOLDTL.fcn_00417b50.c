

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

int* __cdecl fcn_00417b50(int a1, int a2, int v0, int v1, int v2, int v3)
{
	Bytes4 f;
	int* s;
	int i;

	memset(&f, 0, sizeof(f));
	f.c |= 2;
	f.a = 0x7f;
	s = fcn_004524e0(200, "Blut", f, 1.0f, a1, fcn_00417870);
	if (s != 0) {
		s[8] = a2 * 2 | 1;
		s[0] = v0;
		s[1] = v1;
		s[2] = v2;
		s[3] = v3;
		for (i = 0; i < s[0x36]; i++) {
			*((unsigned char*) s[10] + i * 0x54 + 0x51) &= 0xfe;
		}
	}
	return s;
}
