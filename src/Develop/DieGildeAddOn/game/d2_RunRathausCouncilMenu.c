


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
extern char gm_EntitySlotTable[];
extern int sv_ClickedObjekt;
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

void __cdecl d2_ClearStatusTextSlots(void);
int __cdecl main_RunFrameLoop(void*, int);
int __cdecl RegisterStatusText(char*, int, int);
int __cdecl d2_IsTutorialActionAllowed(int);
void __cdecl d2_RunGesetzbuchDialog(int);
void __cdecl d2_RunBuergerrechtDialog(int);
void __cdecl d2_ShowOfficeApplicationDialog(void);

/* ADDRESS: GOLDDE 0x0058e760 */
void __cdecl d2_RunRathausCouncilMenu(int building)
{
	int a;
	int b;
	int c;
	int d;
	int e;

	d2_ClearStatusTextSlots();
	if (main_RunFrameLoop((void*) d2_RunRathausCouncilMenu, 0x67fff) != 0) {
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
			if ((((Player*)gm_EntitySlotTable)[gm_LocalPlayerSlot].x1c8 & 0x4000) && ((Player*)gm_EntitySlotTable)[gm_LocalPlayerSlot].xd == 1 && d2_IsTutorialActionAllowed(0x2000) == 1) {
				d = RegisterStatusText(s_6aaedc, g_14ad248, 0x16);
			}
			else {
				d = 0;
			}
			if (sv_ClickedObjekt != 0) {
				if (sv_ClickedObjekt == a) {
					d2_RunGesetzbuchDialog(0x112);
				}
				else if (sv_ClickedObjekt == b) {
					d2_RunGesetzbuchDialog(0x111);
				}
				else if (sv_ClickedObjekt == c) {
					d2_RunGesetzbuchDialog(0x113);
				}
				else if (sv_ClickedObjekt == d) {
					d2_RunBuergerrechtDialog(building);
				}
				else if (sv_ClickedObjekt == e) {
					d2_ShowOfficeApplicationDialog();
				}
			}
		} while (main_RunFrameLoop((void*) d2_RunRathausCouncilMenu, 0x67fff) != 0);
	}
}
