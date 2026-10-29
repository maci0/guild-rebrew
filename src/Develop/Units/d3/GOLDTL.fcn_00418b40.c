

#include <string.h>

extern char* g_1052ba4;
extern char g_1052a40[];
#include "Develop/Units/d3/d3_animation.h"

char* __cdecl fcn_00418b40(const char* name, char* a, int b)
{
	char buf[0x100];
	char* o;

	strcpy(buf, name);
	o = d3_LoadBinaryAnimStream(buf, a, b);
	if (o != 0) {
		*(char**) (o + 0x164) = g_1052ba4;
		g_1052ba4 = o;
		*(char**) (o + 0x160) = g_1052a40;
		*(char**) (*(char**) (o + 0x164) + 0x160) = o;
	}
	return o;
}
