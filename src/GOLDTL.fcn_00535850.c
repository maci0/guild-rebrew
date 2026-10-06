extern char g_6b5c60[];

// FUNCTION: GOLD 0x0052fd20
// FUNCTION: GOLDTL 0x535850

#include <string.h>

int __cdecl fcn_004c5790(int, char*);
int __cdecl fcn_004c4450(int);
void __cdecl fcn_00533a40(char*);
void __cdecl fcn_005373e0(int, int);

void __cdecl fcn_00535850(int flags, char* name)
{
	char buf[0x7c];
	int s;

	memset(buf, 0, sizeof(buf));
	strcpy(buf, name);
	s = fcn_004c5790(0xe, buf);
	flags |= 0x300000;
	while (fcn_004c4450(s) == 0) {
		fcn_00533a40(name);
		fcn_005373e0(0, flags);
	}
	fcn_00533a40(g_6b5c60);
}
