

// SIZE 0x8
typedef struct {
	int id;
	int v;
} Pair;

extern int g_6abb00;
#include "client_types.h"
extern Btn_776c60 g_776c60[6];
extern char* g_775318;
extern char g_7f4ca0[];
extern int g_772514;
extern char* g_77255c;
extern int g_10161cc[];

int __cdecl fcn_0046f100(int, int, int, int, int, int);
int __cdecl fcn_0046f740(int, int, int, int);
int __cdecl fcn_00519190(int, ...);

void __cdecl fcn_005c5da0(int layer, int x, int y, unsigned short who, int text)
{
	int i;

	if (g_6abb00 == -1) {
		for (i = 0; i < 6; i++) {
			((Pair*)g_776c60)[i].id = -1;
			((Pair*)g_776c60)[i].v = 0;
		}
		g_775318 = g_7f4ca0 + who * 540;
		g_6abb00 = fcn_0046f100(x, y, 0xcd, 0xc4, 0x10, layer);
		fcn_0046f740(0, 0, 0x587, g_6abb00);
		fcn_0046f100(0, 0x2c, *(int*) (g_77255c + 0xc), 0x1e, 0x110, g_772514);
		g_10161cc[g_772514 * 243] = 0x54;
		fcn_00519190(text);
	}
}
