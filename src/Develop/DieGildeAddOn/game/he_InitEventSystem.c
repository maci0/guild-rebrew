#include "Develop/DieGildeAddOn/game/event_deal.h"

extern HE_AP_EVENT he_ApEvents[256];
extern Rec7dc6e0 g_7dc6e0[64];




#include <string.h>

int __cdecl he_RegisterHandler(int, void*, void*);
void __cdecl he_AllocNone(void*);
void __cdecl he_RunNone(void);
void __cdecl he_AllocDummyEvent(void);
void __cdecl he_RunDummyEvent(void);
int __cdecl he_RegisterEventHandlers(void);
int __cdecl he_RegisterActionHandlers(void);
int __cdecl he_RegisterCoreActionHandlers(void);
int __cdecl he_RegisterFriedhofHandlers(void);
int __cdecl he_RegisterAhmHandlers(void);
int __cdecl he_RegisterAssassinHandlers(void);
int __cdecl he_RegisterZigeunerHandlers(void);
int __cdecl he_RegisterAction0xa2Handler(void);

/* ADDRESS: GOLDDE 0x0052bae0 */
int __cdecl he_InitEventSystem(void)
{
	if (he_RegisterHandler(0, (void*) he_AllocNone, (void*) he_RunNone) != 0) {
		return 1;
	}
	if (he_RegisterHandler(1, (void*) he_AllocDummyEvent, (void*) he_RunDummyEvent) != 0) {
		return 1;
	}
	if (he_RegisterEventHandlers() != 0) {
		return 1;
	}
	if (he_RegisterActionHandlers() != 0) {
		return 1;
	}
	if (he_RegisterCoreActionHandlers() != 0) {
		return 1;
	}
	if (he_RegisterFriedhofHandlers() != 0) {
		return 1;
	}
	if (he_RegisterAhmHandlers() != 0) {
		return 1;
	}
	if (he_RegisterAssassinHandlers() != 0) {
		return 1;
	}
	if (he_RegisterZigeunerHandlers() != 0) {
		return 1;
	}
	if (he_RegisterAction0xa2Handler() != 0) {
		return 1;
	}
	memset(he_EventDeals, 0, sizeof(he_EventDeals));
	memset(he_ApEvents, 0, sizeof(he_ApEvents));
	memset(g_7dc6e0, 0, sizeof(g_7dc6e0));
	return 0;
}
