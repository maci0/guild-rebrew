#include <string.h>

extern char* g_772524;
extern int g_1015ea4;
extern int g_1040494;
extern int g_67d380;
extern int g_67d384;
extern int g_772548;
extern int g_772544;
extern char s_67d474[];

int __cdecl fcn_00465950(char* name);
char* __cdecl fcn_00466190(int id);
char* __cdecl fcn_0047b620(char* font, int c);
void __cdecl fcn_0047ccd0(int x, int y, int surf, char* font, int c);
void __cdecl fcn_0047cbf0(int x, int y, int surf, char* font, int c);
void __cdecl fcn_0047cba0(int x, int y, int surf, char* font, int c);

// FUNCTION: GOLDTL 0x46bbc0
// SIZE: 312
void __cdecl fcn_0046bbc0(int x, int y, int surf, char* text, unsigned char flags)
{
	int x0;
	int i;
	unsigned char c;
	char* g;

	x0 = x;
	if (g_772524 == 0) {
		g_772524 = fcn_00466190(fcn_00465950(s_67d474));
	}
	g_1015ea4 = *(unsigned short*) (g_772524 + 8);
	for (i = 0; i < (int) strlen(text); i++) {
		c = text[i];
		g = fcn_0047b620(g_772524, c);
		x -= *(unsigned short*) (g + 0x11);
		if (c != '~') {
			if (c != ' ') {
				if (flags & 2) {
					fcn_0047ccd0(x, y, surf, g_772524, c);
				} else if (flags & 1) {
					fcn_0047cbf0(x, y, surf, g_772524, c);
				} else {
					fcn_0047cba0(x, y, surf, g_772524, c);
				}
				x += *(unsigned short*) (g + 0x15) + g_67d384;
			} else {
				x += g_67d380;
			}
		}
		if (x >= g_1040494) {
			break;
		}
	}
	g_772548 = g_1015ea4;
	g_772544 = x - x0;
}
