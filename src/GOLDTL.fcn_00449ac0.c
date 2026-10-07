// FUNCTION: GOLD 0x0044c530
// FUNCTION: GOLDTL 0x449ac0

#include <string.h>

extern int g_1041d08;
extern int g_6b7fdc;
extern char g_6b85c0[];

int __cdecl fcn_0042f690(char*, int, int, char*);

void __cdecl fcn_00449ac0(char* a, char* b)
{
	char buf[0x100];

	strcpy(buf, "*");
	strcat(buf, a);
	strcat(buf, b);
	fcn_0042f690(buf, g_1041d08, g_6b7fdc, g_6b85c0);
}
