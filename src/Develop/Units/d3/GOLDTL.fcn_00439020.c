double __cdecl atan2(double, double);
#pragma intrinsic(atan2)

typedef struct
{
	unsigned int w;
	unsigned int h;
	char pad8[0x18 - 8];
	int a18;
	int a1c;
	char pad20[0x28 - 0x20];
	unsigned char b28;
	char pad29[0x30 - 0x29];
	unsigned char b30;
	char pad31[3];
	unsigned char b34;
	char pad35[3];
	int bpp;
	float x;
	float y;
	float cw;
	float ch;
	int f4c;
	int f50;
	int f54;
} fcn_00439020_Cfg;
// SIZE 0x58

extern fcn_00439020_Cfg g_10529e0;
extern char g_6b8004;
extern char g_1042fc4;
extern char g_1042fc5;
extern int g_1042a08;
extern unsigned char g_1042557;
extern unsigned char g_1043277;
extern int g_1042fc0;
extern char g_1043060;
extern char g_1042340[];
extern unsigned int g_14ce7e0;
extern char* g_1043254;
extern char* g_1042538;
#include "Develop/Units/d3/d3_camera.h"
extern char* g_1042c38;
extern char g_1042d00[];
extern int g_1042ef8;
extern int g_1042c3c;
extern char* g_1042efc;
extern char g_1042a40[];
extern int g_1052ba0;
extern int g_1042324;
extern char* g_1042320;
extern char g_1052a40[];
extern char* g_1052ba4;
extern char g_10421c0[];
extern int g_1041d08;
extern int g_6b8008;
extern int g_67a374;
extern int g_6b805c;
extern unsigned char g_6b7ff8;
extern char g_6b8018;
extern int g_6b8010;
extern float g_1052bbc;
extern float g_10432a4;
extern float g_1052bc4;
extern float g_1052bb4;
extern float g_1042584;
extern float g_1052bb8;
extern char g_10432c0[];

void __cdecl fcn_00439e70(char* o);
void __cdecl fcn_00450a30(int nlist, int nactive);
void __cdecl fcn_0045bed0(unsigned int n, int a2);
void __cdecl fcn_00436aa0(int* a);
void __cdecl fcn_00436f70(char on);
void __cdecl fcn_0043bc00(char a, char b);
void __cdecl fcn_00456750(int, int, int, int, int, int, int);
void __cdecl InitColorTable(void);
void __cdecl fcn_00438da0(float, float, float, float, int, int, int, unsigned int, unsigned int);
void __cdecl fcn_00452280(void);

/* ADDRESS: GOLDTL 0x00439020 */
char __cdecl fcn_00439020(fcn_00439020_Cfg* cfg)
{
	unsigned int n;

	g_6b8004 = 0;
	{
		int len;

		len = 0x58;
		__asm {
			mov edi, offset g_10529e0
			mov esi, cfg
			mov ebx, len
			lea ecx, [edi+edi*2]
			and ecx, 3
			sub ebx, ecx
			jle short L1
			rep movsb
			mov ecx, ebx
			and ebx, 3
			shr ecx, 2
			rep movsd
		L1:
			add ecx, ebx
			rep movsb
		}
	}
	if (g_10529e0.cw + g_10529e0.x > g_10529e0.w)
		g_10529e0.x = g_10529e0.w - g_10529e0.cw;
	if (g_10529e0.ch + g_10529e0.y > g_10529e0.h)
		g_10529e0.y = g_10529e0.h - g_10529e0.ch;
	g_1042fc4 = 0;
	g_1042fc5 = 0;
	g_1042a08 = 0;
	g_1042fc0 = 6;
	g_1042557 |= 2;
	g_1043277 |= 2;
	fcn_00439e70(((char*)&g_1043060));
	fcn_00439e70(g_1042340);
	n = g_14ce7e0;
	g_1043254 = g_1042340;
	g_1042538 = ((char*)&g_1043060);
	g_6b8014 = 0;
	g_1042c38 = g_1042d00;
	g_1042ef8 = 0;
	g_1042c3c = 0;
	g_1042efc = g_1042a40;
	g_1052ba0 = 0;
	g_1042324 = 0;
	g_1042320 = g_1052a40;
	g_1052ba4 = g_10421c0;
	g_1041d08 = 0;
	if (n > 8)
		n = 8;
	fcn_00450a30(0x200, n);
	g_6b8008 = 0;
	fcn_0045bed0(g_10529e0.a18, g_10529e0.a1c);
	fcn_00436aa0(&g_67a374);
	fcn_00436f70(1);
	g_6b805c = 0;
	g_6b7ff8 = g_10529e0.b34;
	fcn_0043bc00(g_10529e0.b30, g_10529e0.b28);
	fcn_00456750(g_10529e0.bpp, 0x80, 0x100, 0x20, 0, 1, 0x20);
	InitColorTable();
	g_6b8018 = 1;
	fcn_00438da0(g_10529e0.x, g_10529e0.y, g_10529e0.cw, g_10529e0.ch, g_10529e0.f4c, g_10529e0.f50, g_10529e0.f54, g_10529e0.w, g_10529e0.h);
	g_6b8010 = 0;
	g_1052bc4 = (float) atan2(g_1052bbc, g_10432a4);
	g_1052bb8 = (float) atan2(g_1052bb4, g_1042584);
	{
		int len;

		len = 0xf700;
		__asm {
			mov edi, offset g_10432c0
			mov ebx, len
			xor eax, eax
			lea ecx, [edi+edi*2]
			and ecx, 3
			sub ebx, ecx
			jle short L2
			rep stosb
			mov ecx, ebx
			and ebx, 3
			shr ecx, 2
			rep stosd
		L2:
			add ecx, ebx
			rep stosb
		}
	}
	fcn_00452280();
	return 1;
}
unsigned char _dpad_1042a08[2204];
