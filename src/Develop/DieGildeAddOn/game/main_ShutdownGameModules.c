#include "Develop/DieGildeAddOn/game/game_data.h"

void __cdecl io_SaveIniSettings(void);
void __cdecl gm_FreeBuffer773d44(void);
void __cdecl d3_FreeTable7e1d60(void);
void __cdecl evt_ShutdownScripts(void);
void __cdecl main_CloseFrameRateTimer(void);
void __cdecl d3snd_Shutdown(void);
void __cdecl d3_FreeBuffer6b5d08(void);
void __cdecl msx_ShutdownDrivers(void);
void __cdecl msx_ShutdownAIL(void);
void __cdecl d3sndw_Shutdown(void);
void __cdecl io_SaveMessageFilterMask(void);
void __cdecl txt_ReleaseTextBanks(void);
void __cdecl gm_CleanupAllEntities(void);
void __cdecl ls_FreeList774a78(void);
void __cdecl ahm_FreeAlchemyPrototypes(void);
void __cdecl gm_FreeHistoricalTable(void);
void __cdecl d3_DestroySceneSlotObjects(void);
void __cdecl ch_ShutdownCharacters(void);
void __cdecl cm_InitCommandQueuePool(void);


/* The inventory entry also holds two more functions:
 * 0x538220 (47 bytes) and the window procedure at 0x538250. */
/* ADDRESS: GOLDTL 0x005381a0 */
/* ADDRESS: GOLDDE 0x0051fa70 */
void __cdecl main_ShutdownGameModules(void)
{
	io_SaveIniSettings();
	gm_FreeBuffer773d44();
	d3_FreeTable7e1d60();
	evt_ShutdownScripts();
	main_CloseFrameRateTimer();
	if (d3snd_SoundEnabled != 0) {
		d3snd_Shutdown();
		d3_FreeBuffer6b5d08();
	}
	if (msx_MusicEnabled != 0) {
		msx_ShutdownDrivers();
	}
	if (d3snd_SoundEnabled != 0) {
		msx_ShutdownAIL();
		d3sndw_Shutdown();
	}
	io_SaveMessageFilterMask();
	txt_ReleaseTextBanks();
	gm_CleanupAllEntities();
	ls_FreeList774a78();
	ahm_FreeAlchemyPrototypes();
	gm_FreeHistoricalTable();
	d3_DestroySceneSlotObjects();
	ch_ShutdownCharacters();
	cm_InitCommandQueuePool();
}
