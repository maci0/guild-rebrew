


#include "Develop/DieGildeAddOn/game/ch_action.h"

extern float g_6628a8;
void __cdecl fcn_00404300(char* e, char* name, int n);
int __cdecl fcn_004042b0(char* e);
#include "Develop/DieGildeAddOn/game/ch_queue.h"
void __cdecl ch_CheckAniMorph(char* e);

void __cdecl fcn_00406280(CH_ACTION* t)
{
	char* e;
	char* s;

	e = t->besitzer;
	if (t->unbekannt_190 != 0 && *(char**) (e + 0x70) != 0 &&
	    *(unsigned char*) (*(char**) (e + 0x70) + 0x6c) > 2) {
		*(unsigned char*) (*(char**) (e + 0x70) + 0x6c) = 2;
	}
	if (t->zustand == 0) {
		if (t->parameter == -1) {
			*(unsigned short*) (e + 0x8c) |= 2;
		}
		fcn_00404300(e, t->name, t->parameter < 1 ? 1 : t->parameter);
	} else if (t->unbekannt_190 != 0 || t->parameter != -1) {
		if (t->parameter == -1) {
			*(unsigned short*) (e + 0x8c) &= ~2;
		}
		if (fcn_004042b0(e)) {
			ch_RemoveQueueEntry((char*) (t));
			ch_CheckAniMorph(e);
		}
	}
	s = *(char**) (e + 0x70);
	if (s != 0 && t->unbekannt_178 != g_6628a8) {
		*(float*) (s + 0x60) = t->unbekannt_178;
	}
}
