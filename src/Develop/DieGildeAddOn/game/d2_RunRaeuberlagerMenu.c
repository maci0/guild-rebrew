


typedef struct
{
	char pad0[0x247];
	unsigned char x247;
	char pad248[5];
} Shop;
// SIZE 0x24d

extern unsigned char* lpGebaeudePROT;
extern int d2_SelectedEntityUiFlags;
extern int sv_ClickedObjekt;
extern int g_14abaa4;
extern int g_14abaf4;
extern int g_14ad108;
extern int g_14ad178;
extern int g_14a7c98;
#include "Develop/DieGildeAddOn/game/game_data.h"
extern char s_6ab260[];
extern char s_6ab24c[];
extern char s_6aa544[];
extern char s_6aa584[];
extern char s_6ab230[];
extern char s_6ab214[];
extern char s_6aa34c[];
extern char s_6a9924[];

void __cdecl d2_ClearStatusTextSlots(void);
int __cdecl d3_FindSceneObject(int, int, int, char*);
void __cdecl d3_SetSubtreeVisible(int, int);
int __cdecl main_RunFrameLoop(void*, int);
int __cdecl RegisterStatusText(char*, int, int);
void __cdecl d2_StartEinbruchTargetSelect(unsigned char*);
void __cdecl d2_StartThievesGuildSpyPicker(unsigned char*);
void __cdecl d2_OpenAngriffDialog(unsigned char*);
void __cdecl d2_ShowTaschendiebstahlDialog(unsigned char*);
void __cdecl d2_ShowPersonalbuch(unsigned char*, char*);
void __cdecl d2_RunDiebesgildeInfoDialog(unsigned char*);
void __cdecl d2_OpenMeisterbriefDialog(unsigned char*);

/* ADDRESS: GOLDDE 0x00592cc0 */
void __cdecl d2_RunRaeuberlagerMenu(unsigned char* building)
{
	int a;
	int b;
	int c;
	int d;
	int e;
	int f;
	int g;
	int r;
	Shop* t;

	d = 0;
	a = 0;
	b = 0;
	c = 0;
	g = 0;
	f = 0;
	e = 0;
	d2_ClearStatusTextSlots();
	t = &((Shop*)lpGebaeudePROT)[building[0]];
	if (t->x247 >= 2) {
		r = d3_FindSceneObject(0, 0xc0, 0, s_6ab260);
		if (r != 0) {
			d3_SetSubtreeVisible(r, 1);
		}
	}
	else {
		r = d3_FindSceneObject(0, 0xc0, 0, s_6ab260);
		if (r != 0) {
			d3_SetSubtreeVisible(r, 0);
		}
	}
	if (main_RunFrameLoop((void*) d2_RunRaeuberlagerMenu, 0x67fff) != 0) {
		do {
			if (d2_SelectedEntityUiFlags & 0x200) {
				a = RegisterStatusText(s_6ab24c, g_14abaa4, 0x17);
				b = RegisterStatusText(s_6aa544, g_14abaf4, 0x17);
				if (t->x247 >= 2) {
					c = RegisterStatusText(s_6aa584, g_14ad108, 0x17);
				}
				d = RegisterStatusText(s_6ab230, g_14ad178, 0x17);
				e = RegisterStatusText(s_6ab214, g_14a7c98, 0x16);
			}
			if (d2_SelectedEntityUiFlags & 0x400) {
				f = RegisterStatusText(s_6aa34c, g_14a7b50, 0xc);
				g = RegisterStatusText(s_6a9924, g_14a7d28, 0x16);
			}
			if (sv_ClickedObjekt != 0) {
				if (sv_ClickedObjekt == a) {
					d2_StartEinbruchTargetSelect(building);
				}
				else if (sv_ClickedObjekt == b) {
					d2_StartThievesGuildSpyPicker(building);
				}
				else if (sv_ClickedObjekt == c) {
					d2_OpenAngriffDialog(building);
				}
				else if (sv_ClickedObjekt == d) {
					d2_ShowTaschendiebstahlDialog(building);
				}
				else if (sv_ClickedObjekt == f) {
					d2_ShowPersonalbuch(building, s_6aa34c);
				}
				else if (sv_ClickedObjekt == e) {
					d2_RunDiebesgildeInfoDialog(building);
				}
				else if (sv_ClickedObjekt == g) {
					d2_OpenMeisterbriefDialog(building);
				}
			}
		} while (main_RunFrameLoop((void*) d2_RunRaeuberlagerMenu, 0x67fff) != 0);
	}
}
