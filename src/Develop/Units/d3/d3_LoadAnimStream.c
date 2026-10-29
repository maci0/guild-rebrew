

#include <stdio.h>
#include <string.h>

extern char g_67ac98[];
extern char g_67b04c[];
extern char* g_1052ba4;
extern char g_1052a40[];

#include "Develop/Units/d3/d3_animation.h"

/* ADDRESS: GOLDTL 0x0044c620 */
char* __cdecl d3_LoadAnimStream(char* name, char* a, int b)
{
	char buf[0x100];
	char* o;

	strcpy(buf, g_67ac98);
	strcat(buf, name);
	o = fcn_00433ba0(a);
	if (o != 0) {
		sprintf(buf, g_67b04c, name);
		return o;
	}
	o = d3_LoadBinaryAnimStream(buf, a, b);
	if (o != 0) {
		*(char**) (o + 0x164) = *(char**) 0x1052ba4;
		*(char**) 0x1052ba4 = o;
		*(char**) (o + 0x160) = (char*) 0x1052a40;
		*(char**) (*(char**) (o + 0x164) + 0x160) = o;
	}
	return o;
}
