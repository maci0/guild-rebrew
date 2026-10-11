#include "Develop/Units/Msx/msx.h"

// FUNCTION: GOLDTL 0x00538d00

#include <stdio.h>

// SIZE 0x2bc
typedef struct {
	int image;
	int window;
	char pad8[0x2bc - 8];
} Screen;

// SIZE 0x3cc
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

void __cdecl fcn_0042bf20(char*, int);
int __cdecl fcn_0042bd20(char*);
void __cdecl fcn_0041d9e0(char*);
void __cdecl fcn_004b2070(void);
void __cdecl fcn_0046b4f0(void);
int __cdecl fcn_00470820(int, int, char*);
void __cdecl fcn_00471c00(int, int);
void __cdecl fcn_00469c40(int, int, int);
void __cdecl fcn_00519190(int, char*);
void __cdecl fcn_00420db0(int, int);
void __cdecl fcn_004c3d50(void);
void __cdecl fcn_00590650(void);
void __cdecl fcn_00501040(char*);
void __cdecl fcn_004efc50(void);
void __cdecl fcn_00500900(void);
void __cdecl fcn_005b1ef0(void);
float __cdecl fcn_0050b980(int, int);
void __cdecl fcn_0042a080(void);
int __cdecl fcn_00421fe0(int, int, int, int, int);
void __cdecl fcn_00418bc0(int);
void __cdecl fcn_00419480(int);
void __cdecl fcn_004226b0(char*);
int __cdecl fcn_00422dc0(char*, int);
void __cdecl fcn_0053f7b0(char*);
void __cdecl fcn_0041fad0(int, int, int);
void __cdecl fcn_005e2590(void);
void __cdecl fcn_00525eb0(void);
void __cdecl fcn_00510900(void);
void __cdecl fcn_0040bde0(void);
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
void __cdecl fcn_0040e1a0(void);
void __cdecl fcn_00411130(void);
void __cdecl fcn_0042a020(void);
void __cdecl fcn_005e2510(void);
void __cdecl fcn_005356e0(void);

int __cdecl fcn_00538d00(void)
{
	char ini[0x104];
	char path[0x104];
	int n;
	int screen;
	unsigned char* fade;

	g_7725c8 = 1;
	if (g_774818 != 0) {
		sprintf(path, "%s%s", g_6a3550, "die_gilde_add_on_text.def");
		fcn_0042bf20(path, 0);
	} else {
		sprintf(path, "%s%s", g_6a3550, "die_gilde_add_on_text.def");
		if (fcn_0042bd20(path) == 0) {
			fcn_0041d9e0("main_OpenEngine(): could not open txt-engine!");
		}
	}
	fcn_004b2070();
	fcn_0046b4f0();
	screen = fcn_00470820(0, 0, "Misc\\Loading_main");
	fcn_00471c00(((Screen*)g_1038144)[screen].image, 3);
	fcn_00469c40(0, g_1040490 - ((Window*)g_1015f40)[((Screen*)g_1038144)[screen].window].height - 0x30,
		((Window*)g_1015f40)[((Screen*)g_1038144)[screen].window].id);
	fcn_00471c00(((Screen*)g_1038144)[screen].window, 1);
	fcn_00519190(0x73, g_7e25a0);
	fcn_00420db0(0, 0);
	fcn_004c3d50();
	fcn_00590650();
	sprintf(path, "%sdata\\", g_6a3550);
	fcn_00501040(path);
	fcn_004efc50();
	fcn_00500900();
	fcn_005b1ef0();
	fcn_0050b980(0x1d5, 100);
	fcn_0050b980(0x1d7, 100);
	fcn_0050b980(0x1d4, 100);
	fcn_0050b980(0x1da, 100);
	fcn_0050b980(0x1d9, 100);
	fcn_0050b980(0x1d6, 100);
	fcn_0050b980(0x1d8, 100);
	if (g_774934 != 0) {
		fcn_0042a080();
		if (fcn_00421fe0(10000000, 0x30, 2, 0x10, 44100) != 0) {
			g_774934 = 0;
			g_774930 = 0;
		}
		fcn_00418bc0(0x40);
		fcn_00419480(0x30);
		sprintf(path, "%ssfx\\", g_6a3550);
		fcn_004226b0(path);
		(*(int*)&g_7747b8) = fcn_00422dc0("system.sbf", 0);
		sprintf(ini, "%s\\include_sfx.ini", g_7e2080);
		fcn_0053f7b0(ini);
	}
	if (g_774930 != 0) {
		fcn_0041fad0(2, 0x10, 44100);
		sprintf(path, "%smsx\\", g_6a3550);
		SetTrackPath(path);
	}
	fcn_005e2590();
	fcn_00525eb0();
	fcn_00510900();
	fcn_0040bde0();
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
	fcn_0040e1a0();
	fcn_00411130();
	g_67a590 = (int) fcn_0042a020;
	(*(int*)&g_67a0d8) = 0x400000;
	fcn_005e2510();
	fcn_005356e0();
	return 1;
}
