// GLOBAL: GOLDTL 0x14cc360
extern char g_14cc360[];
// GLOBAL: GOLD 0xf8aae0
extern char g_14cc360[];
// FUNCTION: GOLDTL 0x420760
// SIZE: 22
// FUNCTION: GOLD 0x00478860
// SIZE: 22
// fcn_00478860 — strcpy into the fixed buffer (GOLDTL 0x14cc360 / GOLD 0xf8aae0).

#include <string.h>

void __cdecl fcn_00478860(char* a)
{
	strcpy(g_14cc360, a);
}
