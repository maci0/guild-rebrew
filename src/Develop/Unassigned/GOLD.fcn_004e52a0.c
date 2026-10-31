
// fcn_004e52a0 — [0x92c4e0]=a; fcn_005de7a2(&buf, 0x60e9ec, a).

#include <stdio.h>

void __cdecl fcn_004e52a0(int a)
{
	char buf[0x40];
	*(int*) 0x92c4e0 = a;
	sprintf(buf, (const char*) 0x60e9ec, a);
}
