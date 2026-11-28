extern int g_774650;
extern int g_774658;
#include "Develop/Units/d2.v1/client_dialog_state.h"
extern int g_774670;
extern int g_77493c;
extern int g_774708;
extern int g_774954;
extern int g_774938;
extern int d3snd_SoundEnabled;
extern int msx_MusicEnabled;
extern int main_FrameHandlerStack[];
extern int main_LoopFlags;
extern int d2_InsideBuildingActive;
extern int d3_SelectionBoxActive;
#include "Develop/DieGildeAddOn/game/game_player.h"
extern int gm_GameTimeHour;
extern char gm_EntitySlotTable[];
extern int g_14a5544;
extern unsigned int g_aecde4;
extern volatile unsigned int gm_GameTicks;
extern int nt_ClientSocket;
extern char gm_InWorldHud;
extern char g_774660;
extern char g_6a33f4[];
extern int g_6a2c08;
extern char gm_GameTime[];
extern int d3_CurrentContextIndex;
extern int d3_ActiveCamera;
extern int g_6b8008;
extern int g_773dd8;
extern int d2_VisitedBuilding;
extern int d2_InteriorBuilding;
extern int g_67530c;
extern int g_6a2c04;
extern int g_7e4534;
extern int d3_CurrentFloor;
extern int g_772f6c;
extern int g_14ce8e8;
extern int d2_CurrentElementId;
extern int d2_Controls;
extern int d2_HoveredSceneObject;
extern int sv_HoveredObjekt;
extern int g_774668;
extern int d3_ActiveCameraAnimation;
extern int d2_SuppressOverlay;
extern int tp_d2_ActiveHudSlot;
extern int g_67d8dc;
extern int g_6a99e8;
extern int g_6a25ac;
extern int g_6a2c0c;
extern int cut_StartTick;
extern char g_14cf71d;
extern char g_14cf738;
extern int sv_SelectedBuilding;
extern int g_6b5de0;
extern char g_1052be0[];
extern char gm_ClientModeFlags;
extern unsigned char io_LastKeyScancode;
extern short io_PolledCursorState;
extern short io_PolledCursorY;
extern int d2_MouseX;
extern int d2_MouseY;
extern int tp_d2_SelectedControl;
extern int g_14ce8cc;
extern int g_67d8d4;
extern int g_6a25a8;
extern int gm_AllEntitiesControllable;
extern int g_774960;
extern char g_774966;
extern int g_6a25a0;
extern int g_6a257c;
extern int g_6a2584;
extern int g_6a2588;
extern int g_6a258c;
extern int g_6a2580;
extern int g_6a2578;
extern int d2_DialogButtonAction;
extern int main_FrameCounter;
extern int g_fb5744;
extern int g_14a5524;
extern int g_6a3760;
extern char g_7747ad;
extern char g_774988[];
extern int cm_SaveRequestSlot;
extern unsigned int g_772e84;
extern int g_14ac5e8;
extern char g_538060[];
extern char g_5438c0[];
extern char gm_SyncGameTime[];
extern char str_empty[];
extern char g_6a33c8[];
extern char g_6a33dc[];
extern char g_6a33e8[];
extern int g_6772c4;
extern int msx_AudioVolumeSettings;
extern float g_665e44;
extern float g_662a68;

extern void *memcpy(void *, const void *, unsigned int);

