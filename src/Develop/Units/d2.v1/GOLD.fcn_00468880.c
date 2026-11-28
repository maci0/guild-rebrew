#include <string.h>

/* ADDRESS: GOLD 0x00468880 */
int __cdecl fcn_00468880(char* name)
{
	char* row;
	int i;

	row = *(char**) 0x6ed918;
	i = 0;
	while (i < 0x800) {
		if (row[0] != 0 && strcmp(name, row) == 0) {
			return i;
		}
		i++;
		row += 0x54;
	}
	return -1;
}
