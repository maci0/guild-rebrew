#include "client_actions.h"

char* __cdecl fcn_0050e4a0(int);
void* __cdecl fcn_00502cd0(int, int, int, ...);

char* __cdecl fcn_00507ab0(int a)
{
	char* e;

	e = fcn_0050e4a0(a);
	if (a == 1) {
		return fcn_00502cd0(*(int*) (e + 0x5d), 2, 6, 0, 0x115);
	} else {
		return fcn_00502cd0(*(int*) (e + 0x5d), 2, 6, 0, 0x142);
	}
}
