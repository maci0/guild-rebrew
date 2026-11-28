


#include <string.h>

void __cdecl vfs_fwrite(char*, int, int, int);

/* ADDRESS: GOLDDE 0x00401210 */
void __cdecl vfs_WriteCString(int stream, char* text)
{
	vfs_fwrite(text, strlen(text) + 1, 1, stream);
}
