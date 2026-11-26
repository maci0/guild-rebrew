


extern int g_7746d8;
extern int g_7746a0;
extern int g_14b5be4;
extern int g_14ab314;
extern int g_14b5bb8;
#include "Develop/DieGildeAddOn/game/game_data.h"
extern char s_6ad414[];
extern char s_6ad3f0[];
extern char s_6ad3e0[];
extern char s_6a9580[];
extern char s_6a956c[];
extern char s_6aa34c[];
extern char s_6a9924[];

void __cdecl fcn_005338a0(void);
int __cdecl main_RunFrameLoop(void*, int);
int __cdecl RegisterStatusText(char*, int, int);
void __cdecl d2_ShowLagerOptions(char*, int);
void __cdecl fcn_005944d0(char*);
void __cdecl d2_OpenTransportPanel(char*);
void __cdecl d2_ShowPersonalbuch(char*, char*);
void __cdecl d2_OpenMeisterbriefDialog(char*);
void __cdecl d2_ShowHandelSearch(char*, int);
void __cdecl fcn_005e5130(char*, int);
void __cdecl fcn_00597ec0(char*);

void __cdecl d2_RunSchneiderMenu(char* obj, int arg)
{
	int info;
	int trade;
	int build;
	int stats;
	int family;
	int title;
	int diary;

	info = 0;
	stats = 0;
	family = 0;
	title = 0;
	diary = 0;
	trade = 0;
	build = 0;
	fcn_005338a0();
	while (main_RunFrameLoop(d2_RunSchneiderMenu, 0x67fff)) {
		if (g_7746d8 & 0x200) {
			info = RegisterStatusText(s_6ad414, g_14b5be4, 0x13);
			trade = RegisterStatusText(s_6ad3f0, g_14ab314, 0x16);
			build = RegisterStatusText(s_6ad3e0, g_14b5bb8, 0xc);
		}
		if (g_7746d8 & 0x400) {
			stats = RegisterStatusText(s_6a9580, g_14ad0f0, 0xe);
			family = RegisterStatusText(s_6a956c, g_14ad100, 0x15);
			title = RegisterStatusText(s_6aa34c, g_14a7b50, 0xc);
			diary = RegisterStatusText(s_6a9924, g_14a7d28, 0x16);
		}
		if (g_7746a0) {
			if (g_7746a0 == stats) {
				d2_ShowLagerOptions(obj, *(int*) (obj + 0x5d));
			} else if (g_7746a0 == info) {
				fcn_005944d0(obj);
			} else if (g_7746a0 == family) {
				d2_OpenTransportPanel(obj);
			} else if (g_7746a0 == title) {
				d2_ShowPersonalbuch(obj, s_6aa34c);
			} else if (g_7746a0 == diary) {
				d2_OpenMeisterbriefDialog(obj);
			} else if (g_7746a0 == trade) {
				d2_ShowHandelSearch(obj, arg);
			} else if (g_7746a0 == build) {
				fcn_005e5130(obj, arg);
			}
		}
		fcn_00597ec0(obj);
	}
	fcn_005338a0();
}
