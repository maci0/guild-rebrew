

#include <string.h>

typedef struct
{
	char pad0[0x18];
	int x18;
	int x1c;
	char pad20[0x18];
	int x38;
	char pad3c[0x20];
	int x5c;
	char pad60[0x170];
	int x1d0;
	char pad1d4[0x2f4 - 0x1d4];
} Ctl;
// SIZE 0x2f4

extern int* lb_LobbyPlayerList;
extern int d2_NetLobbyForm;
extern int d2_CurrentWindowId;
extern char* d2_Controls;
extern char* txt_MaleTitleFirst;
extern char* txt_FemaleTitleFirst;
extern char* g_14b5d54;
extern int g_779cc0[];
extern char* d2_LobbyLocalPlayerEntry;
extern int g_779ce0;
extern int g_779c40;

char* __cdecl d3_GetSceneEntry(int);
void __cdecl d2_SetForm(int, int);
int __cdecl io_AppendText(int, ...);
int __cdecl sprintf(char*, const char*, ...);
int __cdecl d2_AddElementToWindow(int, int, int, int);
#include "Develop/Units/d2.v1/d2_gui.h"

void __cdecl d2_PopulateNetLobbyPlayerList(void)
{
	int y;
	int i;
	char buf[0x100];
	char* p;
	int h;

	y = 10;
	d2_SetForm(d2_NetLobbyForm, 1);
	io_AppendText((int) "$C");
	for (i = 0; i < 8; i++) {
		p = d3_GetSceneEntry(lb_LobbyPlayerList[i + 1]);
		if (p != 0) {
			h = d2_AddElementToWindow(5, y, *(int*) (p + 0xc) + 0x59a, d2_CurrentWindowId);
			sprintf(buf, "%s %s %s ", p[0x10] == 0 ? txt_MaleTitleFirst : txt_FemaleTitleFirst, p + 0x12, p + 0x22);
			if (*(int*) (p + 4) != 0) {
				strcat(buf, g_14b5d54);
			}
			d2_ShowTxt(((D2_CONTROL_TL*) d2_Controls)[h].width + 10, y, buf, d2_CurrentWindowId);
			y = y + ((D2_CONTROL_TL*) d2_Controls)[h].height + 5;
			g_779cc0[i] = h;
			if (p == d2_LobbyLocalPlayerEntry) {
				g_779ce0 = i;
			} else {
				((D2_CONTROL_TL*) d2_Controls)[h].value_05c = 1;
				((D2_CONTROL_TL*) d2_Controls)[h].flags_1d0 = 3;
			}
			if (g_779c40 == *(int*) p) {
				((D2_CONTROL_TL*) d2_Controls)[h].value_038 = 1;
			}
		}
	}
}
