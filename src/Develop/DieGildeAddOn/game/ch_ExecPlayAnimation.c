


#include "Develop/DieGildeAddOn/game/ch_action.h"

extern float flt_0_0;
void __cdecl ch_LoadCharacterMotion(char* e, char* name, int n);
int __cdecl ch_IsAnimationFinished(char* e);
#include "Develop/DieGildeAddOn/game/ch_queue.h"
void __cdecl ch_CheckAniMorph(char* e);

/* ADDRESS: GOLDDE 0x00405420 */
void __cdecl ch_ExecPlayAnimation(CH_ACTION* t)
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
		ch_LoadCharacterMotion(e, t->name, t->parameter < 1 ? 1 : t->parameter);
	} else if (t->unbekannt_190 != 0 || t->parameter != -1) {
		if (t->parameter == -1) {
			*(unsigned short*) (e + 0x8c) &= ~2;
		}
		if (ch_IsAnimationFinished(e)) {
			ch_RemoveQueueEntry((char*) (t));
			ch_CheckAniMorph(e);
		}
	}
	s = *(char**) (e + 0x70);
	if (s != 0 && t->unbekannt_178 != flt_0_0) {
		*(float*) (s + 0x60) = t->unbekannt_178;
	}
}
