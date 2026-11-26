


extern int g_7746a0;
extern int g_14a7c98;
#include "Develop/DieGildeAddOn/game/game_data.h"
extern char g_6aa450[];
extern char g_6a9924[];
extern char g_6aa34c[];

void __cdecl fcn_005338a0(void);
int __cdecl main_RunFrameLoop(void*, int);
int __cdecl RegisterStatusText(char*, int, int);
void __cdecl fcn_005cf560(int);
void __cdecl d2_ShowPersonalbuch(int, char*);
void __cdecl fcn_005ada30(int);

void __cdecl fcn_0059cd20(int a)
{
	int x;
	int y;
	int z;

	fcn_005338a0();
	while (main_RunFrameLoop(fcn_0059cd20, 0x67fff) != 0) {
		z = RegisterStatusText(g_6aa450, g_14a7c98, 0xc);
		x = RegisterStatusText(g_6a9924, g_14a7d28, 0xc);
		y = RegisterStatusText(g_6aa34c, g_14a7b50, 0xc);
		if (g_7746a0 != 0) {
			if (g_7746a0 == x) {
				fcn_005cf560(a);
			}
			else if (g_7746a0 == y) {
				d2_ShowPersonalbuch(a, g_6aa34c);
			}
			else if (g_7746a0 == z) {
				fcn_005ada30(a);
			}
		}
	}
}
