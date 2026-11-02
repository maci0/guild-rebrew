


#include <string.h>

#include "Develop/DieGildeAddOn/game/ch_action.h"

CH_ACTION* __cdecl fcn_0040c0a0(char* e);
void __cdecl fcn_00406280(CH_ACTION* t);

int __cdecl fcn_00406340(char* e, const char* name, int param)
{
	CH_ACTION* t;

	t = fcn_0040c0a0(e);
	if (t == 0) {
		return 0;
	}
	t->parameter = param;
	t->besitzer = e;
	t->zustand = 0;
	t->ausfuehren = fcn_00406280;
	t->art = 0x2e;
	t->unbekannt_178 = 1.0f;
	t->naechste = 0;
	t->merkmale = 0;
	strcpy(t->name, name);
	return 1;
}
