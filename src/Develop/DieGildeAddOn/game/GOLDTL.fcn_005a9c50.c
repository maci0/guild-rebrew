


typedef struct
{
	char pad0[0xd];
	unsigned char xd;
	char pade[0x1ba];
	int x1c8;
	char pad1cc[0x50];
} Player;
// SIZE 0x21c

#include "Develop/DieGildeAddOn/game/game_player.h"
extern char g_7f4ca0[];
extern int g_7746a0;
extern int g_14aa2f0;
extern int g_14aa2f4;
extern int g_14aa2ec;
extern int g_14ad240;
extern int g_14ad248;
extern char s_6aaf40[];
extern char s_6aaf24[];
extern char s_6aaf08[];
extern char s_6aaef4[];
extern char s_6aaedc[];

void __cdecl fcn_005338a0(void);
int __cdecl main_RunFrameLoop(void*, int);
int __cdecl RegisterStatusText(char*, int, int);
int __cdecl d2_IsTutorialActionAllowed(int);
void __cdecl fcn_005ce460(int);
void __cdecl fcn_005a92c0(int);
void __cdecl d2_ShowOfficeApplicationDialog(void);

void __cdecl fcn_005a9c50(int arg)
{
	int a;
	int b;
	int c;
	int d;
	int e;

	fcn_005338a0();
	if (main_RunFrameLoop((void*) fcn_005a9c50, 0x67fff) != 0) {
		do {
			if (d2_IsTutorialActionAllowed(0x1000) == 1) {
				a = RegisterStatusText(s_6aaf40, g_14aa2f0, 0xc);
				b = RegisterStatusText(s_6aaf24, g_14aa2f4, 0xc);
				c = RegisterStatusText(s_6aaf08, g_14aa2ec, 0xc);
			}
			else {
				c = 0;
				b = 0;
				a = 0;
			}
			if (d2_IsTutorialActionAllowed(0x8000) == 1) {
				e = RegisterStatusText(s_6aaef4, g_14ad240, 0x16);
			}
			else {
				e = 0;
			}
			if ((((Player*)g_7f4ca0)[g_774970].x1c8 & 0x4000) && ((Player*)g_7f4ca0)[g_774970].xd == 1 && d2_IsTutorialActionAllowed(0x2000) == 1) {
				d = RegisterStatusText(s_6aaedc, g_14ad248, 0x16);
			}
			else {
				d = 0;
			}
			if (g_7746a0 != 0) {
				if (g_7746a0 == a) {
					fcn_005ce460(0x112);
				}
				else if (g_7746a0 == b) {
					fcn_005ce460(0x111);
				}
				else if (g_7746a0 == c) {
					fcn_005ce460(0x113);
				}
				else if (g_7746a0 == d) {
					fcn_005a92c0(arg);
				}
				else if (g_7746a0 == e) {
					d2_ShowOfficeApplicationDialog();
				}
			}
		} while (main_RunFrameLoop((void*) fcn_005a9c50, 0x67fff) != 0);
	}
}
