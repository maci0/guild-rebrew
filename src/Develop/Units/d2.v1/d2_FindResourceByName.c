#include <string.h>

extern char* d2_FileObjTable;

/* ADDRESS: GOLDTL 0x00465950 */
int __cdecl d2_FindResourceByName(const char* name)
{
	int i;

	for (i = 0; i < 0x800; i++) {
		if (d2_FileObjTable[i * 0x54] != 0 && strcmp(name, d2_FileObjTable + i * 0x54) == 0) {
			return i;
		}
	}
	return -1;
}
