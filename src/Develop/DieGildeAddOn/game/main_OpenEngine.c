#include "Develop/Units/Msx/msx.h"

#include <stdio.h>

typedef struct {
	int image;
	int window;
	char pad8[0x2bc - 8];
} Screen;

#include "Develop/Units/d2.v1/d2_win.h"








extern int g_774818;
#include "Develop/DieGildeAddOn/game/game_data.h"
extern char g_6a3550[];
#include "client_types.h"
extern Page_1038144 g_1038144[];
extern Win_1015f40 g_1015f40[0x60];
extern int d2_ScreenHeight;
extern int g_1040494;
extern char g_7e25a0[];
extern char* g_7747b8;
extern char g_7e2080[];
extern int g_774820;
extern int g_774824;
extern char g_7e23e0[];
extern char g_774944;
extern int g_67a590;
extern unsigned int g_67a0d8;

void __cdecl txt_OpenText(char*, int);
int __cdecl txt_LoadTextFileDefinition(char*);
#include "Develop/Units/Error/error_message.h"
void __cdecl txt_ResetHistoryTextBanks(void);
void __cdecl d2_ClearScreen(void);
int __cdecl d2_LoadForm(int, int, char*);
void __cdecl d2_PositionWindow(int, int);
void __cdecl d2_PositionControl(int, int, int);
void __cdecl io_AppendText(int, char*);
void __cdecl nt_ConnectTcp(int, int);
void __cdecl cm_ResetCommandQueue(void);
void __cdecl fcn_00590650(void);
void __cdecl gm_InitGameData(char*);
void __cdecl gm_ResetSlot170Table(void);
void __cdecl init_LoadCharacterNames(void);
void __cdecl ls_FreeList774a78(void);
float __cdecl eval_ObjektPreis2Credits(int, int);
void __cdecl msx_InitAIL(void);
int __cdecl sb_Init(int, int, int, int, int);
void __cdecl d3snd_InitSources(int);
void __cdecl d3sndw_Init(int);
void __cdecl sb_SetSampleBasePath(char*);
int __cdecl sb_LoadSampleBank(char*, int);
void __cdecl main_PreloadSound(char*);
void __cdecl msx_InitDrivers(int, int, int);
void __cdecl msx_ApplyAudioSettings(void);
void __cdecl main_InitFrameProfile(void);
void __cdecl d3_ResetSceneContextIndices(void);
void __cdecl ch_InitActionQueue(void);
void __cdecl d3_InitRenderVertexBuffers(void);
void __cdecl ai_InitContextAndGoodsLists(void);
void __cdecl ahm_ReloadAlchemyPrototypes(int);
void __cdecl hmt_CreateBinaryFile(void);
void __cdecl gm_LoadHistoricalTable(void);
void __cdecl cut_InitCombatActionWeights(void);
void __cdecl d2_DestroyForm(int);
unsigned char* __cdecl d2_StartScreenFade(int, int, int, int, char*, int, int);
void __cdecl main_RunFrameLoop(int, int);
void __cdecl d2_ReleaseOverlaySprite(unsigned char*);
void __cdecl evt_AllocScriptEngineBuffers(void);
void __cdecl evt_RegisterCoreCommands(void);
void __cdecl evt_RegisterSceneCommands(void);
void __cdecl ch_RegisterScriptCommands(void);
void __cdecl evt_RegisterSoundCommands(void);
void __cdecl evt_GetLoadAndRunGfxScriptFunc(void);
void __cdecl gm_ApplyGameSettings(void);
int __cdecl main_PumpWindowMessages(void);
#include <windows.h>
#include <stdlib.h>
#include <string.h>

typedef struct rec6 {
	short w[3];
} Rec6;

typedef struct str9 {
	char b[9];
} Str9;

typedef struct str8 {
	char b[8];
} Str8;

typedef struct str7 {
	char b[7];
} Str7;

extern char* __cdecl fcn_0064d1a0(char* s, int c);
extern char* __cdecl fcn_0064e790(char* s, int c);
extern int __cdecl atoi(char* s);
extern int __cdecl fcn_0065f220(char* a, char* b);
extern int __cdecl gm_RandomMod(int n);
extern int __cdecl gm_FindHeadIconIndex(char* name);
extern void __cdecl hst_SetHistoryScrollModeFlag(unsigned char v);
extern void __cdecl main_LoadMessageFilterMask(char* ini);
extern int __cdecl main_CheckExistingInstance(void** handle);
extern int __cdecl main_CreateWindow(HINSTANCE inst, int unused, int windowed);
extern int __cdecl main_InitRuntime(void);
extern void __cdecl main_PlayIntroMovies(void);
extern int __cdecl main_CreateGameWindowAndDevice(int topmost);
extern int __cdecl main_OpenEngine(void);
extern void __cdecl main_ShutdownEngine(void);
extern void __cdecl main_ShutdownSubsystems(void);
extern int __cdecl main_PumpWindowMessages(void);
extern void __cdecl main_Menue(void);
extern void __cdecl main_SetLanguageByName(char* language);
extern Rec6* __cdecl gm_GetStatRecord(Rec6* dst, int idx);
extern void __cdecl main_RunGameLoop(int v);
extern void __cdecl main_SetScreensaverActive(void* p);

