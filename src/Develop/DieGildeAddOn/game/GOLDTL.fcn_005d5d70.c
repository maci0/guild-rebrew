

#include <string.h>

// SIZE 0xf8
#include "client_types.h"
struct msg {
	int f0;
	char b4;
	char pad5[3];
	int f8;
	int fc;
	char pad10[0x18];
	pos14_7f4c00 pos;
	char b36;
	char pad37[0x21];
	int f58;
	int f5c;
	unsigned short w60;
	unsigned short w62;
	char pad64[0x94];
};

// SIZE 0x21c
#include "Develop/DieGildeAddOn/game/entity_record.h"





extern pos14_7f4c00 gm_GameTime;

#include "Develop/DieGildeAddOn/game/game_player.h"
extern char s_6ac494[];
#include "Develop/DieGildeAddOn/game/game_data.h"
#include "client_dialog_state.h"

void __cdecl io_FormatTextBuffer(char*, int, ...);
void __cdecl fcn_00526120(char*, int);
int __cdecl fcn_00470820(int, int, char*);
void __cdecl d2_SetOverlayAnimation(int, int);
void __cdecl d2_CenterDialogWindows(int);
void __cdecl d2_SetForm(int, int);
int __cdecl io_AppendText(int, ...);
void __cdecl fcn_005c9220(int*);
int __cdecl d2_CheckActionBlocker(ENTITY_RECORD*, int);
unsigned short __cdecl gm_RandomMod(int);
int __cdecl cm_SendCopyEntityData(struct msg*);
int __cdecl cm_GetCommandStatus(int);
void __cdecl fcn_00535960(void);
void __cdecl cm_RequestModifyHealth(int, int);
int __cdecl main_RunFrameLoop(void*, int);
void __cdecl d2_DestroyForm(int);

int __cdecl d2_ShowDuelChallengeDialog(unsigned char* e)
{
	int dlg;
	char text[0x100];
	int result;
	int kind;
	unsigned short a;
	unsigned short b;
	int h;

	result = 0;
	if (*(int*) (e + 0x1c8) & 0x400) {
		io_FormatTextBuffer(text, 0x1d7f, *(unsigned short*) e);
		fcn_00526120(text, 0);
		return 0;
	}
	kind = (e[9] != 0) + 0x1d68;
	dlg = fcn_00470820(0, 0, s_6ac494);
	d2_SetOverlayAnimation(0, 0);
	d2_CenterDialogWindows(dlg);
	d2_SetForm(dlg, 1);
	io_AppendText(0x1d67, *(unsigned short*) e, 2, *(unsigned short*) e, kind, *(unsigned short*) e);
	{
		int arr[6];

		memset(arr, 0xff, sizeof(arr));
		arr[0] = dlg;
		arr[1] = 2;
		arr[2] = 3;
		arr[3] = 4;
		arr[4] = 4;
		arr[5] = 4;
		fcn_005c9220(arr);
	}
	g_100f1dc = -1;
	do {
		if (g_100f1dc != -1) {
			if (g_100f1dc == 2) {
				if (d2_CheckActionBlocker(((ENTITY_RECORD*)&((ENTITY_RECORD_VIEW*)g_7f4ca0)[g_774970]), 2)) {
					struct msg m;

					a = gm_RandomMod(9) + 0x1d76;
					b = gm_RandomMod(9) + 0x1d6d;
					memset(&m, 0, sizeof(m));
					m.f8 = ((ENTITY_RECORD_VIEW*)g_7f4ca0)[g_774970].entity_id;
					m.pos = gm_GameTime;
					m.b4 = 0x47;
					m.b36 = 2;
					m.w60 = b;
					m.w62 = a;
					m.f5c = *(int*) (e + 4);
					m.fc = ((ENTITY_RECORD_VIEW*)g_7f4ca0)[g_774970].entity_id;
					m.f58 = ((ENTITY_RECORD_VIEW*)g_7f4ca0)[g_774970].entity_id;
					h = cm_SendCopyEntityData(&m);
					while (cm_GetCommandStatus(h) == 0) {
						fcn_00535960();
					}
					cm_RequestModifyHealth(((ENTITY_RECORD_VIEW*)g_7f4ca0)[g_774970].entity_id, -2);
					io_FormatTextBuffer(text, 0x1d6a, b, *(unsigned short*) e, a);
					fcn_00526120(text, 0);
					g_774654 = 3;
					result = 1;
				}
			} else if (g_100f1dc == 1) {
				g_774654 = 2;
			}
		}
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
		}
	} while (main_RunFrameLoop((void*) d2_ShowDuelChallengeDialog, 0x657c7) != 0);
	d2_DestroyForm(dlg);
	return result;
}
