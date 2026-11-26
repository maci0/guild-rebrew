


#include <string.h>

// SIZE 0x50
typedef struct {
	int a;
	int size;
	__int64 cd;
	int kind;
	int pad14[15];
} Req;

extern __int64 g_666018;
extern char g_6b5c60[];
extern char s_6acdac[];
#include "Develop/DieGildeAddOn/game/game_data.h"
#include "client_dialog_state.h"

unsigned short __cdecl gm_RandomMod(int);
unsigned char* __cdecl gm_LookupEntityRecordById(int);
void __cdecl cm_RequestCopyEntityData(int, int, int, int);
void __cdecl fcn_004c6ae0(int, int);
void __cdecl io_FormatTextBuffer(char*, int, ...);
void __cdecl fcn_00545d40(int, int, char*, int, int, char*);
unsigned char* __cdecl fcn_005cd440(Req*, char*, int, int);
int __cdecl fcn_00470820(int, int, char*);
void __cdecl d2_SetOverlayAnimation(int, int);
void __cdecl d2_CenterDialogWindows(int);
void __cdecl d2_SetForm(int, int);
int __cdecl io_AppendText(int, ...);
int __cdecl d2_GetWindowListItem(int, int, int);
int __cdecl d2_CheckActionBlocker(unsigned char*, int);
void __cdecl fcn_00526120(char*, int);
int __cdecl main_RunFrameLoop(void*, int);
void __cdecl fcn_00471e30(int);

int __cdecl gm_HandleFriedenStiften(unsigned char* e, unsigned char* ctx)
{
	int result;
	int dlg;
	int cancel;
	int ok;
	Req req;
	char text[0x200];
	unsigned char* o1;
	unsigned char* o2;
	int a;
	int b;
	int id;

	if (e[2] != 6) {
		a = gm_RandomMod(0x28) + 0xf;
		b = gm_RandomMod(0x28) + 0xf;
		if (*(int*) (e + 0x194) < 3) {
			return 0x20;
		}
		o1 = gm_LookupEntityRecordById(*(int*) (ctx + 0x214));
		if (o1 == 0) {
			return 0x60;
		}
		o2 = gm_LookupEntityRecordById(*(int*) (ctx + 0x218));
		if (o2 == 0) {
			return 0x60;
		}
		cm_RequestCopyEntityData(*(int*) (o1 + 4), *(int*) (o2 + 4), a, 1);
		cm_RequestCopyEntityData(*(int*) (o2 + 4), *(int*) (o1 + 4), b, 1);
		fcn_004c6ae0(*(int*) (e + 4), -3);
		if (o1[2] == 6 || o1[2] == 7) {
			io_FormatTextBuffer(text, 0x1de8, *(unsigned short*) o2, *(unsigned short*) e);
			fcn_00545d40(*(int*) (o1 + 4), *(int*) (o1 + 4), text, 0, 0x5ec, g_6b5c60);
		}
		if (o2[2] == 6 || o2[2] == 7) {
			io_FormatTextBuffer(text, 0x1de8, *(unsigned short*) o1, *(unsigned short*) e);
			fcn_00545d40(*(int*) (o2 + 4), *(int*) (o2 + 4), text, 0, 0x5ec, g_6b5c60);
		}
		return 0x10;
	}
	result = 0;
	memset(&req, 0, sizeof(req));
	req.size = 0x400;
	req.kind = 6;
	req.cd = g_666018;
	io_FormatTextBuffer(text, 0x1de4);
	o1 = fcn_005cd440(&req, text, 0, 0);
	if (o1 == 0) {
		return 0;
	}
	io_FormatTextBuffer(text, 0x1de5, *(unsigned short*) o1);
	o2 = fcn_005cd440(&req, text, 0, 0);
	if (o2 == 0) {
		return 0;
	}
	dlg = fcn_00470820(0, 0, s_6acdac);
	d2_SetOverlayAnimation(0, 0);
	d2_CenterDialogWindows(dlg);
	d2_SetForm(dlg, 1);
	id = io_AppendText(0x1de6, 3, *(unsigned short*) o1, *(unsigned short*) o2);
	ok = d2_GetWindowListItem(dlg, 1, id);
	cancel = d2_GetWindowListItem(dlg, 1, id + 1);
	g_100f1dc = -1;
	do {
		if (g_100f1dc != -1) {
			if (d2_CurrentElementId == ok) {
				if (d2_CheckActionBlocker(e, 3)) {
					a = gm_RandomMod(0x28) + 0xf;
					b = gm_RandomMod(0x28) + 0xf;
					cm_RequestCopyEntityData(*(int*) (o1 + 4), *(int*) (o2 + 4), a, 1);
					cm_RequestCopyEntityData(*(int*) (o2 + 4), *(int*) (o1 + 4), b, 1);
					fcn_004c6ae0(*(int*) (e + 4), -3);
					io_FormatTextBuffer(text, 0x1de7, *(unsigned short*) o1, *(unsigned short*) o2);
					fcn_00526120(text, 0);
					if (o1[2] == 6 || o1[2] == 7) {
						io_FormatTextBuffer(text, 0x1de8, *(unsigned short*) o2, *(unsigned short*) e);
						fcn_00545d40(*(int*) (o1 + 4), *(int*) (o1 + 4), text, 0, 0x5ec, 0);
					}
					if (o2[2] == 6 || o2[2] == 7) {
						io_FormatTextBuffer(text, 0x1de8, *(unsigned short*) o1, *(unsigned short*) e);
						fcn_00545d40(*(int*) (o2 + 4), *(int*) (o2 + 4), text, 0, 0x5ec, 0);
					}
					g_774654 = 1;
					result = 1;
				}
			} else if (d2_CurrentElementId == cancel) {
				g_774654 = 1;
			}
		}
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
		}
	} while (main_RunFrameLoop((void*) gm_HandleFriedenStiften, 0x657c7) != 0);
	fcn_00471e30(dlg);
	return result;
}
