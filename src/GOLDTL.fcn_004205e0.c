// FUNCTION: GOLD 0x00424250
// SIZE: 112
// FUNCTION: GOLDTL 0x004205e0
// SIZE: 112

#include <string.h>

// SIZE 0x128
typedef struct {
	char name[0x100];
	int handle;
	unsigned char active;
	unsigned char b105;
	unsigned char b106;
	unsigned char b107;
	int f108;
	int f10c;
	char pad110[0x128 - 0x110];
} Chan;

extern Chan g_6b71b0[10];

Chan* __cdecl fcn_004205e0(const char* name)
{
	int i;

	for (i = 0; i < 10; i++) {
		if (strcmp(g_6b71b0[i].name, name) == 0) {
			return &g_6b71b0[i];
		}
	}
	return 0;
}