/* ADDRESS: GOLDTL 0x00538d00 */
int __cdecl main_OpenEngine(void)
{
	char ini[0x104];
	char path[0x104];
	int n;
	int screen;
	unsigned char* fade;

	d2_SuppressOverlay = 1;
	if (g_774818 != 0) {
		sprintf(path, "%s%s", g_6a3550, "die_gilde_add_on_text.def");
		txt_OpenText(path, 0);
	} else {
		sprintf(path, "%s%s", g_6a3550, "die_gilde_add_on_text.def");
		if (txt_LoadTextFileDefinition(path) == 0) {
			ReportClientMessage("main_OpenEngine(): could not open txt-engine!");
		}
	}
	txt_ResetHistoryTextBanks();
	d2_ClearScreen();
	screen = d2_LoadForm(0, 0, "Misc\\Loading_main");
	d2_PositionWindow(((Screen*)g_1038144)[screen].image, 3);
	d2_PositionControl(0, d2_ScreenHeight - ((D2_WIN*)g_1015f40)[((Screen*)g_1038144)[screen].window].height - 0x30,
		((D2_WIN*)g_1015f40)[((Screen*)g_1038144)[screen].window].slot);
	d2_PositionWindow(((Screen*)g_1038144)[screen].window, 1);
	io_AppendText(0x73, g_7e25a0);
	nt_ConnectTcp(0, 0);
	cm_ResetCommandQueue();
	fcn_00590650();
	sprintf(path, "%sdata\\", g_6a3550);
	gm_InitGameData(path);
	gm_ResetSlot170Table();
	init_LoadCharacterNames();
	ls_FreeList774a78();
	eval_ObjektPreis2Credits(0x1d5, 100);
	eval_ObjektPreis2Credits(0x1d7, 100);
	eval_ObjektPreis2Credits(0x1d4, 100);
	eval_ObjektPreis2Credits(0x1da, 100);
	eval_ObjektPreis2Credits(0x1d9, 100);
	eval_ObjektPreis2Credits(0x1d6, 100);
	eval_ObjektPreis2Credits(0x1d8, 100);
	if (g_774934 != 0) {
		msx_InitAIL();
		if (sb_Init(10000000, 0x30, 2, 0x10, 44100) != 0) {
			g_774934 = 0;
			msx_MusicEnabled = 0;
		}
		d3snd_InitSources(0x40);
		d3sndw_Init(0x30);
		sprintf(path, "%ssfx\\", g_6a3550);
		sb_SetSampleBasePath(path);
		(*(int*)&g_7747b8) = sb_LoadSampleBank("system.sbf", 0);
		sprintf(ini, "%s\\include_sfx.ini", g_7e2080);
		main_PreloadSound(ini);
	}
	if (msx_MusicEnabled != 0) {
		msx_InitDrivers(2, 0x10, 44100);
		sprintf(path, "%smsx\\", g_6a3550);
		SetTrackPath(path);
	}
	msx_ApplyAudioSettings();
	main_InitFrameProfile();
	d3_ResetSceneContextIndices();
	ch_InitActionQueue();
	d3_InitRenderVertexBuffers();
	ai_InitContextAndGoodsLists();
	ahm_ReloadAlchemyPrototypes(g_774820);
	if (g_774824 != 0) {
		hmt_CreateBinaryFile();
	}
	g_774824 = 0;
	gm_LoadHistoricalTable();
	cut_InitCombatActionWeights();
	d2_DestroyForm(screen);
	fade = d2_StartScreenFade(0, 0, g_1040494, d2_ScreenHeight, "BLACK", 0x5a, 1);
	while ((*fade & 4) == 0) {
		main_RunFrameLoop(0, 0x24087);
	}
	d2_ReleaseOverlaySprite(fade);
	n = 0x8c;
	/*
	 * The reference zero-fills with the hand-written block-fill prelude no
	 * msvc6 C spelling emits (archived docs/codegen-walls.md 6b).
	 */
	__asm {
		mov edi, offset g_7e23e0
		mov ebx, n
		xor eax, eax
		lea ecx, [edi+edi*2]
		and ecx, 3
		sub ebx, ecx
		jle short L1
		rep stosb
		mov ecx, ebx
		and ebx, 3
		shr ecx, 2
		rep stosd
	L1:
		add ecx, ebx
		rep stosb
	}
	(*(unsigned char*)&g_774944) = 1;
	evt_AllocScriptEngineBuffers();
	evt_RegisterCoreCommands();
	evt_RegisterSceneCommands();
	ch_RegisterScriptCommands();
	evt_RegisterSoundCommands();
	g_67a590 = (int) evt_GetLoadAndRunGfxScriptFunc;
	(*(int*)&g_67a0d8) = 0x400000;
	gm_ApplyGameSettings();
	main_PumpWindowMessages();
	return 1;
}
