#include "Develop/DieGildeAddOn/game/event_callbacks.h"



void* __cdecl fcn_00508e40(int);

int __cdecl fcn_004e6200(int id, unsigned char* a2)
{
	int i;

	for (i = 0; i < a2[0x30]; i++) {
		if (*(int*) (a2 + 0x34 + i * 4) == id) {
			if (fcn_00508e40(id) != 0) {
				return 1;
			}
			break;
		}
	}
	return 0;
}
