#include "Develop/DieGildeAddOn/game/game_data.h"
#include "client_types.h"
extern pos14_7f4c00 gm_GameTime;
extern void (__cdecl* g_7dc440[])(unsigned char*);

#include "Develop/DieGildeAddOn/game/he_action.h"












void __cdecl d3_PruneEventGfxSlots(void);
void __cdecl he_CreateEventGfxInfo(HE_ACTION*);
int __cdecl fcn_00500cb0(char*, char*);
void __cdecl fcn_00546be0(HE_ACTION*);

void __cdecl he_RunDueActions(void)
{
	int i;

	d3_PruneEventGfxSlots();
	for (i = 0; i <= he_LastEventSlot && i < 1024; i++) {
		if (g_77e980[i].kind != 0 && (g_77e980[i].flags & 0x18) == 0) {
			he_CreateEventGfxInfo(&g_77e980[i]);
			if (fcn_00500cb0(((char*)&gm_GameTime), g_77e980[i].unk_52) > 0 && g_77e980[i].kind < 0xa7) {
				fcn_00546be0(&g_77e980[i]);
				g_7dc440[g_77e980[i].kind](&g_77e980[i].kind);
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
