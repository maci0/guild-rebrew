


#include <string.h>

#pragma intrinsic(strlen, strcpy, strcat)

/* ADDRESS: GOLDDE 0x0040ebd0 */
int __cdecl RenameObject(int* a1, int* sourceRef)
{
	char* dst;

	dst = (char*) *a1;
	if (dst == 0) {
		return 0;
	}
	strcpy(dst, (char*) *sourceRef);
	return 1;
}
