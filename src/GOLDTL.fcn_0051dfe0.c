extern int g_6a23a8;
extern char g_665c18[5][64];

// FUNCTION: GOLDTL 0x51dfe0
// SIZE: 144

#include <string.h>

int __cdecl fcn_0051dfe0(char* s)
{
	char buf[64];
	int i;

	strcpy(buf, s);
	_strupr(buf);
	g_6a23a8 = 0xffff;
	for (i = 0; i < 5; i++) {
		if (strcmp(g_665c18[i], buf) == 0) {
			g_6a23a8 = i;
			return i;
		}
	}
	return 0xffff;
}
