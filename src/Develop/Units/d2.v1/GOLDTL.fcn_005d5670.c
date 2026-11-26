

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
	char pad60[0x98];
};

extern pos14_7f4c00 gm_GameTime;
extern char s_6acc74[];
extern int g_100f1dc;
extern int g_14ce8e0;
#include "client_dialog_state.h"

int __cdecl fcn_004f6470(int, char*, unsigned short);
int __cdecl fcn_00470820(int, int, char*);
void __cdecl d2_SetOverlayAnimation(int, int);
void __cdecl d2_CenterDialogWindows(int);
void __cdecl d2_SetForm(int, int);
int __cdecl io_AppendText(int, ...);
unsigned short __cdecl gm_RandomMod(int);
void __cdecl gm_AddTime(pos14_7f4c00*, int, int, int);
int __cdecl cm_SendCopyEntityData(struct msg*);
int __cdecl cm_GetCommandStatus(int);
char* __cdecl cm_GetCommandResult(int);
void __cdecl fcn_00535960(void);
void __cdecl io_FormatTextBuffer(char*, int, ...);
void __cdecl fcn_00526120(char*, int);
void __cdecl cm_RequestCopyEntityData(int, int, int, int);
void __cdecl cm_RequestModifyHealth(int, int);
int __cdecl main_RunFrameLoop(void*, int);
void __cdecl d2_DestroyForm(int);

int __cdecl fcn_005d5670(unsigned char* e, unsigned char* o)
{
	int chance;
	int dlg;
	pos14_7f4c00 pos;
	struct msg m;
	char text[0x100];
	char buf[0x80];
	int result;
	int h;
	char* p;

	if (e == 0 || o == 0) {
		return 0;
	}
	if (e[2] != 6 && e[2] != 7) {
		return 0;
	}
	chance = fcn_004f6470(*(int*) (o + 4), buf, *(unsigned short*) e);
	dlg = fcn_00470820(0, 0, s_6acc74);
	d2_SetOverlayAnimation(0, 0);
	d2_CenterDialogWindows(dlg);
	d2_SetForm(dlg, 1);
	io_AppendText(0x1d57, *(unsigned short*) o, *(unsigned short*) o, *(unsigned short*) o,
		*(unsigned short*) o, 2);
	io_AppendText(0x1d58);
	g_100f1dc = -1;
	result = 0;
	do {
		if (g_100f1dc != -1) {
			if (g_100f1dc == 2) {
				if (chance >= gm_RandomMod(8)) {
					pos = gm_GameTime;
					gm_AddTime(&pos, 0x60, 0, 0);
					memset(&m, 0, sizeof(m));
					m.b4 = 0x45;
					m.b36 = 2;
					m.f8 = *(int*) (e + 4);
					m.pos = gm_GameTime;
					m.fc = *(int*) (e + 4);
					m.f58 = *(int*) (e + 4);
					m.f5c = *(int*) (o + 4);
					h = cm_SendCopyEntityData(&m);
					while (h != -1 && cm_GetCommandStatus(h) == 0) {
						fcn_00535960();
					}
					p = cm_GetCommandResult(h);
					while (!(*(int*) (e + 0x1c8) & 0x100) && *(int*) (p + 0x70) != -1) {
						fcn_00535960();
					}
					if (*(int*) (e + 0x1c8) & 0x100) {
						io_FormatTextBuffer(text, 0x1d5a, *(unsigned short*) o, &pos);
						fcn_00526120(text, 0);
					}
					result = 1;
					g_774654 = 1;
				} else {
					cm_RequestCopyEntityData(*(int*) (e + 4), *(int*) (o + 4), -0x1a, 1);
					cm_RequestModifyHealth(*(int*) (e + 4), -2);
					io_FormatTextBuffer(text, 0x1d59, *(unsigned short*) o);
					fcn_00526120(text, 0);
					result = 0;
					g_774654 = 1;
				}
			} else if (g_100f1dc == 1) {
				result = 0;
				g_774654 = 1;
			}
		}
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
		}
	} while (main_RunFrameLoop((void*) fcn_005d5670, 0x657c7) != 0);
	d2_DestroyForm(dlg);
	return result;
}
