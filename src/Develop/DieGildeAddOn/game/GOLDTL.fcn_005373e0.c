extern int g_774650;
extern int g_774658;
#include "client_dialog_state.h"
extern int g_774670;
extern int g_77493c;
extern int g_774708;
extern int g_774954;
extern int g_774938;
extern int g_774934;
extern int msx_MusicEnabled;
extern int g_7e35c0[];
extern int main_LoopFlags;
extern int g_7e2700;
extern int d3_SelectionBoxActive;
#include "Develop/DieGildeAddOn/game/game_player.h"
extern int g_7f4c04;
extern char g_7f4ca0[];
extern int g_14a5544;
extern unsigned int g_aecde4;
extern volatile unsigned int g_6b7fac;
extern int g_14cbca0;
extern char g_774964;
extern char g_774660;
extern char g_6a33f4[];
extern int g_6a2c08;
extern char gm_GameTime[];
extern int d3_CurrentContextIndex;
extern int d3_ActiveCamera;
extern int g_6b8008;
extern int g_773dd8;
extern int g_7746c4;
extern int g_7746c8;
extern int g_67530c;
extern int g_6a2c04;
extern int g_7e4534;
extern int g_6b8300;
extern int g_772f6c;
extern int g_14ce8e8;
extern int d2_CurrentElementId;
extern int g_1015ea0;
extern int g_7746a4;
extern int sv_HoveredObjekt;
extern int g_774668;
extern int d3_ActiveCameraAnimation;
extern int d2_SuppressOverlay;
extern int g_7749e4;
extern int g_67d8dc;
extern int g_6a99e8;
extern int g_6a25ac;
extern int g_6a2c0c;
extern int g_772f54;
extern char g_14cf71d;
extern char g_14cf738;
extern int g_7746cc;
extern int g_6b5de0;
extern char g_1052be0[];
extern char g_7747b0;
extern unsigned char g_14cf950;
extern short g_14cf900;
extern short g_14cf902;
extern int d2_MouseX;
extern int d2_MouseY;
extern int tp_d2_SelectedControl;
extern int g_14ce8cc;
extern int g_67d8d4;
extern int g_6a25a8;
extern int g_774800;
extern int g_774960;
extern char g_774966;
extern int g_6a25a0;
extern int g_6a257c;
extern int g_6a2584;
extern int g_6a2588;
extern int g_6a258c;
extern int g_6a2580;
extern int g_6a2578;
extern int g_100f1dc;
extern int g_6a24e8;
extern int g_fb5744;
extern int g_14a5524;
extern int g_6a3760;
extern char g_7747ad;
extern char g_774988[];
extern int cm_SaveRequestSlot;
extern unsigned int g_772e84;
extern int g_14ac5e8;
#include "GOLDTL.fcn_005373e0_gconf.h"
extern char g_5438c0[];
extern char g_7e1f70[];
extern char g_6b5c60[];
extern char g_6a33c8[];
extern char g_6a33dc[];
extern char g_6a33e8[];
extern int g_6772c4;
extern int g_7766a0;
extern float g_665e44;
extern float g_662a68;

extern void *memcpy(void *, const void *, unsigned int);

