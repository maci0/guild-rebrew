#include <string.h>
extern int g_67a370;

void __cdecl fcn_004379a0(int, char*, int, void*, void*);
int __cdecl fcn_00445560(char*, char**);

/* ADDRESS: GOLD 0x004495f0 */
/* ADDRESS: GOLDTL 0x00445560 */
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

/* ADDRESS: GOLDTL 0x00445600 */
char* __cdecl fcn_00445600(char* o, int flags, char* ptr, char* name)
{
	char* st[3];
	int saved;

	if (ptr == 0 && name == 0) {
		return 0;
	}
	st[1] = ptr;
	st[0] = name;
	st[2] = 0;
	if (o != 0) {
		saved = *(int*) (o + 0x1f4);
		*(int*) (o + 0x1f4) = 0;
	}
	fcn_004379a0(g_67a370, o, flags | 0x200, fcn_00445560, st);
	if (o != 0) {
		*(int*) (o + 0x1f4) = saved;
	}
	return st[2];
}
