#include <stdlib.h>

int __cdecl ch_RandomIndex(unsigned short si)
{
	int r;
	r = 0;
	if (si != 0) {
		r = rand() % (si & 0xffff);
	}
	return r;
}
