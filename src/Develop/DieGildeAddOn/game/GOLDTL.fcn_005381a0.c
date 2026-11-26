#include "Develop/DieGildeAddOn/game/game_data.h"

void __cdecl fcn_005e12d0(void);
void __cdecl gm_FreeBuffer773d44(void);
void __cdecl d3_FreeTable7e1d60(void);
void __cdecl evt_ShutdownScripts(void);
void __cdecl fcn_00520f40(void);
void __cdecl d3snd_Shutdown(void);
void __cdecl d3_FreeBuffer6b5d08(void);
void __cdecl msx_ShutdownDrivers(void);
void __cdecl msx_ShutdownAIL(void);
void __cdecl fcn_004195f0(void);
void __cdecl fcn_0057de00(void);
void __cdecl txt_ReleaseTextBanks(void);
void __cdecl gm_CleanupAllEntities(void);
void __cdecl ls_FreeList774a78(void);
void __cdecl fcn_004edce0(void);
void __cdecl fcn_004acf00(void);
void __cdecl d3_DestroySceneSlotObjects(void);
void __cdecl ch_ShutdownCharacters(void);
void __cdecl fcn_004c3ed0(void);


/* The inventory entry also holds two more functions:
 * 0x538220 (47 bytes) and the window procedure at 0x538250. */
/* ADDRESS: GOLDTL 0x005381a0 */
void __cdecl fcn_005381a0(void)
{
	fcn_005e12d0();
	gm_FreeBuffer773d44();
	d3_FreeTable7e1d60();
	evt_ShutdownScripts();
	fcn_00520f40();
	if (g_774934 != 0) {
		d3snd_Shutdown();
		d3_FreeBuffer6b5d08();
	}
	if (msx_MusicEnabled != 0) {
		msx_ShutdownDrivers();
	}
	if (g_774934 != 0) {
		msx_ShutdownAIL();
		fcn_004195f0();
	}
	fcn_0057de00();
	txt_ReleaseTextBanks();
	gm_CleanupAllEntities();
	ls_FreeList774a78();
	fcn_004edce0();
	fcn_004acf00();
	d3_DestroySceneSlotObjects();
	ch_ShutdownCharacters();
	fcn_004c3ed0();
}
