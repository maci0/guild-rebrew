#include <string.h>
extern int g_773d40;
extern char g_67bd30[];
extern char g_67a930[];

void __cdecl fcn_005007f0(char* s)
{
	if (strstr(s, g_67bd30) != 0 || strstr(s, g_67a930) != 0) {
		g_773d40++;
	}
}
