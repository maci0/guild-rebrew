#include <string.h>

#include "Develop/DieGildeAddOn/game/game_data.h"
#include "client_dialog_state.h"
extern int main_LoopFlags;

int __cdecl fcn_00470820(int, int, char*);
int __cdecl io_AppendText(char*, ...);
int __cdecl d2_GetWindowListItem(int, int, int);
void __cdecl d2_CenterDialogWindows(int);
void __cdecl fcn_00471e30(int);
int __cdecl main_RunFrameLoop(void*, int);
float __cdecl fcn_004ff210(unsigned short, int);
void __cdecl fcn_00471af0(int, int);
void* __cdecl fcn_005cd440(void*, char*, int, int);
void __cdecl fcn_004c4eb0(char*);
void __cdecl fcn_004c4ef0(char*);
void __cdecl fcn_004c4510(void*, int);
void __cdecl cm_AppendPacketFieldDelta(int, int, int, void*);
void __cdecl fcn_004c5360(void);
void __cdecl fcn_004c4fc0(char, int, int, short, int, char, char, char);

/* ADDRESS: GOLDTL 0x005b4660 */
void __cdecl d2_RunCharacterDebugDialog(char* e)
{
	int flags;
	int hKill;
	int hChild;
	int hMarriage;
	int hShow;
	char names[15][0x20] = { "DUMMY_NPC", "MEISTER_NPC",
		"POLITICIAN_NPC", "AI_NPC", "NPC", "PLAYER", "REMOTE_PLAYER",
		"RELATIVE_PLAYER", "USED_PLAYER", "INVISIBLE_NPC", "ESKORTE",
		"RICHTER", "TMP_NPC", "PEST", "DEAD_PLAYER" };
	char buf[0x50];
	int dialog;
	int i;
	int a;
	int b;
	int d;
	void* p;

	flags = main_LoopFlags;
	flags &= 0xffffffc7;
	dialog = fcn_00470820(0, 0, "misc\\Messagebox_BIG");
	io_AppendText("$Z$[%1N4$]$N$L", *(unsigned short*) e);
	io_AppendText("Mode:%s$A", names[*(unsigned char*) (e + 2)]);
	hKill = d2_GetWindowListItem(dialog, 0, io_AppendText("%it[Kill player]$A"));
	hShow = d2_GetWindowListItem(dialog, 0, io_AppendText("%it[Show He]$A"));
	hMarriage = d2_GetWindowListItem(dialog, 0, io_AppendText("%it[Marriage]$A"));
	hChild = d2_GetWindowListItem(dialog, 0, io_AppendText("%it[Get Child]$A"));
	d2_CenterDialogWindows(dialog);
	while (main_RunFrameLoop((void*) d2_RunCharacterDebugDialog, flags) != 0) {
		if (g_100f1dc != -1) {
			if (d2_CurrentElementId == hKill) {
				fcn_004ff210(*(unsigned short*) e, -2000);
				g_774654 = 1;
			} else if (d2_CurrentElementId == hShow) {
				fcn_00471af0(dialog, 0);
				fcn_00471af0(dialog, 1);
			} else if (d2_CurrentElementId == hMarriage) {
				fcn_00471af0(dialog, 0);
				if (*(int*) (e + 0x5c) == -1) {
					memset(buf, 0, 0x50);
					*(int*) (buf + 4) = *(unsigned char*) (e + 9) ?
						0x5409 : 0x540a;
					p = fcn_005cd440(buf, 0, 0, 0);
					if (p != 0) {
						fcn_004c4eb0("marriage");
						fcn_004c4510(p, *(int*) ((char*) p + 4));
						cm_AppendPacketFieldDelta(4, 1, 0x5c, e + 4);
						fcn_004c5360();
						fcn_004c4510(e, *(int*) (e + 4));
						cm_AppendPacketFieldDelta(4, 1, 0x5c,
							(char*) p + 4);
						fcn_004c5360();
						fcn_004c4ef0("marriage");
					}
				}
				fcn_00471af0(dialog, 1);
			} else if (d2_CurrentElementId == hChild) {
				fcn_00471af0(dialog, 0);
				if (*(int*) (e + 0x5c) != -1) {
					for (i = 3; i < 8; i++) {
						if (*(int*) (e + 0x5c + i * 4) ==
							-1) {
							if (*(unsigned char*) (e + 9) ==
								0) {
								a = *(int*) (e + 4);
								b = *(int*) (e + 0x5c);
							} else {
								b = *(int*) (e + 4);
								a = *(int*) (e + 0x5c);
							}
							d = *(int*) (e + 0x170) ?
								*(int*) (*(int*) (e + 0x170) + 1) : -1;
							fcn_004c4fc0(8, a, b, 0, d, 0, 0, 2);
							break;
						}
					}
				}
				fcn_00471af0(dialog, 1);
			}
		}
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
		}
	}
	fcn_00471e30(dialog);
}
