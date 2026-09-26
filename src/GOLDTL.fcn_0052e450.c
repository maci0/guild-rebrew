// FUNCTION: GOLDTL 0x0052e450
// SIZE: 322

// SIZE 0x3cc
typedef struct {
	char pad0[0xc];
	int width;
	char pad10[0x3cc - 0x10];
} Slot;

// SIZE 0x2f4
typedef struct {
	char pad0[0x5c];
	int f5c;
	char pad60[0x2f4 - 0x60];
} Ent;

extern int g_6a25b8;
extern int g_1040494;
extern char g_6a2f80[];
extern char g_6a2f74[];
extern int g_772514;
#include "client_types.h"
extern Win_1015f40 g_1015f40[0x60];
extern char* g_1015ea0;
extern unsigned short g_774970;
extern int g_14b5e84;
extern int g_6a25e8;
extern int g_6a25c0;
extern int g_6a25d4;
extern int g_6b5c48;

unsigned short* __cdecl gm_ResolveParentEntity(unsigned short* e);
int __cdecl fcn_00470820(int a, int b, char* s);
void __cdecl fcn_004727a0(int h, int mode);
void __cdecl fcn_00519190(char* fmt, int a, int b);
int __cdecl fcn_0046f740(int x, int y, int kind, int owner);
int __cdecl fcn_0052dee0(int x, int y, int z);
int __cdecl fcn_004677e0(int a, int b, int c, int d, int e, int f, int g, int h);
void __cdecl fcn_00472380(int h, int a, int b, int c);

void __cdecl fcn_0052e450(unsigned short* e)
{
	unsigned short* parent;
	int x;
	int id;

	if (g_6a25b8 == -1) {
		parent = gm_ResolveParentEntity(e);
		if (parent != 0) {
			g_6a25b8 = fcn_00470820(g_1040494 - 0x68, 0x106, g_6a2f80);
			fcn_004727a0(g_6a25b8, 1);
			fcn_00519190(g_6a2f74, *parent, *e * 2 + 0x9a8);
			fcn_004727a0(g_6a25b8, 0);
			x = ((((Slot*)g_1015f40)[g_772514].width - 0x30) >> 1) - 1;
			id = fcn_0046f740(x, 0x30, *e + 0xdf, g_772514);
			((Ent*)g_1015ea0)[id].f5c = 1;
			if (*parent == g_774970) {
				g_6a25e8 = fcn_0052dee0(x, 0xac, g_14b5e84);
			}
			g_6a25c0 = fcn_004677e0(0x18, 0x66, 0x30, 0, 0x64, 0x75, 0x442, g_772514);
			fcn_00472380(g_6a25c0, 0, 0x64, *((unsigned char*) e + 0x12));
			fcn_004727a0(g_6a25b8, 2);
			g_6a25d4 = g_772514;
			g_6b5c48 = *(int*) ((char*) e + 0x3b);
		}
	}
}
