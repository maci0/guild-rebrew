


#include <string.h>

extern char* cm_LoadBuf;
extern unsigned int g_1005820;

int __cdecl fcn_004c7670(char* src, char* out)
{
	memcpy(cm_LoadBuf + g_1005820, src + 0x10, 0x80);
	g_1005820 += 0x80;
	if (out != 0) {
		*out = 1;
	}
	return 0;
}
