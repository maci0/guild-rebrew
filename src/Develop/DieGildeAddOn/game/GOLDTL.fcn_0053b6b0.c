#include <string.h>
#include "game_data.h"
#include "client_dialog_state.h"
#include "Develop/Units/d2.v1/d2_gui.h"
#include "Develop/DieGildeAddOn/game/game_data.h"
extern int g_14ce8e0, d2_CurrentElementId, g_7e2468;
extern char g_6b5c60[], g_7e23e8;
void __cdecl ch_SetVisible(void* obj, int value);
void __cdecl ch_SetToDummy(void* obj, void* dev);
void __cdecl ch_DestroyCharacter(void* obj);
void* __cdecl ch_CreateAtPosition(char* name, void* pos);
void __cdecl ch_CreateAction(void* obj, int mode, int value);
void* __cdecl evt_LoadGfxScript(char* script);
void __cdecl fcn_00428340(void* obj, int argc, ...);
void* __cdecl d3_FindSceneObject(void* dev, int flags, void* ptr, char* name);
void __cdecl d3_TransformPoint(void* dev, void* pos, void* out);
int __cdecl fcn_00469c30(int x, int y, int a3);
void __cdecl d2_DestroyElement(int kind);
int __cdecl gm_FindHeadIconIndex(char* name);
int __cdecl gm_MapEntityStatRange(int arg);
int __cdecl main_RunFrameLoop(int task, int time);

/* ADDRESS: GOLDTL 0x0053b6b0 */
unsigned int __cdecl fcn_0053b6b0(int jobCode)
{
	float pos[4];
	char name[0x20];
	char maenner[17][0x20] = {
		"patrizier_MANN2", "wirt_DICKER", "arbeiter_MANN", "wirt3_MANN",
		"wirt2_DICKER", "buerger_MANN", "buerger2_MANN", "domherr_KUTTE",
		"buerger3_DICKER", "patrizier_MANN2", "offizier_SOLDAT", "DIEB2_KUTTE",
		"raeubermeister_SOLDAT", "Nekromant_MEISTER", "zigeunermeister_MANN3",
		"schneider3_DICKER"
	};
	char frauen[17][0x20] = {
		"patrizierin_FRAU", "handwerkerin3_FRAU", "handwerkerin2_FRAU",
		"handwerkerin_FRAU", "magd_FRAU", "buergerin3_FRAU", "Bauerin_FRAU",
		"minerin2_FRAU", "buergerin2_FRAU", "buergerin2_FRAU",
		"buergerin_FRAU", "arbeiterin_FRAU", "minerin_FRAU",
		"feldarbeiterin_FRAU", "zigeunerin_FRAU", "schneiderin3_FRAU"
	};
	void* view;
	void* obj;
	void* dev;
	int id1;
	int id2;
	int id3;
	int count;
	int count2;
	int idx;
	int prev = -1;
	int selected = 0;
	char* p;

	idx = gm_MapEntityStatRange(jobCode);

	dev = d3_FindSceneObject(0, 0x100, 0, "dummy_SPIELER");
	if (dev != 0) {
		d3_TransformPoint(dev, (char*) dev + 0x4c, pos);
	}

	id1 = fcn_00469c30((int) (d2_UiScale * 150.0f + d2_UiScale * 330.0f),
		(int) (d2_UiScale * 370.0f), 0x1a);
	((D2_CONTROL_TL*) ((char*) g_1015ea0))[id1].value_05c = 1;
	((D2_CONTROL_TL*) ((char*) g_1015ea0))[id1].flags_1d0 = 3;

	id2 = fcn_00469c30((int) (d2_UiScale * 330.0f),
		(int) (d2_UiScale * 370.0f), 0x1b);
	((D2_CONTROL_TL*) ((char*) g_1015ea0))[id2].value_05c = 1;
	((D2_CONTROL_TL*) ((char*) g_1015ea0))[id2].flags_1d0 = 3;

	id3 = fcn_00469c30((int) (d2_UiScale * 70.0f + d2_UiScale * 330.0f),
		(int) (d2_UiScale * 45.0f + d2_UiScale * 370.0f), 0x51b);
	((D2_CONTROL_TL*) ((char*) g_1015ea0))[id3].value_05c = 1;
	((D2_CONTROL_TL*) ((char*) g_1015ea0))[id3].flags_1d0 = 3;

	count = 0;
	if (maenner[0][0] != 0) {
		p = &maenner[0][0];
		do {
			p += 0x20;
			count += 1;
		} while (*p != 0);
	}
	count2 = 0;
	if (maenner[0][0] != 0) {
		p = &maenner[0][0];
		do {
			p += 0x20;
			count2 += 1;
		} while (*p != 0);
	}

	obj = 0;



	while (main_RunFrameLoop(0x53b6b0, 0x12d6)) {
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
			selected = 0;
		}
		if (g_14cf950 != 'N'
			&& (g_100f1dc == -1 || d2_CurrentElementId != id1)) {
			if (g_14cf950 != 'J'
				&& (g_100f1dc == -1 || d2_CurrentElementId != id2)) {
				if (g_14cf950 == 0x1c
					|| (g_100f1dc != -1 && d2_CurrentElementId == id3)) {
					g_774654 = 1;
					selected = 1;
				}
			} else {
				idx -= 1;
			}
		} else {
			idx += 1;
		}
		if (obj != 0) {
			*(unsigned char*) ((char*) obj + 0x8c) |= 8;
		}
		if (prev != idx) {
			view = evt_LoadGfxScript("Effekte/choose_character.esc");
			if (view != 0) {
				fcn_00428340(view, 6,
					(int) pos[0],
					(int) pos[1] + 0x14,
					(int) pos[2],
					0x28, 0x5a, g_6b5c60);
			}
			if (obj != 0) {
				ch_CreateAction(obj, 0x38, 0);
				do {
					if (!main_RunFrameLoop(0, 0x12d6)) {
						break;
					}
				} while (*(int*) ((char*) obj + 0x128) != 0);
				ch_DestroyCharacter(obj);
			}
			if (g_7e23e8 == 0) {
				idx = idx % count;
				if (idx < 0) {
					idx = count - 1;
				}
				strcpy(name, maenner[idx]);
			} else {
				idx = idx % count2;
				if (idx < 0) {
					idx = count2 - 1;
				}
				strcpy(name, frauen[idx]);
			}
			obj = 0;
			strcpy((char*) 0x7e2435, name);
			g_7e2468 = gm_FindHeadIconIndex(name) + 0x639;
			obj = ch_CreateAtPosition(name, pos);
			ch_SetToDummy(obj, dev);
			ch_SetVisible(obj, 0);
			*(unsigned char*) (*(int*) ((char*) obj + 0x34) + 0x215) &= 0xfe;
			*(unsigned char*) ((char*) obj + 0x8c) |= 8;
			ch_CreateAction(obj, 0x38, 1);
			prev = idx;
		}
	}
	if (obj != 0) {
		ch_DestroyCharacter(obj);
	}
	d2_DestroyElement(id2);
	d2_DestroyElement(id1);
	d2_DestroyElement(id3);
	return selected;
}
