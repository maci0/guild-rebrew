


#include <stdarg.h>

#include "Develop/DieGildeAddOn/game/ch_action.h"

// SIZE 0x4c
typedef struct {
	void (__cdecl* handler)(CH_ACTION* t);
	unsigned char kind;
	char name[0x43];
	int nargs;
} Entry;

#include "client_types.h"
#include "Develop/DieGildeAddOn/game/ch_queue.h"
CH_ACTION* __cdecl fcn_0040c0a0(char* e);

CH_ACTION* __cdecl fcn_0040c230(char* e, void (__cdecl* done)(CH_ACTION* t), unsigned char level, int kind, ...)
{
	CH_ACTION* t;
	va_list ap;
	int i;

	if (e == 0) {
		return 0;
	}
	if (((Entry*)g_14d0c40)[kind].handler == 0) {
		kind = 0;
	}
	t = fcn_0040c0a0(e);
	if (t == 0) {
		return 0;
	}
	t->ausfuehren = ((Entry*)g_14d0c40)[kind].handler;
	t->art = (char) kind;
	t->besitzer = e;
	t->zustand = 0;
	va_start(ap, kind);
	for (i = 0; i < ((Entry*)g_14d0c40)[(unsigned char) t->art].nargs; i++) {
		(&t->parameter)[i] = va_arg(ap, int);
	}
	va_end(ap);
	t->naechste = 0;
	t->merkmale = 0;
	t->abschluss = done;
	t->stufe = level;
	if (t->ausfuehren == fcn_004079d0) {
		t->parameter = (unsigned char) t->art;
	}
	return t;
}
