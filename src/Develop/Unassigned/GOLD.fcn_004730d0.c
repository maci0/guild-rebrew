#include <string.h>

#include "Develop/Units/d2.v1/d2_gui.h"
extern GuiEnt** g_006ed964;

/* ADDRESS: GOLD 0x004730d0 */
void __cdecl fcn_004730d0(int index, char* owner)
{
	char** table;
	char* record;
	char* p;
	int offset;
	int i;
	offset = index * 0x2ec;
	record = (char*) g_00f8f080 + offset;
	table = (char**) g_006ed964;
	for (i = 0; i < 0x2ff; i++) {
		if (table[i] == record) {
			if (i == 0x2ff) {
				table[0x2ff] = 0;
			} else if (i < 0x2ff) {
				memcpy(table + i, table + i + 1, 0xbf8 - i * 4);
			}
			table = (char**) g_006ed964;
			break;
		}
	}
	for (i = 0x2ff; i >= 0; i--) {
		p = table[i];
		if (p != 0 && ((*(char**) (p + 0x30) == owner && *(int*) (p + 0x18) != 0x40)
			|| *(int*) p == *(int*) (owner + 0x26c))) {
			break;
		}
	}
	if (i >= 0) {
		if (i < 0x2ff) {
			memcpy(table + i + 2, table + i + 1, 0xbf8 - i * 4);
			table = (char**) g_006ed964;
		}
		table[i + 1] = (char*) g_00f8f080 + offset;
	}
}
