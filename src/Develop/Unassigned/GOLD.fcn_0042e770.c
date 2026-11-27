#include <string.h>

/* ADDRESS: GOLD 0x0042e770 */
int __cdecl txt_FindEntryIndex(char* name)
{
	char* e;
	int i;

	i = 0;
	e = (char*) 0xfe7e40;
	do {
		if (_strcmpi(name, e) == 0) {
			return i;
		}
		e += 0x50;
		i++;
	} while ((int) e < 0x114fe40);
	return -1;
}
