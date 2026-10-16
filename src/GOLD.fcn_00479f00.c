
#include <string.h>
#pragma intrinsic(memcpy)

/* ADDRESS: GOLD 0x00479f00 */
void __cdecl fcn_00479f00(char* src, char* obj)
{
	memcpy(obj + *(int*) (obj + 0x2a), src, (unsigned int) (*(unsigned short*) (obj + 0xa)) * 4);
}
