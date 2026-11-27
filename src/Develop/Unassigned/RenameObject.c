


#include <string.h>

#pragma intrinsic(strlen, strcpy, strcat)

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
