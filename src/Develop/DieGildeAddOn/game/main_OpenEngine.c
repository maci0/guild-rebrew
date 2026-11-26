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
void __cdecl fcn_004b2070(void);
void __cdecl d2_ClearScreen(void);
int __cdecl fcn_00470820(int, int, char*);
void __cdecl d2_PositionWindow(int, int);
void __cdecl fcn_00469c40(int, int, int);
void __cdecl io_AppendText(int, char*);
void __cdecl nt_ConnectTcp(int, int);
void __cdecl cm_ResetCommandQueue(void);
void __cdecl fcn_00590650(void);
void __cdecl fcn_00501040(char*);
void __cdecl fcn_004efc50(void);
void __cdecl fcn_00500900(void);
void __cdecl ls_FreeList774a78(void);
float __cdecl eval_ObjektPreis2Credits(int, int);
void __cdecl msx_InitAIL(void);
int __cdecl sb_Init(int, int, int, int, int);
void __cdecl d3snd_InitSources(int);
void __cdecl d3sndw_Init(int);
void __cdecl fcn_004226b0(char*);
int __cdecl sb_LoadSampleBank(char*, int);
void __cdecl main_PreloadSound(char*);
void __cdecl msx_InitDrivers(int, int, int);
void __cdecl msx_ApplyAudioSettings(void);
void __cdecl fcn_00525eb0(void);
void __cdecl fcn_00510900(void);
void __cdecl ch_InitActionQueue(void);
void __cdecl fcn_004186c0(void);
void __cdecl fcn_0047ce90(void);
void __cdecl fcn_004ed200(int);
void __cdecl fcn_004ac560(void);
void __cdecl fcn_004acbb0(void);
void __cdecl fcn_004d3800(void);
void __cdecl fcn_00471e30(int);
unsigned char* __cdecl fcn_004730c0(int, int, int, int, char*, int, int);
void __cdecl main_RunFrameLoop(int, int);
void __cdecl fcn_00473150(unsigned char*);
void __cdecl fcn_00429920(void);
void __cdecl evt_RegisterCoreCommands(void);
void __cdecl fcn_00410870(void);
void __cdecl ch_RegisterScriptCommands(void);
void __cdecl evt_RegisterSoundCommands(void);
void __cdecl fcn_0042a020(void);
void __cdecl fcn_005e2510(void);
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
extern int __cdecl fcn_004fdec0(char* name);
extern void __cdecl fcn_004b20d0(unsigned char v);
extern void __cdecl main_LoadMessageFilterMask(char* ini);
extern int __cdecl main_CheckExistingInstance(void** handle);
extern int __cdecl main_CreateWindow(HINSTANCE inst, int unused, int windowed);
extern int __cdecl main_InitRuntime(void);
extern void __cdecl main_PlayIntroMovies(void);
extern int __cdecl fcn_00538850(int topmost);
extern int __cdecl main_OpenEngine(void);
extern void __cdecl fcn_00538220(void);
extern void __cdecl fcn_00538160(void);
extern int __cdecl main_PumpWindowMessages(void);
extern void __cdecl main_Menue(void);
extern void __cdecl main_SetLanguageByName(char* language);
extern Rec6* __cdecl fcn_00506d50(Rec6* dst, int idx);
extern void __cdecl fcn_005438c0(int v);
extern void __cdecl fcn_005386c0(void* p);

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
	fcn_004b2070();
	d2_ClearScreen();
	screen = fcn_00470820(0, 0, "Misc\\Loading_main");
	d2_PositionWindow(((Screen*)g_1038144)[screen].image, 3);
	fcn_00469c40(0, d2_ScreenHeight - ((D2_WIN*)g_1015f40)[((Screen*)g_1038144)[screen].window].height - 0x30,
		((D2_WIN*)g_1015f40)[((Screen*)g_1038144)[screen].window].slot);
	d2_PositionWindow(((Screen*)g_1038144)[screen].window, 1);
	io_AppendText(0x73, g_7e25a0);
	nt_ConnectTcp(0, 0);
	cm_ResetCommandQueue();
	fcn_00590650();
	sprintf(path, "%sdata\\", g_6a3550);
	fcn_00501040(path);
	fcn_004efc50();
	fcn_00500900();
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
		fcn_004226b0(path);
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
	fcn_00525eb0();
	fcn_00510900();
	ch_InitActionQueue();
	fcn_004186c0();
	fcn_0047ce90();
	fcn_004ed200(g_774820);
	if (g_774824 != 0) {
		fcn_004ac560();
	}
	g_774824 = 0;
	fcn_004acbb0();
	fcn_004d3800();
	fcn_00471e30(screen);
	fade = fcn_004730c0(0, 0, g_1040494, d2_ScreenHeight, "BLACK", 0x5a, 1);
	while ((*fade & 4) == 0) {
		main_RunFrameLoop(0, 0x24087);
	}
	fcn_00473150(fade);
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
	fcn_00429920();
	evt_RegisterCoreCommands();
	fcn_00410870();
	ch_RegisterScriptCommands();
	evt_RegisterSoundCommands();
	g_67a590 = (int) fcn_0042a020;
	(*(int*)&g_67a0d8) = 0x400000;
	fcn_005e2510();
	main_PumpWindowMessages();
	return 1;
}
