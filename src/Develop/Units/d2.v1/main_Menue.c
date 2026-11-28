#include "Develop/DieGildeAddOn/game/game_data.h"
extern int g_1040480;
extern int g_1040484;
extern int g_1040488;
extern int g_104048c;
extern int d2_ScreenHeight;
extern int g_1040494;
extern int d3_ViewportZFar;
extern int d3_ProjectionDist;
extern int d3_ViewportZNear;
extern int g_14ac498;
extern int g_14ac49c;
extern int g_14ac4a0;
extern int g_14ce8d8;
extern int d2_CurrentElementId;
extern int d2_SuppressOverlay;
extern int g_774650;
extern int d2_DialogCloseRequested;
extern int g_774658;
extern int msx_MusicEnabled;
extern int g_774954;
extern int g_77496c;
extern char g_7e1d00[];
extern char g_7e23e0[];
#include <string.h>
#include <windows.h>

typedef struct Handler Handler;

struct Handler {
	int unused;
};

void __cdecl io_PopQueuedInputState(void);
char *__cdecl d2_StartScreenFade(int, int, int, int, char *, int, int);
int __cdecl main_PumpWindowMessages(void);
int __cdecl main_RunFrameLoop(int, int);
void __cdecl d3_SelectSceneContext(int, int);
int __cdecl d3_ClearSceneState(void);
int __cdecl main_GetLanguage(void);
#include "Develop/Units/d3/client_scene_loader.h"
void __cdecl ReportClientMessage(char *);
void __cdecl d3_SetViewport(float, float, int, int, int, int, int, int, int);
void __cdecl d2_ClearScreen(void);
int __cdecl d2_SetBackdropResource(int);
int __cdecl d2_LoadForm(int, int, char *);
int __cdecl d2_CenterForm(int, int);
int __cdecl d2_SetForm(int, int);
int __cdecl d2_AddMainMenuButton(int, int, int);
int __cdecl d2_CreateRadioGroup(int, int, int, int, int, int, int, int, int, int);
int __cdecl fcn_0064d3f8(void);
int __cdecl msx_StartTrack(char *, int);
void __cdecl d2_ReleaseOverlaySprite(int);
void __cdecl msx_SetFadeDuration(int);
void __cdecl evt_ResetCurrentContextId(void);
int __cdecl d2_UpdateRadioGroup(int);
void __cdecl d2_SetSlotVisibility(int, int);
int __cdecl d2_OpenFileSelector(int, int, char *, char *, char *, char *);
int __cdecl fcn_0064d41a(char *, char *, char *, ...);
int __cdecl main_LoadCitySelectionScene(char *, int);
int __cdecl d2_ShowCreditsScreen(void);
void __cdecl msx_StartTrackInternal(int, int);
void __cdecl d2_ShowAmountDialog(void);
void __cdecl d2_ShowGameOptions(void);
void __cdecl d2_ShowSoundOptions(void);
void __cdecl d2_ShowGraphicsOptions(void);
int __cdecl d2_ShowLoadGameMenu(void);
int __cdecl d2_ShowChooseNetworkDialog(void);
int __cdecl d2_ChooseTutorial(void);
void __cdecl d2_InitDefaultMenueProfile(void);
void __cdecl d2_ClearBackdropResource(void);
void __cdecl gm_ResetHistoricalCursors(void);
int __cdecl d2_StartSinglePlayerChooseCity(void);
void __cdecl d2_ClearRadioGroup(int);
void __cdecl d2_DestroyForm(int);
void __cdecl msx_StopTrack(int, int);

/* Frame pointer kept: the reference restores esp from ebp and homes every
   local at [ebp-*] (FPO off). */
#pragma optimize("y", off)

