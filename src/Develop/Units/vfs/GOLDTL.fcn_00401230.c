


#include <string.h>

void __cdecl vfs_fwrite(char*, int, int, int);

void __cdecl fcn_00401230(int a1, char* a2)
{
	vfs_fwrite(a2, strlen(a2) + 1, 1, a1);
}
