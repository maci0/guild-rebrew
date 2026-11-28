#include "Develop/DieGildeAddOn/game/game_data.h"
#include "Develop/client_types.h"
extern pos14_7f4c00 gm_GameTime;
extern void (__cdecl* he_EventDispatchHandlers[])(unsigned char*);

#include "Develop/DieGildeAddOn/game/he_action.h"












void __cdecl d3_PruneEventGfxSlots(void);
void __cdecl he_CreateEventGfxInfo(HE_ACTION*);
int __cdecl gm_CompareGameTime(char*, char*);
void __cdecl he_CancelInvalidBuildingAction(HE_ACTION*);

/* ADDRESS: GOLDDE 0x0052d390 */
void __cdecl he_RunDueActions(void)
{
	int i;

	d3_PruneEventGfxSlots();
	for (i = 0; i <= he_LastEventSlot && i < 1024; i++) {
		if (he_ActionSlots[i].kind != 0 && (he_ActionSlots[i].flags & 0x18) == 0) {
			he_CreateEventGfxInfo(&he_ActionSlots[i]);
			if (gm_CompareGameTime(((char*)&gm_GameTime), he_ActionSlots[i].unk_52) > 0 && he_ActionSlots[i].kind < 0xa7) {
				he_CancelInvalidBuildingAction(&he_ActionSlots[i]);
				he_EventDispatchHandlers[he_ActionSlots[i].kind](&he_ActionSlots[i].kind);
			}
		}
	}
}
#if defined(REBREW_SERVER) || defined(REBREW_GOLD)
unsigned char _dpad_77dda0[3040];
#else
/* Reference gaps only; the emitted objects inside the span keep their own rows. */
unsigned char _dpad_77dda1[383];
unsigned char _dpad_77df21[255];
unsigned char _dpad_77e021[127];
unsigned char _dpad_77e0a1[3];
unsigned char _dpad_77e0ac[2036];
unsigned char _dpad_77e8a8[24];
unsigned char _dpad_77e900[128];
#endif
#if defined(REBREW_SERVER) || defined(REBREW_GOLD)
unsigned char _dpad_77e980[340992];
#else
/* Reference gaps only; the emitted objects inside the span keep their own rows. */
unsigned char _dpad_77f980[335872];
unsigned char _dpad_7d1984[1020];
#endif