/* ADDRESS: GOLDTL 0x0053a400 */
void __cdecl main_Menue(void)
{
	char v7[260];
	char v8[260];
	char profileValueA[96];
	char v10[260];
	char v11[260];
	char profileValueB[96];
	DWORD (WINAPI *read_profile)(LPCSTR, LPCSTR, LPCSTR, LPSTR, DWORD, LPCSTR);
	char *v4;
	char *v14;
	int v5;
	int b[12];
	int v28;
	int v15;
	unsigned char v29;

	b[9] = -1;
	b[1] = -1;
	b[2] = -1;
	b[5] = -1;
	b[0] = -1;
	main_PumpWindowMessages();
	io_PopQueuedInputState();
	*(unsigned char*) &io_LastKeyScancode = 0;
	evt_ResetCurrentContextId();
	v4 = d2_StartScreenFade(0, 0, g_1040494, d2_ScreenHeight, (char *)0x67d67c, 0, 1);
	while ((*(unsigned char *)v4 & 4) == 0) {
		main_RunFrameLoop(0, 0x24087);
	}
	d2_SuppressOverlay = 1;
	d3_SelectSceneContext(0, 0);
	d3_ClearSceneState();
	if (main_GetLanguage() != 0) {
		v14 = "scenes/*ChooseCity_Europa.ed3";
	} else {
		v14 = "scenes/*ChooseCity.ed3";
	}
	d3_LoadScene(v14, 0, 0);
	main_PumpWindowMessages();
	d3_SelectSceneContext(1, 0);
	d3_ClearSceneState();
	if (!d3_LoadScene((char *)0x6a3b98, 0, 0)) {
		ReportClientMessage((char *)0x6a3b70);
	}
	d3_SetViewport((float)g_1040494, (float)d2_ScreenHeight, 0, 0, d3_ViewportZNear, d3_ViewportZFar, d3_ProjectionDist, g_1040494, d2_ScreenHeight);
	g_774658 = g_774650 + 1;
	*(int*) &gm_ClientModeFlags = 0;
	v28 = 0x8c;
	__asm {
		mov edi, offset g_7e23e0
		mov ebx, v28
		xor eax, eax
		lea ecx, [edi+edi*2]
		and ecx, 3
		sub ebx, ecx
		jle short fill_done_menu
		rep stosb
		mov ecx, ebx
		and ebx, 3
		shr ecx, 2
		rep stosd
	fill_done_menu:
		add ecx, ebx
		rep stosb
	}
	g_1040480 = g_1040494;
	d2_SuppressOverlay = 0;
	g_1040488 = 0;
	g_1040484 = 0;
	g_104048c = d2_ScreenHeight;
	d2_ClearScreen();
	d2_SetBackdropResource(0x797);
	v29 = 0;
	v15 = d2_LoadForm(0, 0, (char *)0x6a3b60);
	d2_CenterForm(v15, 3);
	d2_SetForm(v15, 0);
	v5 = d2_CurrentWindowId;
	b[4] = d2_AddMainMenuButton(0, *(int *)0x14ac4ac, v5);
	b[7] = d2_AddMainMenuButton(1, *(int *)0x14ac490, v5);
	b[10] = d2_AddMainMenuButton(2, *(int *)0x14b4f84, v5);
	b[3] = d2_AddMainMenuButton(3, *(int *)0x14ac4b0, v5);
	b[8] = d2_AddMainMenuButton(4, g_14ac498, v5);
	b[11] = d2_AddMainMenuButton(7, *(int *)0x14ac4b4, v5);
	b[6] = d2_AddMainMenuButton(8, *(int *)0x14ac4b8, v5);
	if (*(int *)0x774814 == 0) {
		b[9] = d2_AddMainMenuButton(5, g_14ac49c, v5);
		b[1] = d2_AddMainMenuButton(6, g_14ac4a0, v5);
		v28 = d2_CreateRadioGroup(9, b[4], b[7], b[10], b[3], b[8], b[9], b[1], b[11], b[6]);
	} else {
		b[2] = d2_AddMainMenuButton(4, (int)(char *)0x6a3b48, v5);
		b[5] = d2_AddMainMenuButton(5, (int)(char *)0x6a3b30, v5);
		b[0] = d2_AddMainMenuButton(6, (int)(char *)0x6a3b20, v5);
		v28 = d2_CreateRadioGroup(9, b[4], b[7], b[10], b[3], b[8], b[2], b[5], b[11], b[6]);
	}
	if (msx_MusicEnabled != 0) {
		switch (fcn_0064d3f8() % 3) {
		case 0:
			*(int *)0x7747d0 = msx_StartTrack((char *)0x6a3adc, 1);
			break;
		case 1:
			*(int *)0x7747d0 = msx_StartTrack((char *)0x6a3af0, 1);
			break;
		case 2:
			*(int *)0x7747d0 = msx_StartTrack((char *)0x6a3b04, 1);
			break;
		}
	}
	d2_ReleaseOverlaySprite((int)v4);
	d2_StartScreenFade(0, 0, g_1040494, d2_ScreenHeight, (char *)0x67d67c, 0x5a, 10);
	*(unsigned char*) &io_LastKeyScancode = 0;
	msx_SetFadeDuration(2000);
	read_profile = GetPrivateProfileStringA;
	do {
		d2_UpdateRadioGroup(v28);
		if (v29) {
			d2_SetBackdropResource(0x797);
			v29 = 0;
		}
		if (g_14ce8d8 != 0 && d2_CurrentElementId != -1) {
			if (d2_CurrentElementId == b[4]) {
				d2_SetSlotVisibility(v5, 0);
				d2_ClearBackdropResource();
				gm_ResetHistoricalCursors();
				if (d2_StartSinglePlayerChooseCity()) {
					*(int*) &gm_ClientModeFlags |= 1;
					d2_DialogCloseRequested = 1;
				} else {
					goto label_53a8e3;
				}
			} else if (d2_CurrentElementId == b[10]) {
				d2_SetSlotVisibility(v5, 0);
				if (d2_ChooseTutorial()) {
					d2_InitDefaultMenueProfile();
					*(unsigned char*) &gm_PlayerCount = 1;
					*(int*) g_7e1d00 = *(int *)0x6a3ad0;
					*(int *)0x7e1d04 = *(int *)0x6a3ad4;
					*(char *)0x7e1d08 = *(char *)0x6a3ad8;
					*(int*) &gm_ClientModeFlags = 0x89;
					d2_DialogCloseRequested = 1;
				} else {
label_53a8e3:
					d2_SetSlotVisibility(v5, 1);
				}
			} else if (d2_CurrentElementId == b[2]) {
				d2_SetSlotVisibility(v5, 0);
				if (d2_OpenFileSelector(0x24087, 1, (char *)0x6a3ab8, (char *)0x6a3778, (char *)0x6a3ac8, v7)) {
					fcn_0064d41a(v8, (char *)0x67728c, (char *)0x6a3448, v7);
					read_profile((char *)0x6a2278, (char *)0x6a2288, (char *)0x6a2294, profileValueA, 0x60, v8);
					main_LoadCitySelectionScene(profileValueA, 0);
				}
				goto label_53a8e3;
			} else if (d2_CurrentElementId == b[5]) {
				d2_SetSlotVisibility(v5, 0);
				if (d2_OpenFileSelector(0x24087, 1, (char *)0x6a3ab8, (char *)0x6a3778, (char *)0x6a3ac8, v10)) {
					fcn_0064d41a(v11, (char *)0x67728c, (char *)0x6a3448, v10);
					read_profile((char *)0x6a2278, (char *)0x6a2288, (char *)0x6a2294, profileValueB, 0x60, v11);
					main_LoadCitySelectionScene(profileValueB, 1);
				}
				d2_SetSlotVisibility(v5, 1);
			} else if (d2_CurrentElementId == b[7]) {
				d2_SetSlotVisibility(v5, 0);
				if (d2_ShowLoadGameMenu()) {
					d2_DialogCloseRequested = 1;
				}
				d2_SetSlotVisibility(v5, 1);
			} else if (d2_CurrentElementId == b[3]) {
				d2_SetSlotVisibility(v5, 0);
				if (d2_ShowChooseNetworkDialog()) {
					d2_DialogCloseRequested = 1;
				} else {
					d2_SetSlotVisibility(v5, 1);
					*(int*) &gm_ClientModeFlags = 0;
				}
			} else if (d2_CurrentElementId == b[9]) {
				d2_SetSlotVisibility(v5, 0);
				d2_ShowGraphicsOptions();
				d2_SetSlotVisibility(v5, 1);
				v29 = 1;
				if (*(int *)0x77495c != 0) {
					d2_DialogCloseRequested = 1;
				}
			} else if (d2_CurrentElementId == b[1]) {
				d2_SetSlotVisibility(v5, 0);
				d2_ShowSoundOptions();
				d2_SetSlotVisibility(v5, 1);
			} else if (d2_CurrentElementId == b[8]) {
				d2_SetSlotVisibility(v5, 0);
				d2_ShowGameOptions();
				d2_SetSlotVisibility(v5, 1);
			} else if (d2_CurrentElementId == b[6]) {
				g_774954 = 1;
				g_77496c = 1;
				d2_DialogCloseRequested = 1;
			} else if (d2_CurrentElementId == b[0]) {
				d2_ShowAmountDialog();
			} else if (d2_CurrentElementId == b[11]) {
				d2_SetSlotVisibility(v5, 0);
				if (msx_MusicEnabled != 0) {
					msx_SetFadeDuration(1000);
					msx_StartTrack((char *)0x6a3aa4, 1);
				}
				d2_ShowCreditsScreen();
				d2_SetSlotVisibility(v5, 1);
				if (msx_MusicEnabled != 0) {
					msx_SetFadeDuration(1000);
					msx_StartTrackInternal(*(int *)0x7747d0, 1);
				}
			}
		}
		if (*(unsigned char*) &io_LastKeyScancode == 1) {
			g_77496c = 1;
			d2_DialogCloseRequested = 1;
		}
	} while (main_RunFrameLoop((int)(void *)0x53a400, 0x24087) != 0);
	d2_ClearRadioGroup(v28);
	d2_DestroyForm(v15);
	d2_ClearScreen();
	d3_SelectSceneContext(0, 0);
	d3_ClearSceneState();
	d3_SelectSceneContext(1, 0);
	d3_ClearSceneState();
	msx_SetFadeDuration(1000);
	if (*(int *)0x7747d0 != 0) {
		msx_StopTrack(*(int *)0x7747d0, 1);
		d2_SuppressOverlay = 1;
		while (*(char *)(*(int *)0x7747d0 + 0x104)) {
			main_RunFrameLoop(0, main_LoopFlags);
		}
		Sleep(1000);
	}
	msx_SetFadeDuration(5000);
}
