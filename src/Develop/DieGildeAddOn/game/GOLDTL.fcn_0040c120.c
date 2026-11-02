#include "client_types.h"


#include <stdarg.h>

#include "Develop/DieGildeAddOn/game/ch_action.h"

/* SIZE 0x4c. nargs sits at +0x48, the dword the copy loop indexes. */
typedef struct {
	void (__cdecl* handler)(CH_ACTION* t);
	unsigned char kind;
	char name[0x43];
	int nargs;
} Entry;

#include "Develop/DieGildeAddOn/game/ch_queue.h"
CH_ACTION* __cdecl fcn_0040c0a0(char* e);



/* Build a task for kind and copy the trailing stack dwords into its
 * params. i is the copy counter, so i = -1 reuses ecx (or ecx,-1) for
 * the kind 0x33 checks. Those checks are two separate ifs: an else
 * would jump over the second test instead of retesting param. */
CH_ACTION* __cdecl fcn_0040c120(char* e, int kind, ...)
{
	CH_ACTION* t;
	va_list ap;
	int i;

	if (e == 0) {
		return 0;
	}
	if (((Entry*) g_14d0c40)[kind].handler == 0) {
		kind = 0;
	}
	t = fcn_0040c0a0(e);
	if (t == 0) {
		return 0;
	}
	t->ausfuehren = ((Entry*) g_14d0c40)[kind].handler;
	t->art = (char) kind;
	t->besitzer = e;
	t->zustand = 0;
	va_start(ap, kind);
	for (i = 0; i < ((Entry*) g_14d0c40)[(unsigned char) t->art].nargs; i++) {
		(&t->parameter)[i] = va_arg(ap, int);
	}
	va_end(ap);
	t->naechste = 0;
	t->merkmale = 0;
	if (kind == 0x33) {
		i = -1;
		if (t->unbekannt_034 != i && t->unbekannt_038 == i) {
			__asm { int 3 }
		}
		if (t->parameter == 0 && t->unbekannt_034 != i) {
			goto drop;
		}
		if (t->parameter != 0 && t->unbekannt_034 == i) {
			goto drop;
		}
	}
	fcn_00405180(e, t);
	if (t->ausfuehren == fcn_004079d0) {
		t->parameter = (unsigned char) t->art;
	}
	return t;
drop:
	ch_RemoveQueueEntry((char*) (t));
	return 0;
}
