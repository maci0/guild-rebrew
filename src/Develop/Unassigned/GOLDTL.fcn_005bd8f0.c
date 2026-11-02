#include <string.h>
extern char g_6ac3f4[];
extern char g_6ac3e4[];

int __cdecl fcn_005bd8f0(char* name, int* o)
{
	if (strstr(name, g_6ac3f4) != 0) {
		o[o[98]] = (int) name;
		o[o[98] + 48] = 0x17;
		o[98]++;
	}
	else if (strstr(name, g_6ac3e4) != 0) {
		o[o[98]] = (int) name;
		o[o[98] + 48] = 0x18;
		o[98]++;
	}
	return o[98] < 0x30;
}
