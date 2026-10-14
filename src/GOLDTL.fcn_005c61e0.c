#include "g_6abb08.h"



extern Offer g_6abb08[];

char* __cdecl fcn_005c61e0(int a1)
{
	int n;
	int v;

	v = *(int*) g_6abb08;
	n = 0;
	while (v != 0) {
		if (v == a1) {
			return (char*) g_6abb08 + n * 0x1c;
		}
		n++;
		v = *(int*) ((char*) g_6abb08 + n * 0x1c);
	}
	return 0;
}
