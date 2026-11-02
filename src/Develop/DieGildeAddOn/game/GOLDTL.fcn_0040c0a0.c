


#include <string.h>

#include "Develop/DieGildeAddOn/game/ch_action.h"

#include "Develop/DieGildeAddOn/game/ch_queue.h"
#include "Develop/Units/Error/error_message.h"


CH_ACTION* __cdecl fcn_0040c0a0(char* e)
{
	CH_ACTION* t;
	CH_ACTION* p;

	t = (CH_ACTION*) ch_GetFreeQueueEntry();
	if (t == 0) {
		ReportClientMessage("no free task slot");
		return 0;
	}
	memset(t, 0, sizeof(CH_ACTION));
	if (*(CH_ACTION**) (e + 0x128) == 0) {
		*(CH_ACTION**) (e + 0x128) = t;
	} else {
		p = *(CH_ACTION**) (e + 0x128);
		while (p->naechste != 0) {
			p = p->naechste;
		}
		p->naechste = t;
		t->vorherige = p;
	}
	t->besitzer = e;
	t->zustand = 0;
	t->ausfuehren = 0;
	t->naechste = 0;
	t->merkmale = 0;
	fcn_00405180(e, t);
	return t;
}
