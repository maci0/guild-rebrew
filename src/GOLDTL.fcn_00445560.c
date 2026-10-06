// FUNCTION: GOLD 0x4495f0
// FUNCTION: GOLDTL 0x445560

#include <string.h>

int __cdecl fcn_00445560(char* s, char** st)
{
	char* p;

	if (st[0] != 0) {
		p = s[0] == '!' ? s + 1 : s;
		if (st[1] != 0) {
			if (strcmp(p, st[0]) == 0 && st[1] == s) {
				st[2] = s;
			}
		} else if (strcmp(p, st[0]) == 0) {
			st[2] = s;
		}
	} else if (st[1] == s) {
		st[2] = s;
	}
	return st[2] != s;
}
