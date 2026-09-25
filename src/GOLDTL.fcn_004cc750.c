// FUNCTION: GOLD 0x004cbbd0
// SIZE: 204
// FUNCTION: GOLDTL 0x4cc750
// SIZE: 204

#include <string.h>

extern char g_7e3a60[];
extern char g_68b300[];
extern unsigned short g_774970;
extern char g_7f4ca4[];
extern int g_6b7fac;
extern int g_6a2c1c;

char* __cdecl fcn_0064d470(char*, char*);

int __cdecl fcn_004cc750(char* x, char* out)
{
	char* p;
	int n;
	int found;
	int i;

	n = 0;
	found = 0;
	p = fcn_0064d470(g_7e3a60, g_68b300);
	if (p != 0) {
		while (p != 0) {
			n++;
			p = fcn_0064d470(p + 2, g_68b300);
		}
		if (n > 5)
			g_7e3a60[0] = 0;
	}
	for (i = 0; i < 8; i++) {
		if (*(int*) (x + 0x10 + i * 4) == *(int*) (g_7f4ca4 + g_774970 * 0x21c)) {
			found = 1;
			break;
		}
	}
	if (out != 0 || found != 0) {
		strcat(g_7e3a60, x + 0x30);
		g_6a2c1c = g_6b7fac;
		if (out != 0) {
			out[0] = 1;
			out[1] = 0;
			*(int*) (out + 6) = 0;
		}
	}
	return 0;
}
