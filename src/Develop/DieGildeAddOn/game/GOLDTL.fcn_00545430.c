#include "Develop/DieGildeAddOn/game/event_deal.h"

extern HE_AP_EVENT g_7dcae0[256];
extern Rec7dc6e0 g_7dc6e0[64];




#include <string.h>

int __cdecl he_RegisterHandler(int, void*, void*);
void __cdecl he_AllocNone(void*);
void __cdecl he_RunNone(void);
void __cdecl fcn_00545410(void);
void __cdecl fcn_00545420(void);
int __cdecl he_RegisterEventHandlers(void);
int __cdecl he_RegisterActionHandlers(void);
int __cdecl he_RegisterCoreActionHandlers(void);
int __cdecl he_RegisterFriedhofHandlers(void);
int __cdecl he_RegisterAhmHandlers(void);
int __cdecl he_RegisterAssassinHandlers(void);
int __cdecl he_RegisterZigeunerHandlers(void);
int __cdecl he_RegisterAction0xa2Handler(void);

int __cdecl he_InitEventSystem(void)
{
	if (he_RegisterHandler(0, (void*) he_AllocNone, (void*) he_RunNone) != 0) {
		return 1;
	}
	if (he_RegisterHandler(1, (void*) fcn_00545410, (void*) fcn_00545420) != 0) {
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
	memset(g_7d2020, 0, sizeof(g_7d2020));
	memset(g_7dcae0, 0, sizeof(g_7dcae0));
	memset(g_7dc6e0, 0, sizeof(g_7dc6e0));
	return 0;
}
