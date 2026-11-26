


extern int g_7746d8;
extern int g_7746a0;
extern char* g_7746cc;
#include "Develop/DieGildeAddOn/game/game_data.h"
extern int g_14ad118;
extern int g_14ad160;
extern int g_14ad140;
extern int g_14a5554;
extern char s_6a9580[];
extern char s_6aa5ac[];
extern char s_6ab3cc[];
extern char s_6aa544[];
extern char s_6ab3b0[];
extern char s_6a956c[];

void __cdecl fcn_005338a0(void);
int __cdecl main_RunFrameLoop(void*, int);
int __cdecl RegisterStatusText(char*, int, int);
void __cdecl d2_ShowLagerOptions(int, int);
void __cdecl fcn_005c72f0(int);
void __cdecl fcn_005af770(int);
void __cdecl d2_StartThievesGuildSpyPicker(int);
void __cdecl fcn_005ada30(int);
void __cdecl d2_OpenTransportPanel(int);

void __cdecl d2_RunRazziaWacheMenu(int building)
{
	int a;
	int b;
	int c;
	int d;
	int e;
	int f;

	a = 0;
	b = 0;
	c = 0;
	f = 0;
	d = 0;
	e = 0;
	fcn_005338a0();
	if (main_RunFrameLoop((void*) d2_RunRazziaWacheMenu, 0x67fff) != 0) {
		do {
			if (g_7746d8 & 0x200) {
				a = RegisterStatusText(s_6a9580, g_14ad0f0, 0xe);
				b = RegisterStatusText(s_6aa5ac, g_14ad118, 0xd);
				c = RegisterStatusText(s_6ab3cc, g_14ad160, 0x16);
				d = RegisterStatusText(s_6aa544, g_14ad140, 0x17);
				e = RegisterStatusText(s_6ab3b0, g_14a5554, 0xc);
				f = RegisterStatusText(s_6a956c, g_14ad100, 0x15);
			}
			if (g_7746a0 != 0 && (g_7746d8 & 0x200)) {
				if (g_7746a0 == a) {
					d2_ShowLagerOptions(building, *(int*) (g_7746cc + 0x14));
				}
				else if (g_7746a0 == b) {
					fcn_005c72f0(building);
				}
				else if (g_7746a0 == c) {
					fcn_005af770(building);
				}
				else if (g_7746a0 == d) {
					d2_StartThievesGuildSpyPicker(building);
				}
				else if (g_7746a0 == e) {
					fcn_005ada30(building);
				}
				else if (g_7746a0 == f) {
					d2_OpenTransportPanel(building);
				}
			}
		} while (main_RunFrameLoop((void*) d2_RunRazziaWacheMenu, 0x67fff) != 0);
	}
}
