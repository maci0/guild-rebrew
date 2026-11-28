


#include "Develop/Units/Msx/client_sound.h"
extern int main_LoopFlags;
#include "Develop/DieGildeAddOn/game/game_data.h"
extern char g_68bd78[];

#include "Develop/Units/Msx/msx.h"
char* __cdecl evt_LoadGfxScript(char*);
void __cdecl evt_RunScript(char*);
void __cdecl evt_WaitAndCancelScript(int);

/* ADDRESS: GOLDDE 0x004c0200 */
void __cdecl cut_RunCombatFlightOutro(void)
{
	char* p;

	if (tp_cut_CombatAmbientTrack != 0) {
		msx_StopAmbientTrack(tp_cut_CombatAmbientTrack);
	}
	main_LoopFlags = 0x7d6c6;
	d2_SuppressOverlay = 1;
	p = evt_LoadGfxScript(g_68bd78);
	if (p != 0) {
		evt_RunScript(p);
		evt_WaitAndCancelScript(*(int*) (p + 0x100));
	}
	d2_SuppressOverlay = 0;
}