extern void main_PumpWindowMessages();
extern void fcn_412630();
extern void io_ClearInputState();
extern int cut_FindCutsceneById();
extern void d2_ShowStatusBanner();
extern void d2_ProcessMouseInput();
extern void d2_UpdateBuildingCameraAndUi();
extern void ReportClientMessage();
extern void d2_UpdateActionPopupFocus();
extern void he_RunQueuedActions();
extern void cm_RequestUpdateGameTime();
extern int cut_UpdateCutscenes();
extern void cm_FlushCommandQueue();
extern void cm_PollCommandQueue();
extern void cm_ExecCommand();
extern void ProcessActiveContexts();
extern void fcn_465fe0();
extern void d3_UpdateDaylightPhase();
extern void d3_UpdateFrustumCellVisibility();
extern void d3_UpdateCameraAnimAndSunRays();
extern void d3_RenderDefaultFrame();
extern void ch_CollectContextCharacters();
extern void d3_UpdateBuildingSceneScripts();
extern void d2_UpdateBuildingWorkerSlots();
extern void ch_UpdatePendingPositions();
extern void ch_Update();
extern void ch_UpdateCharacterObjectPositions();
extern void gm_UpdateWeatherWave();
extern void d3_UpdateCannonProjectiles();
extern void d3_UpdateWeatherAndSkyBlend();
extern void d3snd_UpdateRainSoundTier();
extern void gm_UpdateAmbientAudio();
extern void d3snd_UpdateVoiceQueue();
extern void msx_StopOutdoorTrackOnSeason();
extern void d3_UpdateLightningAndThunder();
extern void d3_RenderRainLines();
extern void d3_UpdateSelectionBoxCharacters();
extern void d3_UpdateCharacterBoxSelection();
extern void d3_DrawSelectionBox();
extern void d3snd_UpdateSoundSources();
extern void d3snd_UpdateAmbientSources();
extern void sb_UpdateVoices();
extern void sv_UpdateSceneHover();
extern void d2_SetMouseTooltip();
extern void d2_SetOverlayAnimation();
extern void sv_HandleObjects();
extern void sv_UpdateObjectSelection();
extern void d2_UpdateHoverTooltip();
extern void d2_UpdateSceneTooltip();
extern void d2_RefreshTownView();
extern void d2_RenderAllElements();
extern void d2_DrawElapsedTimer();
extern void d2_RenderHoverTooltips();
extern void d2_DrawBuildingUpgradeLabels();
extern void d2_DrawBuildingItemLabels();
extern void fcn_4d03e0();
extern void d2_DrawCameraScrollArrows();
extern void d2_DrawMouseTooltip();
extern void d2_DrawStatusBannerText();
extern void d2_UpdateMouseCursorOffset();
extern void d2_FlushQueuedQuads();
extern void d2_ResetDrawState();
extern void d2_SweepFadeOverlays();
extern void io_PollMouseInput();
extern void d2_UpdateViewportCenter();
extern void d3_PresentFrame();
extern void SetMasterVolume();
extern void sb_SetMasterVolume();
extern void fcn_5e43f0();
extern void d2_UpdateQuickChatOverlay();
extern void d2_RunChatConsole();
extern void main_RunAdvanceGameDialog();
extern void main_ExitToFrameHandler();
extern void d2_PauseGameLoop();
extern void main_HandleHotkeyAction();
extern void main_ProcessGameHotkeys();
extern void d2_ShowPrivilegien();
extern void d2_RunPlayerRankingDialog();
extern void d2_ShowInventoryDialog();
extern void d2_OpenPlayerStats();
extern void d2_RunMessageFilterDialog();
extern void d2_RunStadtStatistikDialog();
extern void d2_RunStammbaumDialog();
extern void tb_SetCallbackPaused();
extern void d2_RunMessageBox();
extern void d2_HandleMissionTurnEnd();
extern void fcn_64d41a();
extern void ls_SaveNetworkGame();
extern void cm_SaveGameAndWait();


