

#include <string.h>

typedef struct
{
	void* x0;
	char pad4[0xc];
	int x10;
	int x14;
	char pad18[0x18];
	int x30;
	int x34;
} Item;
// SIZE 0x38

typedef struct
{
	char pad[0x21c];
} Player;
// SIZE 0x21c

extern char gm_EntitySlotTable[];
extern char* d2_CurrentWindow;
extern char* d2_FileObjTable;
extern char* g_14a6554;
extern int d2_CurrentWindowId;
extern int d2_DialogButtonAction;
extern int io_RightButtonReleased;
#include "Develop/Units/d2.v1/client_dialog_state.h"
extern char s_6ab048[];

int __cdecl d2_LoadForm(int, int, char*);
void __cdecl d2_CenterDialogWindows(int);
void __cdecl d2_SetForm(int, int);
void __cdecl d2_InitWindowBounds(int);
void __cdecl d2_SetOverlayAnimation(int, int);
void __cdecl gm_GetKircheTop5(int*, int*);
void __cdecl d2_ClearWindowChildren(int, int);
int __cdecl io_AppendText(int, ...);
void __cdecl d2_BuildPersonStatusDesc(Item*);
void __cdecl d2_DrawPersonTile(int, int, int, Item*);
void __cdecl io_FormatTextBuffer(char*, int, ...);
void __cdecl d2_ShowWrappedText(char*, int, int, int, int);
int __cdecl main_RunFrameLoop(void*, int);
void __cdecl d3_EndCameraAndUiMode(void);
void __cdecl d2_DestroyForm(int);

void __cdecl d2_ShowKircheTop5(void)
{
	int dlg;
	int b[5];
	int a[5];
	int pb[5];
	int pa[5];
	char buf[0x200];
	Item items[5];
	int dirty;
	int i;
	int half;
	int x;
	int left;

	dlg = d2_LoadForm(0, 0, s_6ab048);
	d2_CenterDialogWindows(dlg);
	d2_SetForm(dlg, 0);
	d2_InitWindowBounds(d2_CurrentWindowId);
	d2_SetOverlayAnimation(0, 0);
	dirty = 1;
	d2_DialogButtonAction = -1;
	do {
		gm_GetKircheTop5(a, b);
		for (i = 0; i < 5; i++) {
			if (pa[i] != a[i] || pb[i] != b[i]) {
				dirty = 1;
			}
			pa[i] = a[i];
			pb[i] = b[i];
			items[i].x0 = 0;
			if (a[i] != 0xffff) {
				items[i].x0 = &((Player*)gm_EntitySlotTable)[a[i]];
			}
		}
		if (dirty != 0) {
			d2_SetForm(dlg, 1);
			d2_ClearWindowChildren(d2_CurrentWindowId, 1);
			io_AppendText(0x196b);
			half = *(int*) (d2_CurrentWindow + 0xc) / 2;
			x = half - *(short*) (d2_FileObjTable + 0x1ebd8) - 0x87;
			left = half - 0x64;
			for (i = 0; i < 5; i++) {
				items[i].x14 = i * 0x4c + 0x2c;
				items[i].x10 = x;
				items[i].x30 = items[i].x0 != 0;
				d2_BuildPersonStatusDesc(&items[i]);
				items[i].x30 = items[i].x0 != 0;
				d2_DrawPersonTile(items[i].x10, items[i].x14, d2_CurrentWindowId, &items[i]);
				if (items[i].x0 != 0) {
					io_FormatTextBuffer(buf, 0x196d, a[i]);
				}
				else {
					strcpy(buf, g_14a6554);
				}
				d2_ShowWrappedText(buf, left, i * 0x4c + 0x34, *(int*) (d2_CurrentWindow + 0xc) - left + 0x14, 0x53);
				io_FormatTextBuffer(buf, 0x196e, b[i]);
				d2_ShowWrappedText(buf, left, i * 0x4c + 0x4d, *(int*) (d2_CurrentWindow + 0xc) - left + 0x14, 0x53);
			}
			dirty = 0;
		}
		if (io_RightButtonReleased != 0) {
			d2_DialogCloseRequested = 1;
		}
	} while (main_RunFrameLoop((void*) d2_ShowKircheTop5, 0x677c7) != 0);
	d3_EndCameraAndUiMode();
	d2_DestroyForm(dlg);
}
