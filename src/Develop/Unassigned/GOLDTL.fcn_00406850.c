


#include <string.h>

#include "Develop/DieGildeAddOn/game/ch_action.h"

CH_ACTION* __cdecl fcn_0040c0a0(char* e);
void __cdecl UsingGate(CH_ACTION* t);
#include "Develop/Units/Error/error_message.h"

CH_ACTION* __cdecl ch_UseGate(char* e, const char* name, const char* name2, int a, int b, int c)
{
	CH_ACTION* t;

	t = fcn_0040c0a0(e);
	if (t == 0) {
		return 0;
	}
	t->ausfuehren = UsingGate;
	t->art = 0x34;
	strcpy(t->name, name);
	strcpy(t->name_2, name2);
	t->unbekannt_170 = a;
	t->unbekannt_174 = b;
	if (*(int*) &t->unbekannt_178 == -1) {
		ReportClientMessage("task value unset");
	}
	*(int*) &t->unbekannt_178 = c;
	return t;
}
