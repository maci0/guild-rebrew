extern int g_67a370;

char __cdecl fcn_0043ac80(char* a, char on);
void __cdecl fcn_004379a0(int list, int a, int mask, char(__cdecl* fn)(char*, char), int arg);
#include "client_lighting.h"

/* ADDRESS: GOLDTL 0x0043ace0 */
void __cdecl fcn_0043ace0(unsigned char a)
{
	fcn_004379a0(g_67a370, 0, 6, fcn_0043ac80, a);
	UpdateSceneLighting(1);
}