extern void main_PumpWindowMessages();
extern void fcn_412630();
extern void io_ClearInputState();
extern int cut_FindCutsceneById();
extern void fcn_00533a40();
extern void d2_ProcessMouseInput();
extern void fcn_00533090();
extern void ReportClientMessage();
extern void fcn_00545aa0();
extern void he_RunQueuedActions();
extern void cm_RequestUpdateGameTime();
extern int cut_UpdateCutscenes();
extern void cm_FlushCommandQueue();
extern void cm_PollCommandQueue();
extern void cm_ExecCommand();
extern void ProcessActiveContexts();
extern void fcn_465fe0();
extern void fcn_0052a960();
extern void d3_UpdateFrustumCellVisibility();
extern void fcn_00413380();
extern void fcn_00444190();
extern void ch_CollectContextCharacters();
extern void d3_UpdateBuildingSceneScripts();
extern void fcn_00529890();
extern void ch_UpdatePendingPositions();
extern void ch_Update();
extern void ch_UpdateCharacterObjectPositions();
extern void gm_UpdateWeatherWave();
extern void fcn_004efde0();
extern void d3_UpdateWeatherAndSkyBlend();
extern void fcn_004c0cd0();
extern void gm_UpdateAmbientAudio();
extern void fcn_004c0b40();
extern void msx_StopOutdoorTrackOnSeason();
extern void d3_UpdateLightningAndThunder();
extern void fcn_00415d70();
extern void d3_UpdateSelectionBoxCharacters();
extern void d3_UpdateCharacterBoxSelection();
extern void d3_DrawSelectionBox();
extern void d3snd_UpdateSoundSources();
extern void d3snd_UpdateAmbientSources();
extern void fcn_00422150();
extern void sv_UpdateSceneHover();
extern void fcn_00475220();
extern void d2_SetOverlayAnimation();
extern void sv_HandleObjects();
extern void fcn_00531620();
extern void d2_UpdateHoverTooltip();
extern void d2_UpdateSceneTooltip();
extern void fcn_00527f60();
extern void fcn_0046a110();
extern void fcn_004da1b0();
extern void fcn_00532650();
extern void fcn_00532900();
extern void fcn_005329a0();
extern void fcn_4d03e0();
extern void fcn_00532bd0();
extern void fcn_005337a0();
extern void fcn_005337f0();
extern void fcn_00526b70();
extern void fcn_0047c560();
extern void fcn_0047cdf0();
extern void fcn_00472a50();
extern void fcn_00411fe0();
extern void fcn_00537320();
extern void fcn_0041bcb0();
extern void SetMasterVolume();
extern void sb_SetMasterVolume();
extern void fcn_5e43f0();
extern void fcn_00536b10();
extern void d2_RunChatConsole();
extern void main_RunAdvanceGameDialog();
extern void main_ExitToFrameHandler();
extern void fcn_005e4c50();
extern void fcn_005924d0();
extern void main_ProcessGameHotkeys();
extern void d2_ShowPrivilegien();
extern void fcn_005d46d0();
extern void d2_ShowInventoryDialog();
extern void d2_OpenPlayerStats();
extern void d2_RunMessageFilterDialog();
extern void fcn_005d42e0();
extern void fcn_005d0660();
extern void tb_SetCallbackPaused();
extern void d2_RunMessageBox();
extern void fcn_004b6470();
extern void fcn_64d41a();
extern void ls_SaveNetworkGame();
extern void cm_SaveGameAndWait();


