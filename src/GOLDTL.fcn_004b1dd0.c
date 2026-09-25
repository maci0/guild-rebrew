// FUNCTION: GOLDTL 0x4b1dd0
// SIZE: 140

#include <string.h>

extern unsigned char g_773d75;

char* __cdecl fcn_00508e40(int);
int __cdecl fcn_004ae130(unsigned short);
int __cdecl fcn_0064fcaf(char*);
int __cdecl fcn_00501490(char*);
void __cdecl fcn_004c51f0(int, int, int, int, unsigned char, int);

int __cdecl fcn_004b1dd0(char* tbl, int idx, char* arg)
{
	char* e;
	char* s;
	int r;

	e = fcn_00508e40(*(int*) (tbl + idx * 8 + 4));
	if (e != 0 && fcn_004ae130(*(unsigned short*) e) != 0 && *arg == '-') {
		s = arg + 1;
		if (strlen(s) >= 4) {
			s += 3;
			fcn_0064fcaf(s + 1);
			r = fcn_00501490(s);
			if (r != 0) {
				fcn_004c51f0(*(int*) (e + 4), -1, r, 1, g_773d75, 0);
				return 1;
			}
		}
	}
	return 0;
}
