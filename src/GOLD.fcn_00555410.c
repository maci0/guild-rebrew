#include <string.h>

typedef struct {
	unsigned int items[0x20];
	int count;
} TRANSPORTER_LIST;

/* ADDRESS: GOLD 0x00555410 */
char __cdecl fcn_00555410(char* name, TRANSPORTER_LIST* list)
{
	if (strstr(name, "dummy_TRANSPORTER") != 0) {
		list->items[list->count] = (unsigned int) name;
		list->count = list->count + 1;
	}
	return list->count < 0x20;
}
