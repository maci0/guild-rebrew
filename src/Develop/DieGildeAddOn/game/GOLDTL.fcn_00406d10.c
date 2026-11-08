

#include <string.h>

#include "Develop/DieGildeAddOn/game/ch_action.h"

CH_ACTION* __cdecl ch_NewAction(char* e);
void __cdecl ch_DroppingObject(CH_ACTION* t);

int __cdecl fcn_00406d10(char* e, const char* name, const char* name2, int param)
{
	CH_ACTION* t;

	t = ch_NewAction(e);
	if (t == 0) {
		return 0;
	}
	t->besitzer = e;
	t->parameter = param;
	t->zustand = 0;
	t->ausfuehren = ch_DroppingObject;
	t->art = 0x32;
	t->naechste = 0;
	t->merkmale = 0;
	t->unbekannt_034 = 0;
	t->unbekannt_038 = 1;
	if (name != 0) {
		strcpy(t->name, name);
	} else {
		t->name[0] = 0;
	}
	if (name2 != 0) {
		strcpy(t->name_2, name2);
	} else {
		t->name_2[0] = 0;
	}
	return 1;
}
