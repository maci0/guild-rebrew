


typedef struct {
	unsigned short id;
	char pad2[7];
	unsigned char b9;
	char pada[0x15f];
	unsigned char b169;
	char pad16a[0xb2];
} Ent5aa1;
// SIZE 0x21c

typedef struct {
	int kind;
	int who;
	int cost;
	int pad[2];
} Req5aa1;
// SIZE 0x14

#define MAX5AA1(a, b) ((a) > (b) ? (a) : (b))

#include "Develop/DieGildeAddOn/game/entity_record.h"
#include "Develop/DieGildeAddOn/game/game_player.h"
extern unsigned char g_773d75;

extern float g_664388;
extern char g_6aaf58[];
extern int d2_CurrentWindowId;
extern int g_100f1dc;
extern int g_14ce8e0;
extern int d2_CurrentElementId;
#include "client_dialog_state.h"

#include "Develop/DieGildeAddOn/game/spiel.h"
int __cdecl fcn_00526010(Ent5aa1*, int, unsigned char);
int __cdecl fcn_00470820(int, int, char*);
void __cdecl d2_CenterDialogWindows(int);
void __cdecl d2_SetOverlayAnimation(int, int);
void __cdecl d2_SetForm(int, int);
void __cdecl fcn_005340f0(int);
int __cdecl io_AppendText(int, ...);
int __cdecl d2_GetWindowListItem(int, int, int);
void __cdecl fcn_004eb780(Ent5aa1*, Req5aa1*);
int __cdecl main_RunFrameLoop(void*, int);
void __cdecl fcn_00471e30(int);

int __cdecl fcn_005aa120(int unused, char* p)
{
	int w2;
	Req5aa1 req;
	int cost;
	int h;
	int name;
	int t;
	int w1;

	cost = (int) MAX5AA1(gm_WalkEntityChain((*(unsigned short*)&((ENTITY_RECORD_VIEW*)g_7f4ca0)[g_774970].entity_index)) * 0.01f, g_664388);
	if (fcn_00526010(((Ent5aa1*)&((ENTITY_RECORD_VIEW*)g_7f4ca0)[g_774970]), cost, g_773d75) == 0) {
		return 0;
	}
	h = fcn_00470820(0, 0, g_6aaf58);
	d2_CenterDialogWindows(h);
	d2_SetOverlayAnimation(0, 0);
	d2_SetForm(h, 0);
	fcn_005340f0(d2_CurrentWindowId);
	d2_SetForm(h, 1);
	io_AppendText(0x165f);
	d2_SetForm(h, 2);
	if ((*(unsigned char*)&((ENTITY_RECORD_VIEW*)g_7f4ca0)[g_774970].gender) == 0) {
		name = (*(unsigned char*)&((ENTITY_RECORD_VIEW*)g_7f4ca0)[g_774970].grade) + 0x253;
	} else {
		name = (*(unsigned char*)&((ENTITY_RECORD_VIEW*)g_7f4ca0)[g_774970].grade) + 0x27b;
	}
	t = io_AppendText(0x1660, name, 5, cost, *(unsigned short*) (p + 0x27), p);
	w1 = d2_GetWindowListItem(h, 2, t);
	w2 = d2_GetWindowListItem(h, 2, t + 1);
	g_100f1dc = -1;
	do {
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
		}
		if (g_100f1dc != -1) {
			if (d2_CurrentElementId == w1 && fcn_00526010(((Ent5aa1*)&((ENTITY_RECORD_VIEW*)g_7f4ca0)[g_774970]), cost, g_773d75) != 0) {
				req.kind = 2;
				req.who = *(int*) (p + 1);
				req.cost = cost;
				fcn_004eb780(((Ent5aa1*)&((ENTITY_RECORD_VIEW*)g_7f4ca0)[g_774970]), &req);
				g_774654 = 2;
			} else if (d2_CurrentElementId == w2) {
				g_774654 = 1;
			}
		}
	} while (main_RunFrameLoop(fcn_005aa120, 0x677c7) != 0);
	fcn_00471e30(h);
	return 1;
}
