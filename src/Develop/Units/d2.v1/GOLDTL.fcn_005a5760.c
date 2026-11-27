

typedef struct
{
	char pad0[0x18];
	int x18;
	char pad1c[0x38];
	int x54;
	char pad58[4];
	int x5c;
	char pad60[0xc];
	int x6c;
	char pad70[0x2f4 - 0x70];
} Ctl;
// SIZE 0x2f4

typedef struct
{
	int icon;
	int name;
	int info;
	int id;
	unsigned char owner;
	char pad11[0xb];
} Row;
// SIZE 0x1c

typedef struct
{
	int x0;
	char pad4[8];
	int width;
} Screen;

extern int d2_CurrentWindowId;
extern char* g_77255c;
extern char* g_1015ea0;
extern int g_14a79c0[];
extern char g_868060[];

void __cdecl d2_SetForm(int, int);
int __cdecl d2_AddWindowField(int, int, int, int, int);
int __cdecl d2_AddElementToWindow(int, int, int, int);
#include "Develop/Units/d2.v1/d2_gui.h"
void __cdecl io_FormatTextBuffer(void*, char*, ...);
void __cdecl fcn_0046f940(int, char*);
void __cdecl d2_SetElementFont(int, int);

void __cdecl fcn_005a5760(Row* rows, int window, int form, int a4)
{
	char buf[0x80];
	int i;

	for (i = 0; i < 16; i++) {
		if (rows[i].id == 0) {
			return;
		}
		d2_SetForm(window, form);
		if (a4 != 0) {
			rows[i].icon = d2_AddWindowField((((Screen*)g_77255c)->width - 0x30) >> 1, i * 0x4c, rows[i].id + 0xdf, 0x82, d2_CurrentWindowId);
		} else {
			rows[i].icon = d2_AddElementToWindow((((Screen*)g_77255c)->width - 0x30) >> 1, i * 0x4c, rows[i].id + 0xdf, d2_CurrentWindowId);
			((D2_CONTROL_TL*) g_1015ea0)[rows[i].icon].value_05c = 1;
		}
		((D2_CONTROL_TL*) g_1015ea0)[rows[i].icon].value_054 = 1;
		rows[i].name = d2_ShowTxt((((Screen*)g_77255c)->width - 0xbe) >> 1, i * 0x4c + 0x30, "", d2_CurrentWindowId);
		io_FormatTextBuffer(buf, "%S", g_14a79c0[rows[i].id * 2]);
		fcn_0046f940(rows[i].name, buf);
		d2_SetElementFont(rows[i].icon, 0x54);
		d2_SetElementFont(rows[i].name, 0x54);
		((D2_CONTROL_TL*) g_1015ea0)[rows[i].name].value_06c = 1;
		((D2_CONTROL_TL*) g_1015ea0)[rows[i].name].width = 0xbe;
		rows[i].info = d2_ShowTxt((((Screen*)g_77255c)->width - 0xbe) >> 1, i * 0x4c + 0x3f, "", d2_CurrentWindowId);
		io_FormatTextBuffer(buf, "%s", g_868060 + rows[i].owner * 0x2f4);
		fcn_0046f940(rows[i].info, buf);
		d2_SetElementFont(rows[i].info, 0x54);
		((D2_CONTROL_TL*) g_1015ea0)[rows[i].info].value_06c = 1;
		((D2_CONTROL_TL*) g_1015ea0)[rows[i].info].width = 0xbe;
	}
}
