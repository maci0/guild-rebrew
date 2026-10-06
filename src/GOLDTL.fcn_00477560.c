#include <string.h>

// FUNCTION: GOLDTL 0x477560

void __cdecl fcn_00477560(const void* src, char* hdr)
{
	memcpy(hdr + *(int*) (hdr + 0x2a), src, *(unsigned short*) (hdr + 0xa) * 4);
}
