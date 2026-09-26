// FUNCTION: GOLD 0x004c67c0
// SIZE: 169
// FUNCTION: GOLDTL 0x4c7350
// SIZE: 169

#include "client_types.h"
extern pos14_7f4c00 g_7f4c00;

char* __cdecl fcn_00503fe0(int, ...);
char* __cdecl fcn_00502cd0(int, int, int, int, int);

int __cdecl fcn_004c7350(char* x)
{
	char* e;
	char* r;
	int i;

	if (*(int*) (x + 0x10) == 0x636c6572) {
		e = fcn_00503fe0(1, 1, *(int*) (x + 0x18));
		if (e == 0)
			return 1;
		r = fcn_00502cd0(*(int*) (e + 0x5d), 2, 6, 0, 0x12c);
		if (r == 0)
			return 1;
		return (*(int*)&g_7f4c00) - *(int*) (r + 0x28) <= 1;
	}
	if (*(int*) (x + 0x10) == 0x62757920) {
		e = fcn_00503fe0(1, 1, *(int*) (x + 0x18));
		if (e == 0)
			return 1;
		r = fcn_00502cd0(*(int*) (e + 0x5d), 2, 6, 0, 0x12c);
		if (r == 0)
			return 1;
		for (i = 0; i < 3; i++) {
			if (*(int*) (r + 0x1c + i * 4) == *(int*) (x + 0x1c))
				return 0;
		}
	}
	return 1;
}
