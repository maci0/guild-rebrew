/* Global shutdown of the game runtime. */

extern int g_6b5c60;
extern int g_538060;
extern int d2_SuppressOverlay;
extern int g_772f3c;
extern int g_7749cc;
extern int g_774934;
extern int g_7747bc;
extern int g_7747c0;
extern int g_7747c4;
extern int g_7747c8;
extern int g_7747cc;
extern int g_6b5c2c;
extern int g_7e453c;
extern int g_7e4538;
extern int g_6b89c0;
extern char g_6b8061;
extern int g_6b5cf8;
extern int d3_ActiveCameraAnimation;
extern int g_77497c;
extern int g_7e2aa0;
extern int g_7746cc;
extern int g_7746c4;
extern int g_7746c8;

void __cdecl fcn_00533880(void);
void __cdecl d2_SetMouseTooltip(void* p);
void __cdecl fcn_00533a40(void* p);
void __cdecl tb_CloseFunction(void* p);
void __cdecl evt_CloseAllScripts(void);
void __cdecl gv_SpawnIfPending(int p);
void __cdecl d3snd_StopTrackedVoices(void);
void __cdecl d3snd_StopAllObjectSounds(void);
void __cdecl fcn_004230e0(int p);
void __cdecl hst_ResetHistoryState(void);
void __cdecl gm_ClearMissionJobs(void);
void __cdecl he_FreeAllActions(void);
void __cdecl d2_ClearActionPopupSlots(void);
void __cdecl he_ShutdownEventSystem(void);
void __cdecl fcn_00527420(void);
void __cdecl gm_KillAllSpieler(void);
void __cdecl gm_ResetAllEntities(void);
void __cdecl gm_CleanupObjectEntities(void);
void __cdecl ch_DestroyCharacter(int p);
void __cdecl fcn_004162c0(int p);
void __cdecl d3_DestroyRain(int p);
void __cdecl fcn_004597f0(int a, int b);
void __cdecl fcn_00459b40(int a);
void __cdecl fcn_00418ae0(int p);
void __cdecl d3_ClearAllSceneContexts(void);
void __cdecl fcn_005c80d0(void);
void __cdecl fcn_004bbd50(void);
void __cdecl fcn_004c3e30(void);
void __cdecl nt_CloseBroadcastSocket(void);
void __cdecl nt_CloseClientConnection(void);
void __cdecl d2_SetOverlayAnimation(int a, int b);

/* ADDRESS: GOLDTL 0x0053fa80 */
void __cdecl gm_ShutdownGameRuntime(void)
{
    register int _dummy_reg_88 = 0;
    register int _dummy_reg_63 = 0;
    register int _dummy_reg_14 = 0;
	int* entry;

	fcn_00533880();
	d2_SetMouseTooltip(&g_6b5c60);
	fcn_00533a40(&g_6b5c60);
	d2_SuppressOverlay = 1;
	tb_CloseFunction(&g_538060);
	g_772f3c = 0;
	evt_CloseAllScripts();
	if (g_7749cc != 0) {
		gv_SpawnIfPending(g_7749cc);
	}
	if (g_774934 != 0) {
		d3snd_StopTrackedVoices();
		d3snd_StopAllObjectSounds();
		if (g_7747bc != 0) {
			fcn_004230e0(g_7747bc);
			g_7747bc = 0;
			fcn_004230e0(g_7747c0);
			g_7747c0 = 0;
			fcn_004230e0(g_7747c4);
			g_7747c4 = 0;
			fcn_004230e0(g_7747c8);
			g_7747c8 = 0;
			fcn_004230e0(g_7747cc);
			g_7747cc = 0;
			fcn_004230e0(g_6b5c2c);
			g_6b5c2c = 0;
		}
	}
	hst_ResetHistoryState();
	gm_ClearMissionJobs();
	he_FreeAllActions();
	d2_ClearActionPopupSlots();
	he_ShutdownEventSystem();
	fcn_00527420();
	gm_KillAllSpieler();
	gm_ResetAllEntities();
	gm_CleanupObjectEntities();
	for (entry = (int*) 0x14d0020; (int) entry < 0x14d0c20; entry++) {
		if (*entry != 0) {
			ch_DestroyCharacter(*entry);
		}
	}
	if (g_7e453c != 0) {
		((int (*)(char)) fcn_004162c0)(g_7e453c);
		g_7e453c = 0;
	}
	if (g_7e4538 != 0) {
		d3_DestroyRain(g_7e4538);
		g_7e4538 = 0;
	}
	if (g_6b89c0 != 0) {
		int ctx = g_6b89c0;
		for (entry = (int*) 0x7e4540; (int) entry < 0x7e4558; entry++) {
			if (*entry != 0) {
				fcn_004597f0(ctx, *entry);
				ctx = g_6b89c0;
				*entry = 0;
			}
		}
		fcn_00459b40(ctx);
		g_6b89c0 = 0;
	}
	g_6b8061 = 0;
	if (g_6b5cf8 != 0) {
		fcn_00418ae0(g_6b5cf8);
		g_6b5cf8 = 0;
	}
	d3_ActiveCameraAnimation = 0;
	d3_ClearAllSceneContexts();
	fcn_005c80d0();
	fcn_004bbd50();
	fcn_004c3e30();
	nt_CloseBroadcastSocket();
	nt_CloseClientConnection();
	g_77497c = 0;
	d2_SetOverlayAnimation(0, 0);
	g_7e2aa0 = 0;
	g_7746cc = 0;
	g_7746c4 = 0;
	g_7746c8 = 0;
}
