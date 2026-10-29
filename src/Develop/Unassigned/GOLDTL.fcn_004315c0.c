#include <string.h>

/* ADDRESS: GOLDTL 0x004315c0 */
char __cdecl fcn_004315c0(char* obj)
{
	char* child;
	char* rec;
	char* elem;
	char* node;
	char* ent;
	int n;
	int i;
	int j;

	if (obj == 0) {
		return 0;
	}
	child = *(char**) (obj + 0x1ec);
	if (child == 0) {
		return 0;
	}
	rec = child + 0x494;
	for (j = 0; j < 3; j++) {
		elem = *(char**) (rec - 0x10);
		if (elem != 0) {
			*(int*) rec = -1;
			n = 0;
			i = 0;
			ent = elem + 0x40;
			while (i < *(int*) (elem + 0x144)) {
				for (node = *(char**) (obj + 0x200); node != 0; node = *(char**) (node + 0x1f4)) {
					if (strcmp((char*) (*(int*) (node + 0x1ec) + 0xb4), ent) == 0) {
						rec[n] = (char) i;
						n++;
					}
				}
				ent += 0x40;
				i++;
				if (n >= 4) {
					break;
				}
			}
		}
		rec += 0x7c;
	}
	return 0;
}
