

typedef struct
{
	int btn;
	char* rel;
	char* obj;
	int flags;
} Row;
// SIZE 0x10

typedef struct
{
	char pad[0x21c];
} Player;
// SIZE 0x21c

#include "Develop/Units/d2.v1/d2_win.h"






// SIZE 0x3cc

#include "Develop/DieGildeAddOn/game/entity_record.h"
#include "client_types.h"
extern Win_1015f40 g_1015f40[0x60];
#include "Develop/DieGildeAddOn/game/game_player.h"
extern unsigned char g_773d75;
#include "Develop/DieGildeAddOn/game/game_data.h"
#include "Develop/Units/d2.v1/client_dialog_state.h"
extern char s_6aade4[];
extern char s_6811b0[];
extern char s_6b5c60[];

int __cdecl d2_LoadForm(int, int, char*);
void __cdecl d2_CenterDialogWindows(int);
void __cdecl d2_SetForm(int, int);
void __cdecl d2_AddWindowScrollButtons(int, int, int, int, int);
void __cdecl d2_SetOverlayAnimation(int, int);
int __cdecl io_AppendText(int, ...);
void __cdecl d2_ClearWindowChildren(int, int);
char* __cdecl gm_StartFilteredEntitySearch(int, int);
char* __cdecl gm_AddObjekt(void);
char* __cdecl he_StartHandlungSearch(int, int, int);
char* __cdecl he_fn_Handlung(void);
int __cdecl d2_GetWindowListItem(int, int, int);
void __cdecl d3_EndCameraAndUiMode(void);
int __cdecl gm_CheckEntityStock(Player*, int, char);
void __cdecl d2_EnterBuildingObjekt(char*, int, char*);
int __cdecl main_RunFrameLoop(void*, int);
void __cdecl d2_DestroyForm(int);

void __cdecl d2_OpenRathausGebInfo(void)
{
	int flag;
	Row rows[128];
	int dlg;
	int w;
	int n;
	char* e;
	char* r;
	int i;

	n = 0;
	flag = 1;
	dlg = d2_LoadForm(0, 0, s_6aade4);
	d2_CenterDialogWindows(dlg);
	d2_SetForm(dlg, 2);
	w = d2_CurrentWindowId;
	d2_SetForm(dlg, 0);
	d2_AddWindowScrollButtons(-1, -1, d2_CurrentWindowId, w, 0x767);
	d2_SetOverlayAnimation(0, 0);
	*(int*) &((D2_WIN*)g_1015f40)[w].pad3c[0x238] = 0x5a;
	do {
		if (flag != 0) {
			d2_SetForm(dlg, 1);
			io_AppendText(0x17f6);
			d2_SetForm(dlg, 2);
			io_AppendText((int) s_6811b0);
			d2_ClearWindowChildren(d2_CurrentWindowId, 1);
			n = 0;
			for (e = gm_StartFilteredEntitySearch(1, 6); e != 0; e = gm_FindNextFilteredEntity()) {
				if (e[0x5a] & 2) {
					for (r = he_StartHandlungSearch(1, 0, 0x1b); r != 0; r = he_fn_Handlung()) {
						if (*(int*) (r + 0xac) == *(int*) (e + 1)) {
							rows[n].rel = r;
							rows[n].btn = d2_GetWindowListItem(dlg, 2, io_AppendText(0x17f5, (unsigned char) e[0] + 0x427, *(unsigned short*) (e + 0x27), e, *(int*) (r + 0xb0)));
							rows[n].obj = e;
							rows[n].flags = *(unsigned short*) (e + 0x5a);
							n++;
							break;
						}
					}
				}
			}
			flag = 0;
		}
		for (i = 0; i < n; i++) {
			if (rows[i].flags != *(unsigned short*) (rows[i].obj + 0x5a)) {
				flag = 1;
				break;
			}
		}
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
			d3_EndCameraAndUiMode();
		}
		if (g_100f1dc != -1) {
			for (i = 0; i < n; i++) {
				if (d2_CurrentElementId == rows[i].btn && *(unsigned short*) (rows[i].obj + 0x27) != g_774970 &&
				    gm_CheckEntityStock(((Player*)&((ENTITY_RECORD_VIEW*)g_7f4ca0)[g_774970]), *(int*) (rows[i].rel + 0xb0), (*(char*)&g_773d75)) != 0) {
					d2_EnterBuildingObjekt(rows[i].obj, -1, s_6b5c60);
				}
			}
		}
	} while (main_RunFrameLoop((void*) d2_OpenRathausGebInfo, 0x677c7) != 0);
	d2_DestroyForm(dlg);
}
