// FUNCTION: GOLDTL 0x4aff10
// SIZE: 167

#include <string.h>

typedef struct {
	short v[7];
} stamp14;
// SIZE 0xe

extern stamp14 g_7f4c00;
extern char* g_773da8;

int __cdecl fcn_0064eeec(char*);
void __cdecl fcn_004c5530(void*);

int __cdecl fcn_004aff10(int a1, int a2, char* arg)
{
	char m[0xf8];

	if (*arg != '-')
		return 0;
	if (fcn_0064eeec(arg + 1) > 0) {
		memset(m, 0, sizeof(m));
		m[4] = 0x53;
		*(int*) (m + 8) = *(int*) (g_773da8 + 4);
		*(int*) (m + 0xc) = -1;
		m[0x36] = 1;
		m[0x58] = 0;
		*(stamp14*) (m + 0x28) = g_7f4c00;
		*(short*) (m + 0x2c) = 0xc;
		*(int*) (m + 0x2e) = 0;
		fcn_004c5530(m);
	}
	return 1;
}
