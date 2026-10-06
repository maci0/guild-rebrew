// GLOBAL: GOLDTL 0x6628a8
extern float g_6628a8;
// GLOBAL: GOLD 0x5eb788
extern float g_6628a8;
// GLOBAL: GOLDTL 0x99f5e0
extern char g_99f5e0[];
// GLOBAL: GOLD 0x91b4c0
extern char g_99f5e0[];
// GLOBAL: GOLDTL 0x773d4c
extern float g_773d4c;
// GLOBAL: GOLD 0x6f1b9c
extern float g_773d4c;
// FUNCTION: GOLD 0x004f9e00
// FUNCTION: GOLDTL 0x4fc460

#include <string.h>

#pragma intrinsic(memcpy, memset)

float __cdecl fcn_004fc460(char* p)
{
	float v;

	if (p == 0) {
		return *(float*) ((char*)&g_6628a8);
	}
	memcpy(p, (void*) g_99f5e0, 40);
	v = *(float*) (p + 0x24);
	*(int*) (p + 0x18) = *(int*) ((char*)&g_773d4c);
	return v;
}
