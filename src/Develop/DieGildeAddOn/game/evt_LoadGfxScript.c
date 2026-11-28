

#include <stdio.h>

int __cdecl evt_LoadScript(char* path);

/* ADDRESS: GOLDDE 0x00421aa0 */
int __cdecl evt_LoadGfxScript(const char* name)
{
	char path[0x100];

	sprintf(path, "%s%s", "x:\\engine\\gfx\\scripts\\", name);
	return evt_LoadScript(path);
}
