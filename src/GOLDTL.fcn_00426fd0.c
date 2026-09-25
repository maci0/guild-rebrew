// FUNCTION: GOLDTL 0x00426fd0
// SIZE: 48

#include <stdio.h>

int __cdecl fcn_00426d50(char* path);

int __cdecl fcn_00426fd0(const char* name)
{
	char path[0x100];

	sprintf(path, "%s%s", "x:\\engine\\gfx\\scripts\\", name);
	return fcn_00426d50(path);
}
