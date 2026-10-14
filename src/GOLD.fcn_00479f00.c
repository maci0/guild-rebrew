
// fcn_00479f00 — memmove(obj + [obj+0x2a], obj, [obj+0xa]*4).

#include <string.h>

void __cdecl fcn_00479f00(char* obj)
{
	memmove(obj + *(char*) (obj + 0x2a), obj, (unsigned int) *(unsigned short*) (obj + 0xa) * 4);
}
