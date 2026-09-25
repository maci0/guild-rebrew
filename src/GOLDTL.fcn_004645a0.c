#include <string.h>

int __cdecl fcn_00464600(const char* a, const char* b);

// FUNCTION: GOLDTL 0x4645a0
// SIZE: 91
int __cdecl fcn_004645a0(const char* fileName1, const char* fileName2, int iCaseSensitivity)
{
	if (iCaseSensitivity == 0) {
		iCaseSensitivity = 2;
	}
	if (iCaseSensitivity == 1) {
		return strcmp(fileName1, fileName2);
	}
	return fcn_00464600(fileName1, fileName2);
}
