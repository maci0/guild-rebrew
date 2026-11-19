extern char g_67553c[];



int __cdecl fcn_0064d41a(char*, char*, ...);
void __cdecl d3_RemoveObjectAnimation(char*, char*);
#include "Develop/Units/d3/d3_animation.h"

void __cdecl ch_ReleaseMorphAnimation(char* p)
{
	char buf[0x60];
	char* x;

	if (*(int*) (p + 0x7c) != 0) {
		fcn_0064d41a(buf, g_67553c, p);
		d3_RemoveObjectAnimation(*(char**) (*(char**) (p + 0x34) + 0x1ec) + 0xf4, buf);
		x = d3_FindAnimByName(buf);
		d3_ReleaseAnim(x, 1);
		*(int*) (p + 0x7c) = 0;
	}
}
