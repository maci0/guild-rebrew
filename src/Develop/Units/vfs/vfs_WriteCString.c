


#include <string.h>

void __cdecl vfs_fwrite(char*, int, int, int);

void __cdecl vfs_WriteCString(int stream, char* text)
{
	vfs_fwrite(text, strlen(text) + 1, 1, stream);
}
