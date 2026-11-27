#include "Develop/Units/Msx/msx.h"

#include <stdio.h>
#include "client_types.h"

int __cdecl d2_LoadForm(int, int, char*);
void __cdecl fcn_00590650(void);
void __cdecl ls_FreeList774a78(void);
float __cdecl eval_ObjektPreis2Credits(int, int);
void __cdecl sb_SetSampleBasePath(char*);
void __cdecl main_PreloadSound(char*);
void __cdecl msx_ApplyAudioSettings(void);
void __cdecl hmt_CreateBinaryFile(void);
void __cdecl gm_LoadHistoricalTable(void);
void __cdecl main_RunFrameLoop(int, int);
void __cdecl evt_RegisterCoreCommands(void);
void __cdecl evt_RegisterSceneCommands(void);
void __cdecl evt_RegisterSoundCommands(void);
void __cdecl gm_ApplyGameSettings(void);

#if defined(REBREW_GOLD)

typedef struct {
	int image;
	int window;
	char pad8[0x2ac - 8];
} Screen;

#include "Develop/Units/d2.v1/gold_window.h"
#include "client_sprites.h"

extern int g_6f2460;
extern int g_6ed9d4;
extern char g_624698[];
extern Screen g_fb1024[];
extern Slot_f8f110 g_f8f110[];
extern short g_fb9070;
extern short g_fb9072;
extern char g_75e760[];
extern int g_6f257c;
extern int g_6f2578;
extern int g_6f2400;
extern char g_75e240[];
extern int g_6f2468;
extern int g_6f246c;
extern char g_75e5a0[];
extern unsigned char g_6f258c;
extern int g_5fb920;
extern int g_5f927c;

void __cdecl fcn_0042cbc0(char*, int);
int __cdecl txt_LoadTextDefinitionList(char*);
void __cdecl fcn_004222b0(char*);
void __cdecl fcn_004b1f30(void);
void __cdecl d2_ResetDisplaySurface(void);
void __cdecl d2_CenterWindowAxes(int, int);
void __cdecl d2_MoveElement(int, short, int);
void __cdecl fcn_00515990(int, char*);
void __cdecl nt_ConnectToHost(int, int);
void __cdecl fcn_004c3480(void);
void __cdecl gm_InitializeGameTables(char*);
void __cdecl fcn_004eddf0(void);
void __cdecl fcn_004fde90(void);
void __cdecl fcn_0042b720(void);
int __cdecl fcn_00425bc0(int, int, int, int, int);
void __cdecl d3snd_InitSoundSources(int);
void __cdecl fcn_00417ec0(int);
int __cdecl sb_LoadSampleBankFromFile(char*, int);
void __cdecl fcn_00423830(int, int, int);
void __cdecl main_InitFrameRateTimer(void);
void __cdecl fcn_0050d460(void);
void __cdecl fcn_0040afb0(void);
void __cdecl d3_InitSnowMipMaps(void);
void __cdecl ai_InitGoodsAndContext(void);
void __cdecl fcn_004eb480(int);
void __cdecl gm_InitCombatWeightTable(void);
void __cdecl d2_FreeWindowSlot(int);
unsigned char* __cdecl d2_CreateOverlaySprite(int, int, int, int, char*, int, int);
void __cdecl evt_InitScriptEngine(void);
void __cdecl fcn_0040d270(void);
void __cdecl fcn_0042b700(void);
void __cdecl main_DrainWindowMessages(void);

