#include <string.h>

typedef struct {
	unsigned int items[0x20];
	int count;
} FACKEL_LIST;

/* ADDRESS: GOLD 0x005115e0 */

char __cdecl fcn_005115e0(char* name, FACKEL_LIST* list)
{
	if (strstr(name, "ub_FACKEL_") != 0) {
		list->items[list->count] = (unsigned int) name;
		list->count = list->count + 1;
	}
	return list->count < 0x20;
}
