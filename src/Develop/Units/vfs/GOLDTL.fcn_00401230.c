


#include <string.h>

void __cdecl vfs_fwrite(char*, int, int, int);

void __cdecl fcn_00401230(int stream, char* text)
{
	vfs_fwrite(text, strlen(text) + 1, 1, stream);
}
