


#include <string.h>

#include "Develop/DieGildeAddOn/game/ch_action.h"

CH_ACTION* __cdecl ch_NewAction(char* e);
void __cdecl ch_ExecPlayAnimation(CH_ACTION* t);

/* ADDRESS: GOLDDE 0x004054e0 */
int __cdecl ch_QueuePlayAnimation(char* e, const char* name, int param)
{
	CH_ACTION* t;

	t = ch_NewAction(e);
	if (t == 0) {
		return 0;
	}
	t->parameter = param;
	t->besitzer = e;
	t->zustand = 0;
	t->ausfuehren = ch_ExecPlayAnimation;
	t->art = 0x2e;
	t->unbekannt_178 = 1.0f;
	t->naechste = 0;
	t->merkmale = 0;
	strcpy(t->name, name);
	return 1;
}
