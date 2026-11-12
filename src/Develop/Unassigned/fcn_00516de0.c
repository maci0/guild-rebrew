#include "Develop/DieGildeAddOn/game/game_data.h"
extern int g_778d24;
extern char g_77666a;
extern char g_699b08;
void __cdecl fcn_004428d0(char*, unsigned char, char);

/* ADDRESS: GOLDTL 0x00516de0 */
void __cdecl fcn_00516de0(char* a1, unsigned char a2)
{
	unsigned char al;
	int oldmode;
	int unit;

	unit = 0;
	if (a1 == 0)
		return;
	al = *(unsigned char*) (a1 + 0x8036);
	oldmode = (al >> 2) & 7;
	if (g_6b8010 == 0) {
		if (*(int*) a1 == 0x40 || g_778d24 >= 0x780) {
			al = (unsigned char) ((al & 0xe7) | 4);
			*(unsigned char*) (a1 + 0x8036) = al;
			g_699b08 = 1;
			unit = 1;
		} else if (g_77666a == 0) {
			al = (unsigned char) ((al & 0xf3) | 0x10);
			*(unsigned char*) (a1 + 0x8036) = al;
			g_699b08 = 4;
			unit = 4;
		} else if (g_77666a == 1) {
			al = (unsigned char) ((al & 0xeb) | 8);
			*(unsigned char*) (a1 + 0x8036) = al;
			g_699b08 = 2;
			unit = 2;
		} else if (g_77666a == 2) {
			al = (unsigned char) ((al & 0xe7) | 4);
			*(unsigned char*) (a1 + 0x8036) = al;
			g_699b08 = 1;
			unit = 1;
		}
	} else {
		if (g_77666a == 2) {
			al = (unsigned char) ((al & 0xe7) | 4);
			*(unsigned char*) (a1 + 0x8036) = al;
			unit = 1;
		} else {
			al = (unsigned char) ((al & 0xeb) | 8);
			*(unsigned char*) (a1 + 0x8036) = al;
			unit = 2;
		}
	}
	if (oldmode != ((*(unsigned char*) (a1 + 0x8036) >> 2) & 7) || a2 != 0) {
		fcn_004428d0(a1, (unsigned char) (unit >> 1), 1);
	}
}
