#include <string.h>

/* ADDRESS: GOLDTL 0x0042e640 */
int __cdecl vfs_CompareFileKey(const char* a, const char** b)
{
	return strcmp(a, *b);
}
