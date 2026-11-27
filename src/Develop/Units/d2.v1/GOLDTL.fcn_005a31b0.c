extern int g_6a256c;
extern volatile int g_6b7fac;
extern int d2_CurrentWindowId;
#include "client_dialog_state.h"
extern int g_14ce8e0;
extern char g_1015f40[];
extern char g_868060[];
#include "Develop/DieGildeAddOn/game/season_slots.h"
extern double g_665ed0;
extern char g_6a40b0[];

char* __cdecl d3_FindSceneObject(int, int, int, char*);
void __cdecl d3_AnimateCameraToNode(int, int);
int __cdecl main_RunFrameLoop(void*, int);
int __cdecl fcn_00470820(int, int, char*);
void __cdecl d2_CenterDialogWindows(int);
void __cdecl d2_DestroyForm(int);
void __cdecl d2_SetForm(int, int);
int __cdecl io_AppendText(char* fmt, ...);
void __cdecl d2_SetBackgroundTexture(const char* name, int win);
char* __cdecl fcn_00502cd0(int, ...);
char* __cdecl gm_FindSlotById(int, int);
unsigned short* __cdecl gm_NextEntityQueryMatch(void);
int __cdecl fcn_005a30c0(int x, int y, int layer, int a4, int a5);
int __cdecl sprintf(char*, const char*, ...);

/* ADDRESS: GOLDTL 0x005a31b0 */
void __cdecl d2_ShowCityTradeInfoDialog(char* building)
{
	char name[260];
	int win;
	int win2;
	unsigned short* it;
	char* slot;
	int p;
	int k;
	int idx;
	int n;
	unsigned int flag;
	int object;
	double dt;
	char* windowData;

	flag = 0;
	windowData = 0;
	if (building[0] != 'G') {
		return;
	}
	p = (int) d3_FindSceneObject(0, 0x100, 0, g_6a40b0);
	if (p != 0) {
		d3_AnimateCameraToNode(p, g_6a256c);
	}
	object = (int) d3_FindSceneObject(0, 0x40, 0, "ob_KARTENTISCH");
	idx = -1;
	k = -1;
	if (main_RunFrameLoop((void*) d2_ShowCityTradeInfoDialog, 0x677c7)) {
		do {
			if (g_14ce8e0 != 0) {
				g_774654 = 1;
			}
			if (k != 1) {
				if (idx != -1) {
					d2_DestroyForm(idx);
				}
				idx = fcn_00470820(0, 0, "Handel\\Handel_Stadtinfo");
				d2_CenterDialogWindows(idx);
				d2_SetForm(idx, 0);
				win = d2_CurrentWindowId * 0x3cc;
				*(int*) (win + 0x10162e8) = 0x18;
				*(int*) (win + 0x10162ec) = 0x18;
				*(int*) (win + 0x10162f0) = 0x1c;
				*(int*) (win + 0x10162f4) = 0xb;
				d2_SetForm(idx, 1);
				io_AppendText((char*) 0x1a11);
				d2_SetForm(idx, 5);
				io_AppendText((char*) 0x1a14, *(int*) (building + 0x65) * 0x2f4 + g_868060, g_85ab80[*(int*) (building + 0x65)].unk_00);
				windowData = g_1015f40 + *(int*) (idx * 700 + 0x103814c) * 0x3cc;
				sprintf(name, "Wappen128_ns_Stadt_%s", (char*) (*(int*) (building + 0x65) * 0x2f4 + (int) g_868060));
				d2_SetBackgroundTexture(name, *(int*) windowData);
				*(int*) (windowData + 0x3a4) = 0;
				flag = g_6b7fac;
				slot = fcn_00502cd0(*(int*) (building + 0x5d), 2, 0, 0x1db, 6);
				if (slot == 0) {
					return;
				}
				win2 = (int) fcn_00502cd0(*(int*) (building + 0x5d), 2, 0, 0x1dc, 6);
				if (win2 == 0) {
					return;
				}
				n = 0;
				d2_SetForm(idx, 3);
				io_AppendText((char*) 0x1a12);
				it = (unsigned short*) fcn_00502cd0(*(int*) (slot + 0x14), 1, 5);
				while (it != 0) {
					p = (int) gm_FindSlotById(*(int*) (building + 0x65), *it);
					if (p != 0 && *(int*) (p + 4) != 0) {
						fcn_005a30c0((n % 4) * 0x3c + 0xe, (n / 4) * 0x50 + 0x1e, d2_CurrentWindowId, *it, *(int*) (building + 0x65));
						n++;
					}
					it = gm_NextEntityQueryMatch();
				}
				n = 0;
				d2_SetForm(idx, 4);
				io_AppendText((char*) 0x1a13);
				it = (unsigned short*) fcn_00502cd0(*(int*) (win2 + 0x14), 1, 5);
				while (it != 0) {
					p = (int) gm_FindSlotById(*(int*) (building + 0x65), *it);
					if (p != 0 && *(int*) (p + 4) != 0) {
						fcn_005a30c0((n % 4) * 0x3c + 0xe, (n / 4) * 0x50 + 0x1e, d2_CurrentWindowId, *it, *(int*) (building + 0x65));
						n++;
					}
					it = gm_NextEntityQueryMatch();
				}
				k = 1;
			}
			dt = (double) ((unsigned int)g_6b7fac - flag) * (1.0 / 650.0);
			if (!(dt < g_665ed0)) {
				dt = g_665ed0;
			}
			*(float*) (windowData + 0x3a4) = (float) dt;
		} while (main_RunFrameLoop((void*) d2_ShowCityTradeInfoDialog, 0x677c7));
		if (idx != -1) {
			d2_DestroyForm(idx);
		}
	}
	if (object != 0) {
		d3_AnimateCameraToNode(object, g_6a256c);
	}
}
