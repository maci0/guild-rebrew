// FUNCTION: GOLDTL 0x0052e5a0

// SIZE 0x3cc
typedef struct {
	char pad0[0xc];
	int width;
	char pad10[0x3cc - 0x10];
} Slot;

extern int g_6a25b8;
extern char* g_7746c4;
extern unsigned char* g_7746c8;
extern int g_1040494;
extern char g_6a2fac[];
extern char g_6a2f40[];
extern char g_6a2f9c[];
extern int g_14ad0c8;
extern int g_14ad0cc;
extern int g_14ad0d0;
extern int g_14ad0dc;
extern int g_6a25dc;
extern int g_6a25e0;
extern int g_6a25ec;
extern int g_6a25f0;
extern int g_6a25c0;
extern unsigned short g_774970;
extern int g_772514;
#include "client_types.h"
extern Win_1015f40 g_1015f40[0x60];

int __cdecl fcn_00470820(int a, int b, char* s);
void __cdecl fcn_004727a0(int h, int mode);
int __cdecl fcn_0052dee0(int x, int y, int z);
int __cdecl fcn_0050bfe0(unsigned char* s);
void __cdecl fcn_005186c0(int id, int a, int b, char* out);
void __cdecl fcn_00519190(char* fmt, ...);
int __cdecl fcn_0046f740(int x, int y, int kind, int owner);
int __cdecl fcn_004677e0(int a, int b, int c, int d, int e, int f, int g, int h);
void __cdecl fcn_00472380(int h, int a, int b, int c);

void __cdecl fcn_0052e5a0(void)
{
	char name[128];
	int pct;

	if (g_6a25b8 != -1) {
		return;
	}
	if (g_7746c8 == 0) {
		if (((unsigned char*)g_7746c4) != 0) {
			return;
		}
		g_6a25b8 = fcn_00470820(g_1040494 - 0x68, 0x106, g_6a2fac);
		fcn_004727a0(g_6a25b8, 0);
		g_6a25dc = fcn_0052dee0(0, 0x8c, g_14ad0c8);
		g_6a25e0 = fcn_0052dee0(0, 0xa6, g_14ad0dc);
		return;
	}
	if (*(unsigned short*) (g_7746c8 + 0x27) != g_774970) {
		return;
	}
	pct = fcn_0050bfe0(g_7746c8);
	g_6a25b8 = fcn_00470820(g_1040494 - 0x68, 0x106, g_6a2f40);
	fcn_004727a0(g_6a25b8, 0);
	fcn_004727a0(g_6a25b8, 1);
	fcn_005186c0(*(unsigned short*) (g_7746c8 + 0x27), 2, 1, name);
	fcn_00519190(g_6a2f9c, name, *g_7746c8 * 14 + 0x48e, g_7746c8 + 5);
	fcn_004727a0(g_6a25b8, 0);
	fcn_0046f740(((((Slot*)g_1015f40)[g_772514].width - 0x30) >> 1) - 1, 0x4c, *g_7746c8 + 0x427, g_772514);
	g_6a25c0 = fcn_004677e0(0x15, 0x7a, 0x30, 0, 0x64, 0x75, 0x442, g_772514);
	fcn_00472380(g_6a25c0, 0, 0x64, pct);
	g_6a25ec = fcn_0052dee0(0, 0x8c, g_14ad0cc);
	if (*g_7746c8 == 0x1e) {
		g_6a25f0 = fcn_0052dee0(0, 0xa6, g_14ad0d0);
	} else {
		g_6a25e0 = fcn_0052dee0(0, 0xa6, g_14ad0dc);
	}
}
