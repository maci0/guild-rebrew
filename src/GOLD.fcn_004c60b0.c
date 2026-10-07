// FUNCTION: GOLD 0x004c60b0
// fcn_004c60b0 — x[0]=0x60; memcpy(x+0x10, src, 0x1e); fcn_004c39c0(&x).

#include <string.h>

int __cdecl fcn_004c39c0(void*);

void __cdecl fcn_004c60b0(void* src)
{
	char x[0x9c];
	x[0] = 0x60;
	memcpy(x + 0x10, src, 0x1e);
	fcn_004c39c0(&x);
}
