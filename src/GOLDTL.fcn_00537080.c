


extern int g_7e4538;
extern int g_7e453c;
extern unsigned short g_7f4c04;
extern int g_7f4c06;
extern int g_7e4408[];
extern int g_7e43a4[];
extern int g_7e4468;
extern int g_7e446c;
extern int g_6b7fac;
extern int g_6b8010;
extern char* g_6b5cf8;
extern int g_6a2c24;
extern int g_7747c0;
extern float g_699b0c;
extern float g_664e80;
extern char g_6a33a4[];

void __cdecl fcn_00415d70(int);
void __cdecl fcn_00416a20(int);
unsigned short __cdecl gm_RandomMod(int);
int __cdecl fcn_004234e0(int, char*, int, int, int, int, int);
#include "Develop/DieGildeAddOn/game/sonnenstrahlen.h"

void __cdecl fcn_00537080(void)
{
	if (g_7e4538 != 0) {
		fcn_00415d70(g_7e4538);
	}
	if (g_7e453c != 0) {
		fcn_00416a20(g_7e453c);
	}
	if (g_7e4408[(unsigned short) (*(int*)&g_7f4c04)] != 0) {
		if (gm_RandomMod(300) == 0 || (g_7e4408[(unsigned short) (*(int*)&g_7f4c04)] == 3 && gm_RandomMod(100) == 0)) {
			g_7e4468 = g_6b7fac;
			g_7e446c = gm_RandomMod(8) + 8;
			fcn_004234e0(g_7747c0, g_6a33a4, 1, 0x3f, (int) (g_699b0c * g_664e80), 0, 0);
		}
	}
	if (g_6b8010 == 0) {
		if ((unsigned short) (*(int*)&g_7f4c04) >= 0xb && (unsigned short) (*(int*)&g_7f4c04) <= 0x11 && g_7e43a4[(unsigned short) (*(int*)&g_7f4c04)] != 0
		    && g_7e43a4[(unsigned short) (*(int*)&g_7f4c04) + 1] == 0
		    && g_7f4c06 > 0x1e) {
			if (gm_RandomMod(0x80) > 0x60 && (*(int*)&g_6b5cf8) == 0) {
				CreateSonnenstrahlen();
			}
			g_6a2c24 = (unsigned short) (*(int*)&g_7f4c04);
		}
		if (g_6a2c24 != -1 && (unsigned short) (*(int*)&g_7f4c04) > g_6a2c24 && g_7f4c06 > 0x1e) {
			if ((*(int*)&g_6b5cf8) != 0) {
				StopSonnenstrahlen(g_6b5cf8, 1);
			}
			g_6a2c24 = -1;
		}
	}
}
