#include "client_types.h"



#include <string.h>





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
	char pad37;
	int ids[6];
	char pad50[8];
	char str[0x20];
	int x78;
	int x7c;
	char pad80[0x78];
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

extern char g_7f4ca0[];
extern char* ch_ContextCharacters[32];
#include "Develop/DieGildeAddOn/game/game_player.h"
#include "client_types.h"
extern pos14_7f4c00 gm_GameTime;
extern int g_14abc98;
extern int g_100f1dc;
extern int d2_CurrentElementId;
extern int g_14ce8e0;
#include "client_dialog_state.h"
extern char* g_7746c4;
extern char* g_7746cc;
extern char s_6ab348[];

int __cdecl fcn_00526120(int, int);
int __cdecl fcn_00470820(int, int, char*);
void __cdecl d2_CenterDialogWindows(int);
void __cdecl d2_SetOverlayAnimation(int, int);
void __cdecl d2_SetForm(int, int);
int __cdecl io_AppendText(int, ...);
int __cdecl d2_GetWindowListItem(int, int, int);
int __cdecl cm_SendCopyEntityData(Packet*);
void __cdecl cm_ExProdObjekt(void);
int __cdecl main_RunFrameLoop(void*, int);
void __cdecl fcn_00471e30(int);

int __cdecl fcn_005af7f0(int unused, char* str)
{
	int btn2;
	int btn1;
	Packet pkt;
	int i;
	int n;
	int dlg;
	int s;

	if (str == 0) {
		return 0;
	}
	for (i = 0; i < 768; i++) {
		if (((Player*)g_7f4ca0)[i].x188 != 0) {
			break;
		}
	}
	if (i >= 768) {
		fcn_00526120(g_14abc98, 0);
		return 0;
	}
	dlg = fcn_00470820(0, 0, s_6ab348);
	d2_CenterDialogWindows(dlg);
	d2_SetOverlayAnimation(0, 0);
	d2_SetForm(dlg, 1);
	s = io_AppendText(0x1a70);
	btn1 = d2_GetWindowListItem(dlg, 1, s);
	btn2 = d2_GetWindowListItem(dlg, 1, s + 1);
	g_100f1dc = -1;
	do {
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
		}
		if (g_100f1dc != -1) {
			if (d2_CurrentElementId == btn1) {
				pkt.type = 0x65;
				pkt.x8 = ((Player*)g_7f4ca0)[g_774970].x4;
				pkt.xc = *(int*) (g_7746c4 + 1);
				pkt.name = (*(pos14_7f4c00*)&gm_GameTime);
				pkt.x36 = 2;
				strcpy(pkt.str, str);
				for (i = 0; i < 6; i++) {
					pkt.ids[i] = -1;
				}
				n = 0;
				pkt.x78 = *(int*) (g_7746c4 + 1);
				pkt.x7c = *(int*) (g_7746cc + 2);
				for (i = 0; i < 32; i++) {
					if (n >= 6) {
						break;
					}
					if (((Player**)ch_ContextCharacters)[i] != 0 && ((Player**)ch_ContextCharacters)[i]->x188 != 0) {
						pkt.ids[n] = ((Player**)ch_ContextCharacters)[i]->x4;
						n++;
					}
				}
				if (n != 0) {
					cm_SendCopyEntityData(&pkt);
					cm_ExProdObjekt();
				}
				g_774654 = 2;
			}
			else if (d2_CurrentElementId == btn2) {
				g_774654 = 1;
			}
		}
	} while (main_RunFrameLoop((void*) fcn_005af7f0, 0x677c7) != 0);
	fcn_00471e30(dlg);
	return 0;
}
