


extern int he_LastEventSlot;
#include "Develop/client_types.h"
#include "Develop/DieGildeAddOn/game/he_action.h"
extern void (__cdecl* g_7dc440[])(unsigned char*);

void __cdecl he_CancelInvalidBuildingAction(unsigned char*);

void __cdecl he_DispatchFlaggedEvents(void)
{
	int i;
	unsigned char* p;

	for (i = 0; i <= he_LastEventSlot && i < 0x400; i++) {
		p = &g_77e980[i].kind;
		if (*p != 0 && (p[0x78] & 0x10) != 0 && *p < 0xa7) {
			he_CancelInvalidBuildingAction(p);
			g_7dc440[*p](p);
		}
	}
}