/* ADDRESS: GOLDTL 0x005373e0 */
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
		if (*(int *) ((char *) g_7e35c0 + g_774650 * 8) != a0) {
			io_ClearInputState();
		}
		if (g_774970 != 0xffff) {
			if ((g_7f4ca0[(unsigned short) g_774970 * 540 + 2] == 6 ||
				g_7f4ca0[(unsigned short) g_774970 * 540 + 2] == 7) &&
				g_7f4ca0[(unsigned short) g_774970 * 540 + 8] == 0 &&
				g_774650 > g_774658) {
				p = (char *) cut_FindCutsceneById(
					*(int *) (g_7f4ca0 + (unsigned short) g_774970 * 540 + 0x20c));
				if (p != 0 && p[8] == 8 && !(flags & 0x10000)) {
					g_774654 = g_774650 - g_774658;
					fcn_00533a40(g_14a5544);
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
	if (g_774654 == 0 && (flags & 0x100) && !(flags & 0x100000)) {
		fcn_00533090(flags);
	}
	g_774708 = a0;
	if (a0 != 0) {
		if (*(int *) ((char *) g_7e35c0 + g_774650 * 8) == a0) {
			result = 1;
		} else if (g_774654 != 0) {
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
				*(int *) ((char *) g_7e35c0 + g_774650 * 8) = a0;
			}
		}
		if (g_774654 != 0 && result != 0) {
			g_774654--;
			if (g_774650 != 0) {
				*(int *) ((char *) g_7e35c0 + g_774650 * 8) = z;
				g_774650--;
			}
			result = 0;
		}
	} else {
		result = 1;
	}
	if ((flags & 1) && g_774954 == 0) {
		if (flags & 0x100) {
			fcn_00545aa0();
		}
		he_RunQueuedActions();
		if (g_14cbca0 == -1 && g_6b7fac > g_aecde4 && g_774964 != 0) {
			cm_RequestUpdateGameTime(g_7e1f70);
		}
		if (!(flags & 0x10000) && g_774964 != 0 && g_7e2700 == 0 &&
			cut_UpdateCutscenes() != 0 && g_774660 != 0) {
			g_774654 = 1;
		}
	}
	if (flags & 0x20000) {
		if (g_6b7fac > g_aecde4) {
			cm_FlushCommandQueue();
			cm_PollCommandQueue();
			cm_ExecCommand();
			g_aecde4 = g_6b7fac + 7;
		}
	}
	if (result == 0 || g_7e2700 != 0) {
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
				fcn_0052a960(gm_GameTime);
			}
			if (d3_CurrentContextIndex == 0) {
				d3_UpdateFrustumCellVisibility(g_773dd8, d3_ActiveCamera, g_6b8008);
			}
			fcn_00413380();
			fcn_00444190();
		}
	}
	i = g_7746c4;
	if (i == 0) {
		i = g_7746c8;
	}
	z = flags & 0x8000;
	if (z == 0 && g_774964 != 0) {
		ch_CollectContextCharacters(i);
	}
	if (i != 0 && !(flags & 0x10000)) {
		d3_UpdateBuildingSceneScripts(i);
		fcn_00529890(i);
		g_67530c = *(int *) (i + 1);
	} else {
		g_67530c = -1;
	}
	if (g_6a2c04 != 0) {
		ch_UpdatePendingPositions();
		ch_Update();
		ch_UpdateCharacterObjectPositions();
	}
	if (g_774964 != 0) {
		gm_UpdateWeatherWave();
		fcn_004efde0();
	}
	p = (char *) (flags & 0x4000);
	if (p != 0 && (g_7f4c04 & 0xffff) != g_7e4534) {
		d3_UpdateWeatherAndSkyBlend();
	}
	if (g_774938 != 0) {
		fcn_004c0cd0();
	}
	if (g_774934 != 0) {
		gm_UpdateAmbientAudio();
		fcn_004c0b40();
	}
	if (msx_MusicEnabled != 0 && (flags & 0x40000)) {
		msx_StopOutdoorTrackOnSeason();
	}
	if (g_774670 == 0) {
		if (g_6b8300 != 0 && p != 0 && (flags & 0x40)) {
			d3_UpdateLightningAndThunder();
		}
		if (g_774670 == 0) {
			if ((flags & 0x10000) && g_772f6c != 0) {
				fcn_00415d70(g_772f6c);
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
	if (g_774934 != 0) {
		d3snd_UpdateSoundSources();
		if (g_774938 != 0) {
			d3snd_UpdateAmbientSources();
		}
		fcn_00422150();
	}
	if (g_774654 == 0 && !(flags & 0x100000)) {
		if (z == 0) {
			sv_UpdateSceneHover();
		}
		f = flags & 0x10;
		if (f == 0) {
			if (g_14ce8e8 == 0) {
				if (d2_CurrentElementId == -1 ||
					!(*(char *) (g_1015ea0 + d2_CurrentElementId * 756 + 0x1d0) & 0x40)) {
					fcn_00475220(g_6b5c60);
				}
				g_7746a4 = 0;
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
				fcn_00531620();
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
			d3_SelectionBoxActive == 0 && d2_SuppressOverlay == 0 && g_7749e4 == 0)) {
			g_67d8dc = 0;
		} else {
			g_67d8dc = 1;
			if (g_6a99e8 != -1) {
				g_67d8dc = 0;
			}
		}
		if (g_6a25ac != -1 && (flags & 0x100) && g_6a2c0c != 0) {
			fcn_00527f60(2, flags);
		}
		fcn_0046a110((~flags >> 6) & 1);
		if (g_772f54 != 0) {
			fcn_004da1b0();
		}
		if (f != 0 && g_774650 == g_774658 && g_7749e4 == 0) {
			fcn_00532650();
			if (g_14cf71d != 0) {
				fcn_00532900();
			} else if (g_14cf738 != 0) {
				fcn_005329a0();
			}
		}
		if (flags & 0x80000) {
			fcn_4d03e0();
		} else if ((flags & 8) && (g_7746cc != 0 || g_7746c8 != 0)) {
			fcn_00532bd0();
		}
		if (f != 0 && g_14ce8e8 == 0 && g_774668 == 0 && d3_ActiveCameraAnimation == 0 &&
			d3_SelectionBoxActive == 0 && d2_SuppressOverlay == 0 && g_7749e4 == 0) {
			fcn_005337a0();
		}
		fcn_005337f0();
		fcn_00526b70();
		fcn_0047c560(0, 0, 0);
		(*(void (__stdcall **) (int, int)) (*(int *) g_6b5de0 + 0xa0))(g_6b5de0, (int) g_1052be0);
		fcn_0047cdf0();
	} else if (g_7e2700 != 0) {
		fcn_00472a50();
	}
	fcn_00411fe0();
	if (g_6772c4 != 0) {
		d2_MouseX = g_14cf900;
		d2_MouseY = g_14cf902;
	}
	fcn_00537320(flags);
	if (g_774670 == 0 && (flags & 0x80)) {
		fcn_0041bcb0();
	}
	if (g_14cf950 == 1 && (flags & 0x2000)) {
		t = (float) (g_7766a0 & 0xff) * g_665e44;
		SetMasterVolume((int) (((float) *((unsigned char *) &g_7766a0 + 2) * t) * 0.33333334f));
		sb_SetMasterVolume((int) (((float) *((unsigned char *) &g_7766a0 + 1) * t) * 0.33333334f));
		fcn_5e43f0();
		t = (float) (g_7766a0 & 0xff) * g_665e44;
		SetMasterVolume((int) ((float) *((unsigned char *) &g_7766a0 + 2) * t));
		sb_SetMasterVolume((int) ((float) *((unsigned char *) &g_7766a0 + 1) * t));
	}
	fcn_00536b10();
	if (g_774964 != 0) {
		if ((g_7747b0 & 4) && tp_d2_SelectedControl == 0 && g_14cf950 == 0x1c && (flags & 0x2000)) {
			d2_RunChatConsole();
		}
		if (g_774964 != 0) {
			if (g_14cf950 == 0xcf || (g_14ce8cc != 0 && g_67d8d4 == g_6a25a8)) {
				if (!(flags & 0x10000) && g_774660 == 0 && !(g_7747b0 & 4)) {
					if (g_774800 == 0) {
						main_RunAdvanceGameDialog();
					} else {
						g_774960 = 1;
						main_ExitToFrameHandler(g_5438c0);
					}
				}
			}
			if (g_774964 != 0) {
				if (g_774966 == 0 && !(g_7747b0 & 4) && z == 0 && g_14cf950 == 0x39) {
					fcn_005e4c50();
				}
				if (g_774964 != 0 && !(flags & 0x300000)) {
					fcn_005924d0();
				}
			}
		}
	}
	if (g_6a25ac != -1 && (flags & 0x2000) && !(flags & 0x100000) &&
		g_774650 == g_774658) {
		if (g_774964 != 0) {
			main_ProcessGameHotkeys();
		}
		if (g_774970 != 0xffff && (unsigned char) g_7f4ca0[(unsigned short) g_774970 * 540 + 8] > 0) {
			if (g_100f1dc != -1) {
				i = d2_CurrentElementId;
				if (i == g_6a25a0) {
					d2_ShowPrivilegien();
				} else if (i == g_6a257c) {
					fcn_005d46d0();
				} else if (i == g_6a2584) {
					d2_ShowInventoryDialog();
				} else if (i == g_6a2588) {
					d2_OpenPlayerStats();
				} else if (i == g_6a258c) {
					d2_RunMessageFilterDialog();
				} else if (i == g_6a2580) {
					fcn_005d42e0();
				} else if (i == g_6a2578) {
					fcn_005d0660(*(int *) (g_7f4ca0 + (unsigned short) g_774970 * 540 + 4),
						0x11, 0, 0x657c7);
				}
			}
		} else if (g_100f1dc != -1) {
			i = d2_CurrentElementId;
			if (i == g_6a25a0 || i == g_6a257c || i == g_6a2584 ||
				i == g_6a2588 || i == g_6a2580 || i == g_6a2578) {
				fcn_00533a40(g_14a5544);
			}
		}
	}
	g_6a24e8++;
	i = flags & 0x10000;
	if (i == 0) {
		if ((g_774654 == 0 && g_7e2700 == 0 && g_fb5744 != 0 && g_774960 == 0) ||
			(g_14cbca0 == -1 && (unsigned short) g_7f4c04 >= 0x17 && g_774960 == 0)) {
			if (!((g_7747b0 & 0x80))) {
				g_774960 = 1;
				tb_SetCallbackPaused(g_538060, 1);
				main_LoopFlags |= 0x100000;
				d2_RunMessageBox(g_14a5524, 0xc4);
				main_ExitToFrameHandler(g_5438c0);
			}
		}
	}
	if (g_774960 != 0 && g_774654 == 0 &&
		*(int *) ((char *) g_7e35c0 + g_774650 * 8) == (int) 0x59a340) {
		g_774654 = 1;
	}
	if (i == 0 && g_7747ad == 0 && g_6a3760 != -1 && g_774964 != 0) {
		g_7747ad = 1;
		tb_SetCallbackPaused(g_538060, 1);
		fcn_004b6470(0x65fff);
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
