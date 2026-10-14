

#include <string.h>

extern char* g_1052ba4;
extern char g_1052a40[];
char* __cdecl fcn_0044e1e0(char* name, int a, int b);

char* __cdecl fcn_00418b40(const char* name, int a, int b)
{
	char buf[0x100];
	char* o;

	strcpy(buf, name);
	o = fcn_0044e1e0(buf, a, b);
	if (o != 0) {
		*(char**) (o + 0x164) = g_1052ba4;
		g_1052ba4 = o;
		*(char**) (o + 0x160) = g_1052a40;
		*(char**) (*(char**) (o + 0x164) + 0x160) = o;
	}
	return o;
}
