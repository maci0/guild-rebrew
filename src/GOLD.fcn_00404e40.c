#include <stdlib.h>

int __cdecl fcn_00404e40(unsigned short si)
{
	int r;
	r = 0;
	if (si != 0) {
		r = rand() % (si & 0xffff);
	}
	return r;
}
