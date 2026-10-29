extern unsigned char* lpGebaeudePROT;



#include <string.h>

char __cdecl fcn_00514e80(char* o)
{
	unsigned char* t;

	if (strncmp(o, "gb_", 3) == 0) {
		t = 0;
		if (o[0x4b] == 2) {
			t = lpGebaeudePROT + (*(int*) (o + 0x48) & 0xffffff) * 0x24d;
		}
		if (t == 0) {
			if (strstr(o, "_TOR_") == 0) {
				o[0x216] = (o[0x216] & 0xfd) | 1;
				return 1;
			}
		} else if (*t != 0x1f) {
			o[0x216] = (o[0x216] & 0xfd) | 1;
			return 1;
		} else {
			o[0x216] |= 3;
		}
	}
	return 1;
}
