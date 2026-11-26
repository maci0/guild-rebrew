extern int main_LoopFlags;
extern int d2_ScreenHeight;
extern int g_1040494;
#include "Develop/DieGildeAddOn/game/game_data.h"

unsigned char* __cdecl fcn_004730c0(int, int, int, int, char*, int, int);
int __cdecl main_RunFrameLoop(void*, int);
void __cdecl fcn_00533cf0(int);
void __cdecl d2_ClearScreen(void);
void __cdecl fcn_00469e30(int);
void __cdecl fcn_00473150(unsigned char*);
void __cdecl fcn_005270c0(int);
#include <string.h>

typedef struct {
	int type;
	char name[0x78];
} SaveReq;

extern unsigned char g_7747b0;
extern char* g_14ac604;
extern int g_14ac608;
extern char g_773de8;
extern char g_6b5c60[];

void __cdecl fcn_00533a40(char*);
int __cdecl fcn_005e4060(void);
int __cdecl cm_RequestSysMessage(int, void*);
int __cdecl cm_GetCommandStatus(int);
void __cdecl fcn_00535960(void);
int __cdecl main_RunFrameLoop(void*, int);
void __cdecl ls_CaptureSavePreview(void);
void __cdecl ls_SaveGame(char*, char*, int);

/* ADDRESS: GOLDTL 0x005e3b70 */
void __cdecl d2_EnterMenuScreen(void)
{
	int flags;
	unsigned char* p;

	flags = (main_LoopFlags & ~0x2000) | 0x100000;
	p = fcn_004730c0(0, 0, g_1040494, d2_ScreenHeight, g_67d67c, 0x1e, 1);
	while (!(*p & 4)) {
		main_RunFrameLoop(0, flags);
	}
	g_1040488 = 0;
	g_1040480 = g_1040494;
	g_1040484 = 0;
	g_104048c = d2_ScreenHeight;
	main_LoopFlags = 0x24087;
	fcn_00533cf0(1);
	d2_ClearScreen();
	fcn_00469e30(0x794);
	fcn_00473150(p);
	fcn_005270c0(0);
	fcn_004730c0(0, 0, g_1040494, d2_ScreenHeight, g_67d67c, 0x32, 0xa);
}

/* ADDRESS: GOLD 0x005d7580 */
/* ADDRESS: GOLDTL 0x005e40b0 */
void __cdecl ls_QuickSave(void)
{
	SaveReq s;
	int r;

	if (g_7747b0 & 4) {
		if (!(g_7747b0 & 0x10)) {
			fcn_00533a40((char*) g_14ac608);
			return;
		}
		if (fcn_005e4060() == 0) {
			fcn_00533a40((char*) (*(int*)&g_14ac604));
			return;
		}
		memset(&s, 0, sizeof(s));
		s.type = 1;
		strcpy(s.name, "QUICKSAVE");
		r = cm_RequestSysMessage(0xf, &s);
		while (cm_GetCommandStatus(r) == 0) {
			fcn_00535960();
		}
	} else if (!(g_7747b0 & 0x80)) {
		fcn_00533a40("Quicksave");
		main_RunFrameLoop(0, 0x657c7);
		ls_CaptureSavePreview();
		g_773de8 = 1;
		ls_SaveGame("Gamedata\\Saves\\Quicksave.SAV", "Quicksave", 1);
		fcn_00533a40(g_6b5c60);
	}
}
