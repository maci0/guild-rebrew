extern char g_14d0020[];
/* Global shutdown of the game runtime. */

extern int str_empty;
extern int g_538060;
extern int d2_SuppressOverlay;
extern int cut_SkipMode;
extern int g_7749cc;
extern int d3snd_SoundEnabled;
extern int g_7747bc;
extern int g_7747c0;
extern int g_7747c4;
extern int g_7747c8;
extern int g_7747cc;
extern int g_6b5c2c;
extern int d3_SnowEffect;
extern int d3_RainEffect;
extern int g_6b89c0;
extern char g_6b8061;
extern int SonnenstrahlenObjekt;
extern int d3_ActiveCameraAnimation;
extern int g_77497c;
extern int d2_SelectedBuilding;
extern int sv_SelectedBuilding;
extern int d2_VisitedBuilding;
extern int d2_InteriorBuilding;

void __cdecl d3_ClearSceneObjectCache(void);
void __cdecl d2_SetMouseTooltip(void* p);
void __cdecl d2_ShowStatusBanner(void* p);
void __cdecl tb_CloseFunction(void* p);
void __cdecl evt_CloseAllScripts(void);
void __cdecl gv_SpawnIfPending(int p);
void __cdecl d3snd_StopTrackedVoices(void);
void __cdecl d3snd_StopAllObjectSounds(void);
void __cdecl sb_ReleaseSampleBank(int p);
void __cdecl hst_ResetHistoryState(void);
void __cdecl gm_ClearMissionJobs(void);
void __cdecl he_FreeAllActions(void);
void __cdecl d2_ClearActionPopupSlots(void);
void __cdecl he_ShutdownEventSystem(void);
void __cdecl d2_DestroyAllHudPanels(void);
void __cdecl gm_KillAllSpieler(void);
void __cdecl gm_ResetAllEntities(void);
void __cdecl gm_CleanupObjectEntities(void);
void __cdecl ch_DestroyCharacter(int p);
void __cdecl d3_DestroySnowEffect(int p);
void __cdecl d3_DestroyRain(int p);
void __cdecl d3_RemoveSkyLayer(int a, int b);
void __cdecl d3_FreeSkyDome(int a);
void __cdecl d3_DestroySunRayObject(int p);
void __cdecl d3_ClearAllSceneContexts(void);
void __cdecl d2_ClearPreviewTexture(void);
void __cdecl gm_FreeAmbientAnimalSlots(void);
void __cdecl cm_InitCommandQueue(void);
void __cdecl nt_CloseBroadcastSocket(void);
void __cdecl nt_CloseClientConnection(void);
void __cdecl d2_SetOverlayAnimation(int a, int b);

/* ADDRESS: GOLDTL 0x0053fa80 */
/* ADDRESS: GOLDDE 0x00526590 */
void __cdecl gm_ShutdownGameRuntime(void)
{
    register int _dummy_reg_88 = 0;
    register int _dummy_reg_63 = 0;
    register int _dummy_reg_14 = 0;
	int* entry;

	d3_ClearSceneObjectCache();
	d2_SetMouseTooltip(&str_empty);
	d2_ShowStatusBanner(&str_empty);
	d2_SuppressOverlay = 1;
	tb_CloseFunction(&g_538060);
	cut_SkipMode = 0;
	evt_CloseAllScripts();
	if (g_7749cc != 0) {
		gv_SpawnIfPending(g_7749cc);
	}
	if (d3snd_SoundEnabled != 0) {
		d3snd_StopTrackedVoices();
		d3snd_StopAllObjectSounds();
		if (g_7747bc != 0) {
			sb_ReleaseSampleBank(g_7747bc);
			g_7747bc = 0;
			sb_ReleaseSampleBank(g_7747c0);
			g_7747c0 = 0;
			sb_ReleaseSampleBank(g_7747c4);
			g_7747c4 = 0;
			sb_ReleaseSampleBank(g_7747c8);
			g_7747c8 = 0;
			sb_ReleaseSampleBank(g_7747cc);
			g_7747cc = 0;
			sb_ReleaseSampleBank(g_6b5c2c);
			g_6b5c2c = 0;
		}
	}
	hst_ResetHistoryState();
	gm_ClearMissionJobs();
	he_FreeAllActions();
	d2_ClearActionPopupSlots();
	he_ShutdownEventSystem();
	d2_DestroyAllHudPanels();
	gm_KillAllSpieler();
	gm_ResetAllEntities();
	gm_CleanupObjectEntities();
	for (entry = (int*) &g_14d0020; (int) entry < ((int) &g_14d0020 + 0xc00); entry++) {
		if (*entry != 0) {
			ch_DestroyCharacter(*entry);
		}
	}
	if (d3_SnowEffect != 0) {
		((int (*)(char)) d3_DestroySnowEffect)(d3_SnowEffect);
		d3_SnowEffect = 0;
	}
	if (d3_RainEffect != 0) {
		d3_DestroyRain(d3_RainEffect);
		d3_RainEffect = 0;
	}
	if (g_6b89c0 != 0) {
		int ctx = g_6b89c0;
		for (entry = (int*) ((int) &d3_SnowEffect + 0x4); (int) entry < ((int) &d3_SnowEffect + 0x1c); entry++) {
			if (*entry != 0) {
				d3_RemoveSkyLayer(ctx, *entry);
				ctx = g_6b89c0;
				*entry = 0;
			}
		}
		d3_FreeSkyDome(ctx);
		g_6b89c0 = 0;
	}
	g_6b8061 = 0;
	if (SonnenstrahlenObjekt != 0) {
		d3_DestroySunRayObject(SonnenstrahlenObjekt);
		SonnenstrahlenObjekt = 0;
	}
	d3_ActiveCameraAnimation = 0;
	d3_ClearAllSceneContexts();
	d2_ClearPreviewTexture();
	gm_FreeAmbientAnimalSlots();
	cm_InitCommandQueue();
	nt_CloseBroadcastSocket();
	nt_CloseClientConnection();
	g_77497c = 0;
	d2_SetOverlayAnimation(0, 0);
	d2_SelectedBuilding = 0;
	sv_SelectedBuilding = 0;
	d2_VisitedBuilding = 0;
	d2_InteriorBuilding = 0;
}
