#include <string.h>
#include "Develop/DieGildeAddOn/game/entity_record.h"
#include "client_types.h"
#include "Develop/DieGildeAddOn/game/game_data.h"

extern pos14_7f4c00 gm_GameTime;

extern int d2_CurrentWindowId;
extern int g_774654;
extern char* g_77255c;

int __cdecl fcn_00470820(int, int, char*);
void __cdecl d2_CenterDialogWindows(int);
int __cdecl d2_SetForm(int, int);
void __cdecl d2_DestroyForm(int);
int __cdecl io_AppendText(int, ...);
int __cdecl main_RunFrameLoop(void*, int);
int __cdecl gm_GetOppositeStatIndex(int);
float __cdecl gm_CalcActionCompletionTime(int, int*);
int __cdecl gm_MapEntityStatRange(int);
void __cdecl fcn_005340f0(int);
void __cdecl fcn_00525ef0(void);
char* __cdecl he_StartHandlungSearch(int, int, int, int, int);
void __cdecl gm_ModifyHealth(int, int);
int __cdecl d2_AddWindowValueGauge(int, int, int, int, int, int, int, int);
void __cdecl d2_SetElementValue(int, ...);
void __cdecl gm_AddTime(void*, int, int, int);
void __cdecl cm_SendCopyEntityData(char*);
void __cdecl io_FormatTextBuffer(char*, int, int);
int __cdecl fcn_00526120(char*, int);
int __cdecl d3_EndCameraAndUiMode(void);
/* ADDRESS: GOLDTL 0x005a02b0 */
int __cdecl fcn_005a02b0(void)
{
	float grade;
	int info[4];
	char msg[0xf8];
	char text[0x100];
	char* slot;
	int h;
	int n;
	int mode;
	int d;
	int base;
	int r;

	slot = ((char*)&((ENTITY_RECORD*)g_7f4ca0)[(unsigned int) g_774970]);
	n = gm_GetOppositeStatIndex(*(unsigned char*) (slot + 0x164)) + 1;
	h = fcn_00470820(0, 0, (char*) 0x6aa80c);
	d2_CenterDialogWindows(h);
	d2_SetForm(h, 0);
	fcn_005340f0(d2_CurrentWindowId);
	fcn_00525ef0();
	grade = gm_CalcActionCompletionTime(g_774970, info);
	r = (int) he_StartHandlungSearch(2, 2, g_774970, 0, 0x26);
	if (r == 0 && grade >= 1.0 && n <= 6) {
		base = *(char*) (slot + 9) != 0 ? 0x18f : 0x130;
		gm_MapEntityStatRange(*(unsigned char*) (slot + 0x164));
		d2_SetForm(h, 1);
		io_AppendText(0x15bb);
		d2_SetForm(h, 2);
		io_AppendText(0x15bf, *(unsigned short*) slot, 4,
		    base + *(unsigned char*) (slot + 0x164) - 1);
		if (n % 2 != 0) {
			io_AppendText(0x15c0);
		}
		d2_SetForm(h, 3);
		io_AppendText(0x15c1);
	}
	else if (r != 0) {
		d2_SetForm(h, 1);
		io_AppendText(0x15bb);
		d2_SetForm(h, 2);
		if (*(char*) (slot + 9) != 0) {
			base = 0x18f;
		} else {
			base = 0x130;
		}
		io_AppendText(0x15bd, *(unsigned short*) slot,
		    base + *(unsigned char*) (slot + 0x164) - 1);
	}
	else {
		if (n >= 7) {
			d2_SetForm(h, 1); io_AppendText(0x15bb); d2_SetForm(h, 2);
			io_AppendText(0x15be, *(unsigned short*) slot);
		}
		else {
			d2_SetForm(h, 1); io_AppendText(0x15bb); d2_SetForm(h, 2);
			io_AppendText(0x15bc, *(unsigned short*) slot, info);
			d = d2_AddWindowValueGauge(0x1c,
			    *(int*) (g_77255c + 0x10) - 0x3c,
			    *(int*) (g_77255c + 0xc) - 0x40, 0, 0x64, 0x83,
			    0x42, d2_CurrentWindowId);
			d2_SetElementValue(d, 0, 0x64, (int) (grade * 100.0f));
		}
	}
	while (main_RunFrameLoop((void*) fcn_005a02b0, 0x677c7) != 0) {
		if ((mode = g_100f1dc) != -1 && grade >= 1.0) {
			if (mode == 2) {
				if (*(int*) (slot + 0x194) < 4) {
					io_FormatTextBuffer(text, 0x74, 4);
					fcn_00526120(text, 4);
				}
				else {
					gm_ModifyHealth(*(int*) (slot + 4), -4);
					memset(msg, 0, sizeof(msg));
					*(int*) (msg + 8) = *(int*) (slot + 4);
					msg[4] = 0x26;
					*(int*) (msg + 0xc) = -1;
					msg[0x36] = 9;
					*(int*) (msg + 0x58) = *(int*) (slot + 4);
					*(pos14_7f4c00*) (msg + 0x28) = gm_GameTime;
					gm_AddTime(msg + 0x28, 2, 0, 0);
					cm_SendCopyEntityData(msg);
					g_774654 = 1;
				}
			}
			else if (mode == 1) {
				g_774654 = 1;
			}
		}
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
		}
	}
	d2_DestroyForm(h);
	return d3_EndCameraAndUiMode();
}
