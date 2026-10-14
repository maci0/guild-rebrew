#include <string.h>

/* ADDRESS: GOLDTL 0x00477560 */

void __cdecl fcn_00477560(const void* src, char* hdr)
{
	memcpy(hdr + *(int*) (hdr + 0x2a), src, *(unsigned short*) (hdr + 0xa) * 4);
}
