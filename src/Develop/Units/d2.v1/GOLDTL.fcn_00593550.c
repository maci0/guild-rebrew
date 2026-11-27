

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

extern int* g_774a34;
extern int g_6a9b9c;
extern int d2_CurrentWindowId;
extern char* g_1015ea0;
extern char* g_14a5774;
extern char* g_14a579c;
extern char* g_14b5d54;
extern int g_779cc0[];
extern char* g_779cb8;
extern int g_779ce0;
extern int g_779c40;

char* __cdecl fcn_004ce190(int);
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
	d2_SetForm(g_6a9b9c, 1);
	io_AppendText((int) "$C");
	for (i = 0; i < 8; i++) {
		p = fcn_004ce190(g_774a34[i + 1]);
		if (p != 0) {
			h = d2_AddElementToWindow(5, y, *(int*) (p + 0xc) + 0x59a, d2_CurrentWindowId);
			sprintf(buf, "%s %s %s ", p[0x10] == 0 ? g_14a5774 : g_14a579c, p + 0x12, p + 0x22);
			if (*(int*) (p + 4) != 0) {
				strcat(buf, g_14b5d54);
			}
			d2_ShowTxt(((D2_CONTROL_TL*) g_1015ea0)[h].width + 10, y, buf, d2_CurrentWindowId);
			y = y + ((D2_CONTROL_TL*) g_1015ea0)[h].height + 5;
			g_779cc0[i] = h;
			if (p == g_779cb8) {
				g_779ce0 = i;
			} else {
				((D2_CONTROL_TL*) g_1015ea0)[h].value_05c = 1;
				((D2_CONTROL_TL*) g_1015ea0)[h].flags_1d0 = 3;
			}
			if (g_779c40 == *(int*) p) {
				((D2_CONTROL_TL*) g_1015ea0)[h].value_038 = 1;
			}
		}
	}
}