/* ADDRESS: GOLD 0x005321c0 */
int __cdecl main_OpenEngine(void)
{
	char ini[0x104];
	char path[0x104];
	int n;
	int screen;
	unsigned char* fade;

	g_6ed9d4 = 1;
	if (g_6f2460 != 0) {
		sprintf(path, "%s%s", g_624698, "die_gilde_add_on_text.def");
		fcn_0042cbc0(path, 0);
	} else {
		sprintf(path, "%s%s", g_624698, "die_gilde_add_on_text.def");
		if (txt_LoadTextDefinitionList(path) == 0) {
			fcn_004222b0("main_OpenEngine(): could not open txt-engine!");
		}
	}
	fcn_004b1f30();
	d2_ResetDisplaySurface();
	screen = d2_LoadForm(0, 0, "Misc\\Loading_main");
	d2_CenterWindowAxes(g_fb1024[screen].image, 3);
	d2_MoveElement(0, g_fb9070 - ((GOLD_GUI_WINDOW*) ((char*) g_f8f110 + 0x10))[g_fb1024[screen].window].height - 0x30,
		((GOLD_GUI_WINDOW*) ((char*) g_f8f110 + 0x10))[g_fb1024[screen].window].id);
	d2_CenterWindowAxes(g_fb1024[screen].window, 1);
	fcn_00515990(0x73, g_75e760);
	nt_ConnectToHost(0, 0);
	fcn_004c3480();
	fcn_00590650();
	sprintf(path, "%sdata\\", g_624698);
	gm_InitializeGameTables(path);
	fcn_004eddf0();
	fcn_004fde90();
	ls_FreeList774a78();
	eval_ObjektPreis2Credits(0x1d5, 100);
	eval_ObjektPreis2Credits(0x1d7, 100);
	eval_ObjektPreis2Credits(0x1d4, 100);
	eval_ObjektPreis2Credits(0x1da, 100);
	eval_ObjektPreis2Credits(0x1d9, 100);
	eval_ObjektPreis2Credits(0x1d6, 100);
	eval_ObjektPreis2Credits(0x1d8, 100);
	if (g_6f257c != 0) {
		fcn_0042b720();
		if (fcn_00425bc0(10000000, 0x30, 2, 0x10, 44100) != 0) {
			g_6f257c = 0;
			g_6f2578 = 0;
		}
		d3snd_InitSoundSources(0x40);
		fcn_00417ec0(0x30);
		sprintf(path, "%ssfx\\", g_624698);
		sb_SetSampleBasePath(path);
		g_6f2400 = sb_LoadSampleBankFromFile("system.sbf", 0);
		sprintf(ini, "%s\\include_sfx.ini", g_75e240);
		main_PreloadSound(ini);
	}
	if (g_6f2578 != 0) {
		fcn_00423830(2, 0x10, 44100);
		sprintf(path, "%smsx\\", g_624698);
		SetTrackPath(path);
	}
	msx_ApplyAudioSettings();
	main_InitFrameRateTimer();
	fcn_0050d460();
	fcn_0040afb0();
	d3_InitSnowMipMaps();
	ai_InitGoodsAndContext();
	fcn_004eb480(g_6f2468);
	if (g_6f246c != 0) {
		hmt_CreateBinaryFile();
	}
	g_6f246c = 0;
	gm_LoadHistoricalTable();
	gm_InitCombatWeightTable();
	d2_FreeWindowSlot(screen);
	fade = d2_CreateOverlaySprite(0, 0, g_fb9072, g_fb9070, "BLACK", 0x5a, 1);
	while ((*fade & 4) == 0) {
		main_RunFrameLoop(0, 0x24087);
	}
	d2_FreeOverlaySprite(fade);
	n = 0x8c;
	/*
	 * The reference zero-fills with the hand-written block-fill prelude no
	 * msvc6 C spelling emits (archived docs/codegen-walls.md 6b).
	 */
	__asm {
		mov edi, offset g_75e5a0
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
	g_6f258c = 1;
	evt_InitScriptEngine();
	evt_RegisterCoreCommands();
	evt_RegisterSceneCommands();
	fcn_0040d270();
	evt_RegisterSoundCommands();
	g_5fb920 = (int) fcn_0042b700;
	g_5f927c = 0x400000;
	gm_ApplyGameSettings();
	main_DrainWindowMessages();
	return 1;
}

#else

typedef struct {
	int image;
	int window;
	char pad8[0x2bc - 8];
} Screen;

#include "Develop/Units/d2.v1/d2_win.h"
#include "Develop/DieGildeAddOn/game/game_data.h"
#include "Develop/Units/Error/error_message.h"

extern int g_774818;
extern char g_6a3550[];
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
void __cdecl txt_ResetHistoryTextBanks(void);
void __cdecl d2_ClearScreen(void);
void __cdecl d2_PositionWindow(int, int);
void __cdecl d2_PositionControl(int, int, int);
void __cdecl io_AppendText(int, char*);
void __cdecl nt_ConnectTcp(int, int);
void __cdecl cm_ResetCommandQueue(void);
void __cdecl gm_InitGameData(char*);
void __cdecl gm_ResetSlot170Table(void);
void __cdecl init_LoadCharacterNames(void);
void __cdecl msx_InitAIL(void);
int __cdecl sb_Init(int, int, int, int, int);
void __cdecl d3snd_InitSources(int);
void __cdecl d3sndw_Init(int);
int __cdecl sb_LoadSampleBank(char*, int);
void __cdecl msx_InitDrivers(int, int, int);
void __cdecl main_InitFrameProfile(void);
void __cdecl d3_ResetSceneContextIndices(void);
void __cdecl ch_InitActionQueue(void);
void __cdecl d3_InitRenderVertexBuffers(void);
void __cdecl ai_InitContextAndGoodsLists(void);
void __cdecl ahm_ReloadAlchemyPrototypes(int);
void __cdecl cut_InitCombatActionWeights(void);
void __cdecl d2_DestroyForm(int);
unsigned char* __cdecl d2_StartScreenFade(int, int, int, int, char*, int, int);
void __cdecl d2_ReleaseOverlaySprite(unsigned char*);
void __cdecl evt_AllocScriptEngineBuffers(void);
void __cdecl ch_RegisterScriptCommands(void);
void __cdecl evt_GetLoadAndRunGfxScriptFunc(void);
int __cdecl main_PumpWindowMessages(void);

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

#endif
