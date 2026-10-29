#include <string.h>

typedef struct {
	unsigned int items[0x20];
	int count;
} FACKEL_LIST;


/* ADDRESS: GOLDTL 0x00514d30 */
char __cdecl fcn_00514d30(char* name, FACKEL_LIST* list)
{
	if (strstr(name, "ub_FACKEL_") != 0) {
		list->items[list->count] = (unsigned int)name;
		list->count = list->count + 1;
	}
	return list->count < 0x20;
}