/* ADDRESS: GOLDTL 0x005373e0 */
/* ADDRESS: GOLDDE 0x0051ed60 */
int __cdecl main_RunFrameLoop(int a0, unsigned int flags)
{
	int result;
	float t;
	int z;
	char s[260];
	char buf[260];
	int i;
	int f;
	char *p;
	int addr;

	z = 0;
	main_LoopFlags = flags;
	main_PumpWindowMessages();
	fcn_412630();
	if (a0 != 0) {
		if (*(int *) ((char *) main_FrameHandlerStack + g_774650 * 8) != a0) {
			io_ClearInputState();
		}
		if (gm_LocalPlayerSlot != 0xffff) {
			if ((gm_EntitySlotTable[(unsigned short) gm_LocalPlayerSlot * 540 + 2] == 6 ||
				gm_EntitySlotTable[(unsigned short) gm_LocalPlayerSlot * 540 + 2] == 7) &&
				gm_EntitySlotTable[(unsigned short) gm_LocalPlayerSlot * 540 + 8] == 0 &&
				g_774650 > g_774658) {
				p = (char *) cut_FindCutsceneById(
					*(int *) (gm_EntitySlotTable + (unsigned short) gm_LocalPlayerSlot * 540 + 0x20c));
				if (p != 0 && p[8] == 8 && !(flags & 0x10000)) {
					d2_DialogCloseRequested = g_774650 - g_774658;
					d2_ShowStatusBanner(g_14a5544);
				}
			}
		}
	}
	if (flags & 4) {
		d2_ProcessMouseInput();
	}
	if (g_77493c != 0) {
		g_774670 = 1;
	}
	if (d2_DialogCloseRequested == 0 && (flags & 0x100) && !(flags & 0x100000)) {
		d2_UpdateBuildingCameraAndUi(flags);
	}
	g_774708 = a0;
	if (a0 != 0) {
		if (*(int *) ((char *) main_FrameHandlerStack + g_774650 * 8) == a0) {
			result = 1;
		} else if (d2_DialogCloseRequested != 0) {
			result = 0;
		} else {
			result = 1;
			for (addr = 0x7e35c0; addr < 0x7e39c0; addr += 8) {
				if (*(int *) addr == a0) {
					ReportClientMessage(g_6a33f4);
					result = 0;
					break;
				}
			}
			if (result != 0) {
				g_774650++;
				*(int *) ((char *) main_FrameHandlerStack + g_774650 * 8) = a0;
			}
		}
		if (d2_DialogCloseRequested != 0 && result != 0) {
			d2_DialogCloseRequested--;
			if (g_774650 != 0) {
				*(int *) ((char *) main_FrameHandlerStack + g_774650 * 8) = z;
				g_774650--;
			}
			result = 0;
		}
	} else {
		result = 1;
	}
	if ((flags & 1) && g_774954 == 0) {
		if (flags & 0x100) {
			d2_UpdateActionPopupFocus();
		}
		he_RunQueuedActions();
		if (nt_ClientSocket == -1 && gm_GameTicks > g_aecde4 && gm_InWorldHud != 0) {
			cm_RequestUpdateGameTime(gm_SyncGameTime);
		}
		if (!(flags & 0x10000) && gm_InWorldHud != 0 && d2_InsideBuildingActive == 0 &&
			cut_UpdateCutscenes() != 0 && g_774660 != 0) {
			d2_DialogCloseRequested = 1;
		}
	}
	if (flags & 0x20000) {
		if (gm_GameTicks > g_aecde4) {
			cm_FlushCommandQueue();
			cm_PollCommandQueue();
			cm_ExecCommand();
			g_aecde4 = gm_GameTicks + 7;
		}
	}
	if (result == 0 || d2_InsideBuildingActive != 0) {
		g_774670++;
	}
	if (flags & 0x200) {
		ProcessActiveContexts();
	}
	if (g_774670 == 0) {
		if (flags & 0x80) {
			fcn_465fe0();
		}
		if (g_774670 == 0 && (flags & 0x40) && g_6a2c08 != 0) {
			if (!(flags & 0x10000) && (flags & 0x40000)) {
				d3_UpdateDaylightPhase(gm_GameTime);
			}
			if (d3_CurrentContextIndex == 0) {
				d3_UpdateFrustumCellVisibility(g_773dd8, d3_ActiveCamera, g_6b8008);
			}
			d3_UpdateCameraAnimAndSunRays();
			d3_RenderDefaultFrame();
		}
	}
	i = d2_VisitedBuilding;
	if (i == 0) {
		i = d2_InteriorBuilding;
	}
	z = flags & 0x8000;
	if (z == 0 && gm_InWorldHud != 0) {
		ch_CollectContextCharacters(i);
	}
	if (i != 0 && !(flags & 0x10000)) {
		d3_UpdateBuildingSceneScripts(i);
		d2_UpdateBuildingWorkerSlots(i);
		g_67530c = *(int *) (i + 1);
	} else {
		g_67530c = -1;
	}
	if (g_6a2c04 != 0) {
		ch_UpdatePendingPositions();
		ch_Update();
		ch_UpdateCharacterObjectPositions();
	}
	if (gm_InWorldHud != 0) {
		gm_UpdateWeatherWave();
		d3_UpdateCannonProjectiles();
	}
	p = (char *) (flags & 0x4000);
	if (p != 0 && (gm_GameTimeHour & 0xffff) != g_7e4534) {
		d3_UpdateWeatherAndSkyBlend();
	}
	if (g_774938 != 0) {
		d3snd_UpdateRainSoundTier();
	}
	if (d3snd_SoundEnabled != 0) {
		gm_UpdateAmbientAudio();
		d3snd_UpdateVoiceQueue();
	}
	if (msx_MusicEnabled != 0 && (flags & 0x40000)) {
		msx_StopOutdoorTrackOnSeason();
	}
	if (g_774670 == 0) {
		if (d3_CurrentFloor != 0 && p != 0 && (flags & 0x40)) {
			d3_UpdateLightningAndThunder();
		}
		if (g_774670 == 0) {
			if ((flags & 0x10000) && g_772f6c != 0) {
				d3_RenderRainLines(g_772f6c);
			}
			if (g_774670 == 0 && d3_SelectionBoxActive != 0) {
				if (z != 0) {
					d3_UpdateSelectionBoxCharacters();
				} else {
					d3_UpdateCharacterBoxSelection();
				}
				d3_DrawSelectionBox();
			}
		}
	}
	if (d3snd_SoundEnabled != 0) {
		d3snd_UpdateSoundSources();
		if (g_774938 != 0) {
			d3snd_UpdateAmbientSources();
		}
		sb_UpdateVoices();
	}
	if (d2_DialogCloseRequested == 0 && !(flags & 0x100000)) {
		if (z == 0) {
			sv_UpdateSceneHover();
		}
		f = flags & 0x10;
		if (f == 0) {
			if (g_14ce8e8 == 0) {
				if (d2_CurrentElementId == -1 ||
					!(*(char *) (d2_Controls + d2_CurrentElementId * 756 + 0x1d0) & 0x40)) {
					d2_SetMouseTooltip(str_empty);
				}
				d2_HoveredSceneObject = 0;
				sv_HoveredObjekt = 0;
				if (z == 0) {
					d2_SetOverlayAnimation(0, 0);
				}
			}
		}
		if (g_14ce8e8 == 0) {
			if (f != 0) {
				sv_HandleObjects();
			}
			if (flags & 0x20) {
				sv_UpdateObjectSelection();
				d2_UpdateHoverTooltip();
			}
		}
	}
	if (flags & 0x400) {
		d2_UpdateSceneTooltip();
	}
	if (g_774670 == 0 && (flags & 0x80)) {
		f = flags & 0x1000;
		if (!(f != 0 && g_14ce8e8 == 0 && g_774668 == 0 && d3_ActiveCameraAnimation == 0 &&
			d3_SelectionBoxActive == 0 && d2_SuppressOverlay == 0 && tp_d2_ActiveHudSlot == 0)) {
			g_67d8dc = 0;
		} else {
			g_67d8dc = 1;
			if (g_6a99e8 != -1) {
				g_67d8dc = 0;
			}
		}
		if (g_6a25ac != -1 && (flags & 0x100) && g_6a2c0c != 0) {
			d2_RefreshTownView(2, flags);
		}
		d2_RenderAllElements((~flags >> 6) & 1);
		if (cut_StartTick != 0) {
			d2_DrawElapsedTimer();
		}
		if (f != 0 && g_774650 == g_774658 && tp_d2_ActiveHudSlot == 0) {
			d2_RenderHoverTooltips();
			if (g_14cf71d != 0) {
				d2_DrawBuildingUpgradeLabels();
			} else if (g_14cf738 != 0) {
				d2_DrawBuildingItemLabels();
			}
		}
		if (flags & 0x80000) {
			fcn_4d03e0();
		} else if ((flags & 8) && (sv_SelectedBuilding != 0 || d2_InteriorBuilding != 0)) {
			d2_DrawCameraScrollArrows();
		}
		if (f != 0 && g_14ce8e8 == 0 && g_774668 == 0 && d3_ActiveCameraAnimation == 0 &&
			d3_SelectionBoxActive == 0 && d2_SuppressOverlay == 0 && tp_d2_ActiveHudSlot == 0) {
			d2_DrawMouseTooltip();
		}
		d2_DrawStatusBannerText();
		d2_UpdateMouseCursorOffset();
		d2_FlushQueuedQuads(0, 0, 0);
		(*(void (__stdcall **) (int, int)) (*(int *) g_6b5de0 + 0xa0))(g_6b5de0, (int) g_1052be0);
		d2_ResetDrawState();
	} else if (d2_InsideBuildingActive != 0) {
		d2_SweepFadeOverlays();
	}
	io_PollMouseInput();
	if (g_6772c4 != 0) {
		d2_MouseX = io_PolledCursorState;
		d2_MouseY = io_PolledCursorY;
	}
	d2_UpdateViewportCenter(flags);
	if (g_774670 == 0 && (flags & 0x80)) {
		d3_PresentFrame();
	}
	if (io_LastKeyScancode == 1 && (flags & 0x2000)) {
		t = (float) (msx_AudioVolumeSettings & 0xff) * g_665e44;
		SetMasterVolume((int) (((float) *((unsigned char *) &msx_AudioVolumeSettings + 2) * t) * 0.33333334f));
		sb_SetMasterVolume((int) (((float) *((unsigned char *) &msx_AudioVolumeSettings + 1) * t) * 0.33333334f));
		fcn_5e43f0();
		t = (float) (msx_AudioVolumeSettings & 0xff) * g_665e44;
		SetMasterVolume((int) ((float) *((unsigned char *) &msx_AudioVolumeSettings + 2) * t));
		sb_SetMasterVolume((int) ((float) *((unsigned char *) &msx_AudioVolumeSettings + 1) * t));
	}
	d2_UpdateQuickChatOverlay();
	if (gm_InWorldHud != 0) {
		if ((gm_ClientModeFlags & 4) && tp_d2_SelectedControl == 0 && io_LastKeyScancode == 0x1c && (flags & 0x2000)) {
			d2_RunChatConsole();
		}
		if (gm_InWorldHud != 0) {
			if (io_LastKeyScancode == 0xcf || (g_14ce8cc != 0 && g_67d8d4 == g_6a25a8)) {
				if (!(flags & 0x10000) && g_774660 == 0 && !(gm_ClientModeFlags & 4)) {
					if (gm_AllEntitiesControllable == 0) {
						main_RunAdvanceGameDialog();
					} else {
						g_774960 = 1;
						main_ExitToFrameHandler(g_5438c0);
					}
				}
			}
			if (gm_InWorldHud != 0) {
				if (g_774966 == 0 && !(gm_ClientModeFlags & 4) && z == 0 && io_LastKeyScancode == 0x39) {
					d2_PauseGameLoop();
				}
				if (gm_InWorldHud != 0 && !(flags & 0x300000)) {
					main_HandleHotkeyAction();
				}
			}
		}
	}
	if (g_6a25ac != -1 && (flags & 0x2000) && !(flags & 0x100000) &&
		g_774650 == g_774658) {
		if (gm_InWorldHud != 0) {
			main_ProcessGameHotkeys();
		}
		if (gm_LocalPlayerSlot != 0xffff && (unsigned char) gm_EntitySlotTable[(unsigned short) gm_LocalPlayerSlot * 540 + 8] > 0) {
			if (d2_DialogButtonAction != -1) {
				i = d2_CurrentElementId;
				if (i == g_6a25a0) {
					d2_ShowPrivilegien();
				} else if (i == g_6a257c) {
					d2_RunPlayerRankingDialog();
				} else if (i == g_6a2584) {
					d2_ShowInventoryDialog();
				} else if (i == g_6a2588) {
					d2_OpenPlayerStats();
				} else if (i == g_6a258c) {
					d2_RunMessageFilterDialog();
				} else if (i == g_6a2580) {
					d2_RunStadtStatistikDialog();
				} else if (i == g_6a2578) {
					d2_RunStammbaumDialog(*(int *) (gm_EntitySlotTable + (unsigned short) gm_LocalPlayerSlot * 540 + 4),
						0x11, 0, 0x657c7);
				}
			}
		} else if (d2_DialogButtonAction != -1) {
			i = d2_CurrentElementId;
			if (i == g_6a25a0 || i == g_6a257c || i == g_6a2584 ||
				i == g_6a2588 || i == g_6a2580 || i == g_6a2578) {
				d2_ShowStatusBanner(g_14a5544);
			}
		}
	}
	main_FrameCounter++;
	i = flags & 0x10000;
	if (i == 0) {
		if ((d2_DialogCloseRequested == 0 && d2_InsideBuildingActive == 0 && g_fb5744 != 0 && g_774960 == 0) ||
			(nt_ClientSocket == -1 && (unsigned short) gm_GameTimeHour >= 0x17 && g_774960 == 0)) {
			if (!((gm_ClientModeFlags & 0x80))) {
				g_774960 = 1;
				tb_SetCallbackPaused(g_538060, 1);
				main_LoopFlags |= 0x100000;
				d2_RunMessageBox(g_14a5524, 0xc4);
				main_ExitToFrameHandler(g_5438c0);
			}
		}
	}
	if (g_774960 != 0 && d2_DialogCloseRequested == 0 &&
		*(int *) ((char *) main_FrameHandlerStack + g_774650 * 8) == (int) 0x59a340) {
		d2_DialogCloseRequested = 1;
	}
	if (i == 0 && g_7747ad == 0 && g_6a3760 != -1 && gm_InWorldHud != 0) {
		g_7747ad = 1;
		tb_SetCallbackPaused(g_538060, 1);
		d2_HandleMissionTurnEnd(0x65fff);
		tb_SetCallbackPaused(g_538060, 0);
		g_7747ad = 0;
	}
	if (g_774988[0] != 0 && !(main_LoopFlags & 0x200000)) {
		if (cm_SaveRequestSlot == 1) {
			memcpy(s, g_6a33e8, 10);
		} else if (cm_SaveRequestSlot == 0) {
			memcpy(s, g_6a33dc, 9);
		} else {
			fcn_64d41a(s, g_6a33c8, cm_SaveRequestSlot);
		}
		i = 0;
		do {
			buf[i] = g_774988[i];
		} while (g_774988[i++] != 0);
		g_774988[0] = 0;
		ls_SaveNetworkGame(s, buf);
	}
	if (g_772e84 > 0 && !(main_LoopFlags & 0x200000)) {
		g_772e84--;
		cm_SaveGameAndWait(flags, g_14ac5e8);
	}
	if (g_774670 > 0) {
		g_774670--;
	}
	return result;
}
