#include "Develop/DieGildeAddOn/game/entity_record.h"


extern char g_7f4ca0[];

char* __cdecl fcn_0050dc90(int arg1)
{
	int i;
	int cursor;
	char* record;

	record = 0;
	if (arg1 == 0) {
		return record;
	}
	i = 0;
	cursor = (int) (g_7f4ca0 + 2);
	while (cursor < (int) (g_7f4ca0 + 2 + 768 * (int)sizeof(ENTITY_RECORD))) {
		if (*(char*) (cursor + 0x162) != 0 && *(int*) (cursor + 0x16a) == arg1) {
			if (*(char*) cursor == 6 || *(char*) cursor == 7 || *(char*) cursor == 1 || *(char*) cursor == 2) {
				record = (char *)&((ENTITY_RECORD*)g_7f4ca0)[i];
				break;
			}
		}
		cursor += (int)sizeof(ENTITY_RECORD);
		i++;
	}
	return record;
}
