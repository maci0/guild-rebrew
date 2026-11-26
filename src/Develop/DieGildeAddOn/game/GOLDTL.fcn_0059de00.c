


extern int g_7746d8;
extern int g_7746a0;
extern int g_14ad118;
extern int g_14ad110;
extern int g_14ad108;
#include "Develop/DieGildeAddOn/game/game_data.h"
extern int g_14ad170;
extern int g_14ad140;
extern int g_14abd28;
extern int g_14ad168;
extern int g_14ad0e8;
extern char s_6aa5ac[];
extern char s_6aa594[];
extern char s_6aa584[];
extern char s_6aa3c0[];
extern char s_6aa3b0[];
extern char s_6aa564[];
extern char s_6aa544[];
extern char s_6aa52c[];
extern char s_6aa514[];
extern char s_6a9580[];
extern char s_6aa3d0[];
extern char s_6aa508[];

void __cdecl fcn_005338a0(void);
int __cdecl main_RunFrameLoop(void*, int);
int __cdecl RegisterStatusText(char*, int, int);
char* __cdecl fcn_00502cd0(int, int, int, int, int);
void __cdecl d3_UpdateBuildingInteriorState(void);
void __cdecl d2_ShowLagerOptions(char*, int);
void __cdecl fcn_005c5b10(char*);
void __cdecl d2_OpenTransportPanel(char*);
void __cdecl fcn_005c72f0(char*);
void __cdecl fcn_005c79a0(char*);
void __cdecl fcn_0059d020(char*);
void __cdecl d2_SelectPickpocketTarget(char*);
void __cdecl fcn_0059d630(char*);
void __cdecl d2_SelectBriberyTarget(char*);
void __cdecl fcn_0059dc50(char*);

void __cdecl d2_RunRaeuberInteriorHud(char* e)
{
	int a;
	int b;
	int c;
	int d;
	int f;
	int g;
	int h;
	int i;
	int j;
	int k;
	int l;
	int m;

	k = 0;
	j = 0;
	h = 0;
	i = 0;
	a = 0;
	f = 0;
	d = 0;
	b = 0;
	c = 0;
	g = 0;
	l = 0;
	m = 0;
	fcn_005338a0();
	if (main_RunFrameLoop((void*) d2_RunRaeuberInteriorHud, 0x67fff) != 0) {
		do {
			if (g_7746d8 & 0x200) {
				a = RegisterStatusText(s_6aa5ac, g_14ad118, 0xd);
				b = RegisterStatusText(s_6aa594, g_14ad110, 0x15);
				c = RegisterStatusText(s_6aa584, g_14ad108, 0x17);
				if (fcn_00502cd0(*(int*) (e + 0x5d), 2, 6, 0, 0x35) != 0) {
					d = RegisterStatusText(s_6aa3c0, g_14abc30, 0x17);
				}
				if (fcn_00502cd0(*(int*) (e + 0x5d), 2, 6, 0, 0x34) != 0) {
					f = RegisterStatusText(s_6aa3b0, g_14abc2c, 0x17);
				}
				k = RegisterStatusText(s_6aa564, g_14ad170, 0x17);
				l = RegisterStatusText(s_6aa544, g_14ad140, 0x17);
				m = RegisterStatusText(s_6aa52c, g_14abd28, 0x17);
				g = RegisterStatusText(s_6aa514, g_14ad168, 0x17);
			}
			if (g_7746d8 & 0x400) {
				h = RegisterStatusText(s_6a9580, g_14ad0f0, 0xe);
				i = RegisterStatusText(s_6aa3d0, g_14ad0e8, 0xe);
				j = RegisterStatusText(s_6aa508, g_14ad100, 0x15);
			}
			d3_UpdateBuildingInteriorState();
			if (g_7746a0 != 0) {
				if (g_7746a0 == h) {
					d2_ShowLagerOptions(e, *(int*) (e + 0x5d));
				}
				else if (g_7746a0 == i) {
					fcn_005c5b10(e);
				}
				else if (g_7746a0 == j) {
					d2_OpenTransportPanel(e);
				}
				else if (g_7746a0 == a) {
					fcn_005c72f0(e);
				}
				else if (g_7746a0 == f || g_7746a0 == d || g_7746a0 == g) {
					fcn_005c79a0(e);
				}
				else if (g_7746a0 == b) {
					fcn_0059d020(e);
				}
				else if (g_7746a0 == c) {
					d2_SelectPickpocketTarget(e);
				}
				else if (g_7746a0 == k) {
					fcn_0059d630(e);
				}
				else if (g_7746a0 == l) {
					d2_SelectBriberyTarget(e);
				}
				else if (g_7746a0 == m) {
					fcn_0059dc50(e);
				}
			}
		} while (main_RunFrameLoop((void*) d2_RunRaeuberInteriorHud, 0x67fff) != 0);
	}
}
