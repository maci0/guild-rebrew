extern int g_68bfb8;

// FUNCTION: GOLD 0x0052fdb0
// SIZE: 115
// FUNCTION: GOLDTL 0x5358e0
// SIZE: 115

#include <string.h>

int __cdecl fcn_004c5790(int, char*);
int __cdecl fcn_004c4450(int);
void __cdecl fcn_00533a40(char*);
void __cdecl fcn_005373e0(int, int);

void __cdecl fcn_005358e0(char* name)
{
	char buf[0x7c];
	int s;

	memset(buf, 0, sizeof(buf));
	strcpy(buf, name);
	s = fcn_004c5790(0xe, buf);
	while (fcn_004c4450(s) == 0) {
		fcn_00533a40(name);
		fcn_005373e0(0, g_68bfb8 | 0x210000);
	}
}
