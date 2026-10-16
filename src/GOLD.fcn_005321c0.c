#include "Develop/Units/Msx/msx.h"



#include <stdio.h>

// SIZE 0x2ac
typedef struct {
	int image;
	int window;
	char pad8[0x2ac - 8];
} Screen;

// SIZE 0x3c4
typedef struct {
	char pad0[0x1a];
	short height;
	char pad1c[0x27c - 0x1c];
	int id;
	char pad280[0x3c4 - 0x280];
} Window;

extern int g_6f2460;
extern int g_6ed9d4;
extern char g_624698[];
extern Screen g_fb1024[];
#include "client_types.h"
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
int __cdecl fcn_0042c9c0(char*);
void __cdecl fcn_004222b0(char*);
void __cdecl fcn_004b1f30(void);
void __cdecl fcn_0046e980(void);
int __cdecl fcn_004741e0(int, int, char*);
void __cdecl fcn_004756a0(int, int);
void __cdecl fcn_0046cd90(int, short, int);
void __cdecl fcn_00515990(int, char*);
void __cdecl fcn_00424990(int, int);
void __cdecl fcn_004c3480(void);
void __cdecl fcn_005880b0(void);
void __cdecl fcn_004fe570(char*);
void __cdecl fcn_004eddf0(void);
void __cdecl fcn_004fde90(void);
void __cdecl fcn_005a8a70(void);
float __cdecl fcn_00508820(int, int);
void __cdecl fcn_0042b720(void);
int __cdecl fcn_00425bc0(int, int, int, int, int);
void __cdecl fcn_00417650(int);
void __cdecl fcn_00417ec0(int);
void __cdecl fcn_004226b0(char*);
int __cdecl fcn_00426950(char*, int);
void __cdecl fcn_00537ed0(char*);
void __cdecl fcn_00423830(int, int, int);
void __cdecl fcn_005d6060(void);
void __cdecl fcn_00520f10(void);
void __cdecl fcn_0050d460(void);
void __cdecl fcn_0040afb0(void);
void __cdecl fcn_00416980(void);
void __cdecl fcn_0047d9d0(void);
void __cdecl fcn_004eb480(int);
void __cdecl fcn_004ac440(void);
void __cdecl fcn_004aca90(void);
void __cdecl fcn_004d27a0(void);
void __cdecl fcn_004758e0(int);
unsigned char* __cdecl fcn_004767c0(int, int, int, int, char*, int, int);
void __cdecl fcn_005309d0(int, int);
void __cdecl fcn_00476850(unsigned char*);
void __cdecl fcn_0042b050(void);
void __cdecl fcn_0040b8a0(void);
void __cdecl fcn_0040f960(void);
void __cdecl fcn_0040d270(void);
void __cdecl fcn_00410220(void);
void __cdecl fcn_0042b700(void);
void __cdecl fcn_005d5fe0(void);
void __cdecl fcn_0052fbb0(void);

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
		if (fcn_0042c9c0(path) == 0) {
			fcn_004222b0("main_OpenEngine(): could not open txt-engine!");
		}
	}
	fcn_004b1f30();
	fcn_0046e980();
	screen = fcn_004741e0(0, 0, "Misc\\Loading_main");
	fcn_004756a0(g_fb1024[screen].image, 3);
	fcn_0046cd90(0, g_fb9070 - ((Window*)g_f8f110)[g_fb1024[screen].window].height - 0x30,
		((Window*)g_f8f110)[g_fb1024[screen].window].id);
	fcn_004756a0(g_fb1024[screen].window, 1);
	fcn_00515990(0x73, g_75e760);
	fcn_00424990(0, 0);
	fcn_004c3480();
	fcn_005880b0();
	sprintf(path, "%sdata\\", g_624698);
	fcn_004fe570(path);
	fcn_004eddf0();
	fcn_004fde90();
	fcn_005a8a70();
	fcn_00508820(0x1d5, 100);
	fcn_00508820(0x1d7, 100);
	fcn_00508820(0x1d4, 100);
	fcn_00508820(0x1da, 100);
	fcn_00508820(0x1d9, 100);
	fcn_00508820(0x1d6, 100);
	fcn_00508820(0x1d8, 100);
	if (g_6f257c != 0) {
		fcn_0042b720();
		if (fcn_00425bc0(10000000, 0x30, 2, 0x10, 44100) != 0) {
			g_6f257c = 0;
			g_6f2578 = 0;
		}
		fcn_00417650(0x40);
		fcn_00417ec0(0x30);
		sprintf(path, "%ssfx\\", g_624698);
		fcn_004226b0(path);
		g_6f2400 = fcn_00426950("system.sbf", 0);
		sprintf(ini, "%s\\include_sfx.ini", g_75e240);
		fcn_00537ed0(ini);
	}
	if (g_6f2578 != 0) {
		fcn_00423830(2, 0x10, 44100);
		sprintf(path, "%smsx\\", g_624698);
		SetTrackPath(path);
	}
	fcn_005d6060();
	fcn_00520f10();
	fcn_0050d460();
	fcn_0040afb0();
	fcn_00416980();
	fcn_0047d9d0();
	fcn_004eb480(g_6f2468);
	if (g_6f246c != 0) {
		fcn_004ac440();
	}
	g_6f246c = 0;
	fcn_004aca90();
	fcn_004d27a0();
	fcn_004758e0(screen);
	fade = fcn_004767c0(0, 0, g_fb9072, g_fb9070, "BLACK", 0x5a, 1);
	while ((*fade & 4) == 0) {
		fcn_005309d0(0, 0x24087);
	}
	fcn_00476850(fade);
	n = 0x8c;
	/*
	 * The reference zero-fills with the hand-written block-fill prelude no
	 * msvc6 C spelling emits (docs/codegen-walls.md 6b).
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
	fcn_0042b050();
	fcn_0040b8a0();
	fcn_0040f960();
	fcn_0040d270();
	fcn_00410220();
	g_5fb920 = (int) fcn_0042b700;
	g_5f927c = 0x400000;
	fcn_005d5fe0();
	fcn_0052fbb0();
	return 1;
}
