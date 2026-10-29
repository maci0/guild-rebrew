#include "he_tables.h"

void __cdecl fcn_00546e40(int a1, int a2, char* a3, int a4, void* a5);

extern Deal g_7d2020[256];



#include <string.h>

void __cdecl fcn_00546e40(int a1, int a2, char* a3, int a4, void* a5)
{
	int i;
	Deal* t;

	for (i = 0; i < 256; i++) {
		if (g_7d2020[i].id == 0) {
			break;
		}
	}
	if (i < 256) {
		t = &g_7d2020[i];
		t->id = a1;
		t->owner = a2;
		t->amount = a4;
		t->has_amount = 1;
		t->state = 2;
		strncpy(t->name, a3, 0x7f);
		t->pos = *(Pos14*) a5;
	}
}
