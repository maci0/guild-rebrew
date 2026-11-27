#include "client_types.h"
#include "Develop/DieGildeAddOn/game/building_prototype.h"

void* __cdecl memset(void*, int, unsigned int);
#pragma intrinsic(memset)





// SIZE 0xe

typedef struct
{
	int x0;
	unsigned char type;
	char pad5[3];
	int x8;
	int xc;
	char pad10[0x18];
	pos14_7f4c00 name;
	unsigned char x36;
	char pad37[0x21];
	char x58;
	char pad59[3];
	int x5c;
	int x60;
	char pad64[0x94];
} Packet;
// SIZE 0xf8

typedef struct
{
	int x0;
	int x4;
	char pad8[0x180];
	unsigned char x188;
	char pad189[0x93];
} Player;
// SIZE 0x21c

typedef struct
{
	unsigned char x0;
	char pad1[0x24c];
} Shop;
// SIZE 0x24d

extern char g_7f4ca0[];
extern unsigned char* lpGebaeudePROT;
#include "Develop/DieGildeAddOn/game/game_player.h"
#include "client_types.h"
extern pos14_7f4c00 gm_GameTime;
extern int g_14abc44;
#include "Develop/DieGildeAddOn/game/game_data.h"
#include "client_dialog_state.h"
extern char s_6ac79c[];

char* __cdecl he_StartHandlungSearch(int, int, int, int, int);
char* __cdecl he_fn_Handlung(void);
void __cdecl io_FormatTextBuffer(char*, int, ...);
int __cdecl fcn_00526120(char*, int);
void __cdecl fcn_0052a0c0(unsigned char*, int);
int __cdecl d2_LoadForm(int, int, char*);
void __cdecl d2_CenterDialogWindows(int);
void __cdecl d2_SetOverlayAnimation(int, int);
void __cdecl d2_SetForm(int, int);
int __cdecl io_AppendText(int, ...);
int __cdecl d2_GetWindowListItem(int, int, int);
int __cdecl cm_SendCopyEntityData(Packet*);
void __cdecl cm_ExProdObjekt(void);
int __cdecl main_RunFrameLoop(void*, int);
void __cdecl d2_DestroyForm(int);
void __cdecl d2_RestoreHudAfterDialog(void);
void __cdecl d3_EndCameraAndUiMode(void);
void __cdecl sv_ClearObjectSelection(void);

void __cdecl d2_ShowTrainingDialog(unsigned char* obj, char* sceneObj, int targetId)
{
	int btn2;
	int btn1;
	int dlg;
	Packet pkt;
	char buf[0x800];
	int kind;
	BUILDING_PROTOTYPE * t;
	int cnt;
	char* p;
	int s;
	int n;
	int i;

	cnt = 0;
	t = &((BUILDING_PROTOTYPE *)lpGebaeudePROT)[obj[0]];
	if (t->category == 4) {
		kind = 1;
	}
	else {
		kind = t->category == 0x10 ? 0xf : 0x13;
	}
	for (p = he_StartHandlungSearch(2, 0, 0x16, 3, *(int*) (obj + 1)); p != 0; p = he_fn_Handlung()) {
		cnt++;
	}
	if (cnt >= 3) {
		io_FormatTextBuffer(buf, 0x1a4a, cnt);
		fcn_00526120(buf, 0);
		return;
	}
	fcn_0052a0c0(obj, 1);
	dlg = d2_LoadForm(0, 0, s_6ac79c);
	d2_CenterDialogWindows(dlg);
	d2_SetOverlayAnimation(0, 0);
	d2_SetForm(dlg, 1);
	s = io_AppendText(0x1a45, kind + 0x20d, kind + 0x20e, targetId + 0x16b7);
	btn1 = d2_GetWindowListItem(dlg, 1, s);
	btn2 = d2_GetWindowListItem(dlg, 1, s + 1);
	g_100f1dc = -1;
	do {
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
		}
		if (g_100f1dc != -1) {
			if (d2_CurrentElementId == btn1) {
				n = 0;
				for (i = 0; i < 768; i++) {
					if (n >= 3) {
						break;
					}
					if (((Player*)g_7f4ca0)[i].x188 != 0) {
						memset(&pkt, 0, sizeof(pkt));
						pkt.type = 0x16;
						pkt.x8 = ((Player*)g_7f4ca0)[g_774970].x4;
						pkt.xc = *(int*) (obj + 1);
						pkt.name = (*(pos14_7f4c00*)&gm_GameTime);
						pkt.x36 = 1;
						if (sceneObj != 0) {
							pkt.x60 = *(int*) (sceneObj + 2);
						}
						else {
							pkt.x60 = -1;
						}
						pkt.x5c = ((Player*)g_7f4ca0)[i].x4;
						pkt.x58 = (char) targetId;
						cm_SendCopyEntityData(&pkt);
						n++;
					}
				}
				if (n == 0) {
					fcn_00526120((char*) g_14abc44, 0);
				}
				else {
					cm_ExProdObjekt();
					if (n > 3) {
						io_FormatTextBuffer(buf, 0x1a4a, 3);
						fcn_00526120(buf, 0);
					}
					g_774654 = 1;
				}
			}
			else if (d2_CurrentElementId == btn2) {
				g_774654 = 1;
			}
		}
	} while (main_RunFrameLoop((void*) d2_ShowTrainingDialog, 0x677c7) != 0);
	d2_DestroyForm(dlg);
	d2_RestoreHudAfterDialog();
	d3_EndCameraAndUiMode();
	sv_ClearObjectSelection();
}
