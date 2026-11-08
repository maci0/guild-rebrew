#include "Develop/Units/Msx/msx.h"

#include <stdio.h>

typedef struct {
	int image;
	int window;
	char pad8[0x2bc - 8];
} Screen;

typedef struct {
	char pad0[0x10];
	int height;
	char pad14[0x27c - 0x14];
	int id;
	char pad280[0x3cc - 0x280];
} Window;

extern int g_774818;
extern int g_7725c8;
extern char g_6a3550[];
#include "client_types.h"
extern Page_1038144 g_1038144[];
extern Win_1015f40 g_1015f40[0x60];
extern int g_1040490;
extern int g_1040494;
extern char g_7e25a0[];
extern int g_774934;
extern int g_774930;
extern char* g_7747b8;
extern char g_7e2080[];
extern int g_774820;
extern int g_774824;
extern char g_7e23e0[];
extern char g_774944;
extern int g_67a590;
extern unsigned int g_67a0d8;

void __cdecl txt_OpenText(char*, int);
int __cdecl fcn_0042bd20(char*);
#include "Develop/Units/Error/error_message.h"
void __cdecl fcn_004b2070(void);
void __cdecl fcn_0046b4f0(void);
int __cdecl fcn_00470820(int, int, char*);
void __cdecl fcn_00471c00(int, int);
void __cdecl fcn_00469c40(int, int, int);
void __cdecl io_AppendText(int, char*);
void __cdecl fcn_00420db0(int, int);
void __cdecl fcn_004c3d50(void);
void __cdecl fcn_00590650(void);
void __cdecl fcn_00501040(char*);
void __cdecl fcn_004efc50(void);
void __cdecl fcn_00500900(void);
void __cdecl fcn_005b1ef0(void);
float __cdecl eval_ObjektPreis2Credits(int, int);
void __cdecl msx_InitAIL(void);
int __cdecl sb_Init(int, int, int, int, int);
void __cdecl fcn_00418bc0(int);
void __cdecl fcn_00419480(int);
void __cdecl fcn_004226b0(char*);
int __cdecl sb_LoadSampleBank(char*, int);
void __cdecl main_PreloadSound(char*);
void __cdecl fcn_0041fad0(int, int, int);
void __cdecl fcn_005e2590(void);
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
void __cdecl fcn_005373e0(int, int);
void __cdecl fcn_00473150(unsigned char*);
void __cdecl fcn_00429920(void);
void __cdecl fcn_0040c7c0(void);
void __cdecl fcn_00410870(void);
void __cdecl ch_RegisterScriptCommands(void);
void __cdecl fcn_00411130(void);
void __cdecl fcn_0042a020(void);
void __cdecl fcn_005e2510(void);
int __cdecl fcn_005356e0(void);
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
extern int __cdecl fcn_0064eeec(char* s);
extern int __cdecl fcn_0065f220(char* a, char* b);
extern int __cdecl gm_RandomMod(int n);
extern int __cdecl fcn_004fdec0(char* name);
extern void __cdecl fcn_004b20d0(unsigned char v);
extern void __cdecl fcn_0057ddc0(char* ini);
extern int __cdecl fcn_00538680(void** handle);
extern int __cdecl fcn_00539090(HINSTANCE inst, int unused, int windowed);
extern int __cdecl fcn_00538710(void);
extern void __cdecl fcn_00544750(void);
extern int __cdecl fcn_00538850(int topmost);
extern int __cdecl main_OpenEngine(void);
extern void __cdecl fcn_00538220(void);
extern void __cdecl fcn_00538160(void);
extern int __cdecl fcn_005356e0(void);
extern void __cdecl main_Menue(void);
extern void __cdecl fcn_0051dfe0(char* language);
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

	g_7725c8 = 1;
	if (g_774818 != 0) {
		sprintf(path, "%s%s", g_6a3550, "die_gilde_add_on_text.def");
		txt_OpenText(path, 0);
	} else {
		sprintf(path, "%s%s", g_6a3550, "die_gilde_add_on_text.def");
		if (fcn_0042bd20(path) == 0) {
			ReportClientMessage("main_OpenEngine(): could not open txt-engine!");
		}
	}
	fcn_004b2070();
	fcn_0046b4f0();
	screen = fcn_00470820(0, 0, "Misc\\Loading_main");
	fcn_00471c00(((Screen*)g_1038144)[screen].image, 3);
	fcn_00469c40(0, g_1040490 - ((Window*)g_1015f40)[((Screen*)g_1038144)[screen].window].height - 0x30,
		((Window*)g_1015f40)[((Screen*)g_1038144)[screen].window].id);
	fcn_00471c00(((Screen*)g_1038144)[screen].window, 1);
	io_AppendText(0x73, g_7e25a0);
	fcn_00420db0(0, 0);
	fcn_004c3d50();
	fcn_00590650();
	sprintf(path, "%sdata\\", g_6a3550);
	fcn_00501040(path);
	fcn_004efc50();
	fcn_00500900();
	fcn_005b1ef0();
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
			g_774930 = 0;
		}
		fcn_00418bc0(0x40);
		fcn_00419480(0x30);
		sprintf(path, "%ssfx\\", g_6a3550);
		fcn_004226b0(path);
		(*(int*)&g_7747b8) = sb_LoadSampleBank("system.sbf", 0);
		sprintf(ini, "%s\\include_sfx.ini", g_7e2080);
		main_PreloadSound(ini);
	}
	if (g_774930 != 0) {
		fcn_0041fad0(2, 0x10, 44100);
		sprintf(path, "%smsx\\", g_6a3550);
		SetTrackPath(path);
	}
	fcn_005e2590();
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
	fade = fcn_004730c0(0, 0, g_1040494, g_1040490, "BLACK", 0x5a, 1);
	while ((*fade & 4) == 0) {
		fcn_005373e0(0, 0x24087);
	}
	fcn_00473150(fade);
	n = 0x8c;
	/*
	 * The reference zero-fills with the hand-written block-fill prelude no
	 * msvc6 C spelling emits (docs/codegen-walls.md 6b).
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
	fcn_0040c7c0();
	fcn_00410870();
	ch_RegisterScriptCommands();
	fcn_00411130();
	g_67a590 = (int) fcn_0042a020;
	(*(int*)&g_67a0d8) = 0x400000;
	fcn_005e2510();
	fcn_005356e0();
	return 1;
}
