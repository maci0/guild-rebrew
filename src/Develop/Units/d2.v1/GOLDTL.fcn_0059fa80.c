#include <string.h>
#include "client_data.h"

extern char* g_772500;
extern int d2_CurrentWindowId;
extern char* g_77255c;
#include "client_dialog_state.h"
#include "Develop/DieGildeAddOn/game/game_player.h"
extern int d2_CurrentElementId;




extern int g_100f1dc;
extern int g_14abc88;
extern int g_14abc90;
extern int g_14abc94;
extern int g_14ce8e0;
extern int g_666018;
extern int g_66601c;

int __cdecl d2_LoadForm(int a, int b, const char* name);
void __cdecl d2_SetForm(int dialog, int slot);
void __cdecl d2_InitWindowBounds(int screen);
void __cdecl d2_CenterDialogWindows(int dialog);
void __cdecl d2_SetOverlayAnimation(int a, int b);
void __cdecl io_AppendText(const char* text, int value);
void __cdecl d2_CreateButtonRow(int screen, int a, int* out, int count, int b,
	int c);
void __cdecl d2_BuildPersonStatusDesc(void* desc);
void __cdecl d2_DrawPersonCard(int x, int y, int screen, int id, void* desc,
	int flag);
int __cdecl gm_LookupEntityRecordById(unsigned int id);
int __cdecl he_StartHandlungSearch(int a, int b, int c);
void __cdecl d2_SetElementEnabled(int value, int flag);
char* __cdecl io_FormatTextBuffer(char* buf, int id, ...);
int __cdecl d2_ShowModalMessageBox(char* text, int flag);
void* __cdecl d2_OpenTargetPicker(void* desc, int a, int b, int c);
int __cdecl d2_CheckActionBlocker(void* p, int flag);
int __cdecl cm_SendSetHE(int mode, int arg);
void __cdecl gm_ModifyHealth(int handle, int value);
void __cdecl cm_RequestCopyEntityData(int a, int b, int c, int d);
int __cdecl cm_GetCommandStatus(int handle);
int __cdecl main_RunFrameLoop(int func, int id);

/* ADDRESS: GOLDTL 0x0059fa80 */
void __cdecl fcn_0059fa80(int a0, unsigned short* a1, int a2)
{
	unsigned int v3;
	unsigned int v4;
	unsigned int v11;
	int pair[2];
	int id_a;
	int id_b;
	int v5;
	int dialog;
	int v9;
	int v7;
	unsigned short* v6;
	unsigned short* v10;
	unsigned int flags[20];
	char text[512];
	char buf[64];
	char title[512];
	char cmd[0x40];

	v7 = a2;
	v6 = a1;
	v4 = *(unsigned int*) (a2 + 4);
	v3 = *(unsigned int*) &a1[2];
	dialog = d2_LoadForm(0, 0, "locations\\wohnsitz\\geliebte2");
	d2_SetForm(dialog, 0);
	d2_InitWindowBounds(d2_CurrentWindowId);
	d2_CenterDialogWindows(dialog);
	d2_SetOverlayAnimation(0, 0);
	d2_SetForm(dialog, 1);
	io_AppendText("$C$Z$[%1N3$]", *v6);
	d2_SetForm(dialog, 3);
	d2_CreateButtonRow(d2_CurrentWindowId, 0, pair, 2, g_14abc90, g_14abc94);
	id_a = pair[0];
	id_b = pair[1];
	d2_SetForm(dialog, 2);
	*(int*) (cmd + 0x10) = (*(int*) (g_77255c + 0xc) - (int) *(short*) (g_772500 + 0x1ebd8)) / 2;
	*(int*) (cmd + 0x14) = 0x19;
	*(unsigned int*) cmd = (unsigned int) v6;
	*(unsigned int*) (cmd + 0x30) = 0;
	d2_BuildPersonStatusDesc(cmd);
	d2_DrawPersonCard(*(int*) (cmd + 0x10), *(int*) (cmd + 0x14), d2_CurrentWindowId, 0x54, cmd, 1);
	g_100f1dc = -1;
	for (;;) {
		v5 = gm_LookupEntityRecordById(v3) && he_StartHandlungSearch(1, 1, v4);
		if (v5 && *(int*) (v7 + 0xbc) < gm_GameTime.a) {
			d2_SetElementEnabled(id_b, 1);
		} else {
			d2_SetElementEnabled(id_b, 0);
		}
		if (!g_14ce8e0 && v5) {
			if (g_100f1dc != -1) {
				if (d2_CurrentElementId == id_a) {
					if (!*(char*) ((unsigned int) g_774970 * 0x21c + 0x7f4ca9)) {
						io_FormatTextBuffer(text, 0x1a57, *v6);
					} else {
						io_FormatTextBuffer(text, 0x1a58, *v6);
					}
					if (d2_ShowModalMessageBox(text, 1)) {
						*(pos14_7f4c00*) (v7 + 0x52) = gm_GameTime;



						*(int*) (v7 + 0xbc) = gm_GameTime.a;
						v9 = cm_SendSetHE(1, v7);
						while (v9 != -1 && !cm_GetCommandStatus(v9)) {
							main_RunFrameLoop(0, 0x20007);
						}
						g_774654 = 1;
					}
			} else if (d2_CurrentElementId == id_b) {
					memset(flags, 0, sizeof(flags));
					flags[1] = 0x20400;
					flags[4] = 6;
					flags[2] = g_666018;
					flags[3] = g_66601c;
					io_FormatTextBuffer(cmd, 0x1a53);
					io_FormatTextBuffer(buf, 0x1a54);
					v10 = (unsigned short*) d2_OpenTargetPicker(flags,
						g_14abc88, 0, 0);
					if (v10 != 0) {
						io_FormatTextBuffer(title, 0x1a5b, 2, *v6,
							*v10);
						if (d2_ShowModalMessageBox(title, 1) && (v11 = g_774970,
							d2_CheckActionBlocker((char*) (v11 * 0x21c + 0x7f4ca0), 2))) {
							*(int*) (v7 + 0xbc) = gm_GameTime.a;
							cm_SendSetHE(3, v7);
							gm_ModifyHealth(*(unsigned int*) (a0 + 4),
								0xfffffffe);
							cm_RequestCopyEntityData(*(unsigned int*) &v10[2],
								*(unsigned int*) &v6[2], 0xffffffdf, 1);
							g_774654 = 1;
						}
					}
				}
			}
		} else {
			g_774654 = 1;
		}
		if (!main_RunFrameLoop(0x59fa80, 0x677c7)) {
			d2_DestroyForm(dialog);
			return;
		}
	}
}
