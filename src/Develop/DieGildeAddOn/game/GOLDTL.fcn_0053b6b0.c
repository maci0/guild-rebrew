#include "game_data.h"
#include "client_dialog_state.h"
#include "Develop/Units/d2.v1/d2_gui.h"
extern float g_67d368;
extern int g_14ce8e0, g_67d370, g_7e2468;
extern char g_6b5c60[], g_7e23e8;
void __cdecl ch_SetVisible(void* obj, int value);
void __cdecl fcn_00402b00(void* obj, void* dev);
void __cdecl fcn_004030e0(void* obj);
void* __cdecl ch_CreateAtPosition(char* name, void* pos);
void __cdecl fcn_0040c120(void* obj, int mode, int value);
void* __cdecl evt_LoadGfxScript(char* script);
void __cdecl fcn_00428340(void* obj, int argc, ...);
void* __cdecl fcn_00445600(void* dev, int flags, void* ptr, char* name);
void __cdecl fcn_00455350(void* dev, void* pos, void* out);
int __cdecl fcn_00469c30(int x, int y, int a3);
void __cdecl fcn_0046b2b0(int kind);
int __cdecl fcn_004fdec0(char* name);
int __cdecl gm_MapEntityStatRange(int arg);
int __cdecl fcn_005373e0(int task, int time);

/* ADDRESS: GOLDTL 0x0053b6b0 */
unsigned int __cdecl fcn_0053b6b0(int a0)
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
	int prev;
	int selected;
	int i;
	char* p;
	float d;

	idx = gm_MapEntityStatRange(a0);

	dev = fcn_00445600(0, 0x100, 0, "dummy_SPIELER");
	if (dev != 0) {
		fcn_00455350(dev, (char*) dev + 0x4c, pos);
	}

	d = g_67d368;
	id1 = fcn_00469c30((int) (d * 150.0f + d * 330.0f),
		(int) (d * 370.0f), 0x1a);
	*(int*) ((char*) g_1015ea0 + id1 * 0x2f4 + 0x5c) = 1;
	*(int*) ((char*) g_1015ea0 + id1 * 0x2f4 + 0x1d0) = 3;

	d = g_67d368;
	id2 = fcn_00469c30((int) (d * 330.0f),
		(int) (d * 370.0f), 0x1b);
	*(int*) ((char*) g_1015ea0 + id2 * 0x2f4 + 0x5c) = 1;
	*(int*) ((char*) g_1015ea0 + id2 * 0x2f4 + 0x1d0) = 3;

	d = g_67d368;
	id3 = fcn_00469c30((int) (d * 70.0f + d * 330.0f),
		(int) (d * 45.0f + d * 370.0f), 0x51b);
	*(int*) ((char*) g_1015ea0 + id3 * 0x2f4 + 0x5c) = 1;
	*(int*) ((char*) g_1015ea0 + id3 * 0x2f4 + 0x1d0) = 3;

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

	prev = -1;
	selected = 0;
	while (fcn_005373e0(0x53b6b0, 0x12d6)) {
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
			selected = 0;
		}
		if (g_14cf950 != 'N'
			&& (g_100f1dc == -1 || g_67d370 != id1)) {
			if (g_14cf950 != 'J'
				&& (g_100f1dc == -1 || g_67d370 != id2)) {
				if (g_14cf950 == 0x1c
					|| (g_100f1dc != -1 && g_67d370 == id3)) {
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
				d = g_67d368;
				fcn_00428340(view, 6,
					(int) pos[0],
					(int) pos[1] + 0x14,
					(int) pos[2],
					0x28, 0x5a, g_6b5c60);
			}
			if (obj != 0) {
				fcn_0040c120(obj, 0x38, 0);
				do {
					if (!fcn_005373e0(0, 0x12d6)) {
						break;
					}
				} while (*(int*) ((char*) obj + 0x128) != 0);
				fcn_004030e0(obj);
			}
			if (g_7e23e8 != 0) {
				idx = idx % count2;
				if (idx <= -1) {
					idx = count2 - 1;
				}
				p = &frauen[idx][0];
			} else {
				idx = idx % count;
				if (idx <= -1) {
					idx = count - 1;
				}
				p = &maenner[idx][0];
			}
			i = 0;
			do {
				name[i] = p[i];
				i += 1;
			} while (p[i - 1] != 0);
			obj = 0;
			i = 0;
			do {
				*(char*) (0x7e2435 + i) = name[i];
				i += 1;
			} while (name[i - 1] != 0);
			g_7e2468 = fcn_004fdec0(name) + 0x639;
			obj = ch_CreateAtPosition(name, pos);
			fcn_00402b00(obj, dev);
			ch_SetVisible(obj, 0);
			*(unsigned char*) (*(int*) ((char*) obj + 0x34) + 0x215) &= 0xfe;
			*(unsigned char*) ((char*) obj + 0x8c) |= 8;
			fcn_0040c120(obj, 0x38, 1);
			prev = idx;
		}
	}
	if (obj != 0) {
		fcn_004030e0(obj);
	}
	fcn_0046b2b0(id2);
	fcn_0046b2b0(id1);
	fcn_0046b2b0(id3);
	return selected;
}
