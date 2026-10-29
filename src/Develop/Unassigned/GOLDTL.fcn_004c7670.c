


#include <string.h>

extern char* cm_LoadBuf;
extern unsigned int g_1005820;

int __cdecl fcn_004c7670(char* a1, char* a2)
{
	memcpy(cm_LoadBuf + g_1005820, a1 + 0x10, 0x80);
	g_1005820 += 0x80;
	if (a2 != 0) {
		*a2 = 1;
	}
	return 0;
}
