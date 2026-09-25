// FUNCTION: GOLD 0x4010b0
// SIZE: 208
// FUNCTION: GOLDTL 0x004010b0
// SIZE: 208

#include <string.h>

extern char g_6b5b20[];
int __cdecl fcn_004308a0(char* buf, int size, int f);
void __cdecl fcn_0066080a(char* s);

char* __cdecl fcn_004010b0(int f)
{
	int i;
	char* p;

	while (fcn_004308a0(g_6b5b20, 0x100, f)) {
		i = strlen(g_6b5b20) - 1;
		while (i > -1 && (g_6b5b20[i] == '\n' || g_6b5b20[i] == '\r' ||
				  g_6b5b20[i] == '\t' || g_6b5b20[i] == ' ')) {
			i--;
		}
		if (i < 0) {
			continue;
		}
		g_6b5b20[i + 1] = 0;
		p = g_6b5b20;
		while (*p != 0 && (*p == '\n' || *p == '\r' || *p == '\t' || *p == ' ')) {
			p++;
		}
		if (*p != 0 && *p != ';') {
			fcn_0066080a(p);
			return p;
		}
	}
	return 0;
}
