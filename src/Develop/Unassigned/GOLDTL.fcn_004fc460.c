extern float g_6628a8;
extern float g_6628a8;
extern char g_99f5e0[];
extern char g_99f5e0[];
extern float g_773d4c;
extern float g_773d4c;



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
