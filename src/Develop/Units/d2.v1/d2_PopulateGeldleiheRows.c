

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
extern char* d2_CurrentWindow;
extern char* d2_Controls;
extern int d2_ObjektNameTable[];
extern char gm_TownTable[];

void __cdecl d2_SetForm(int, int);
int __cdecl d2_AddWindowField(int, int, int, int, int);
int __cdecl d2_AddElementToWindow(int, int, int, int);
#include "Develop/Units/d2.v1/d2_gui.h"
void __cdecl io_FormatTextBuffer(void*, char*, ...);
void __cdecl d2_SetLabelText(int, char*);
void __cdecl d2_SetElementFont(int, int);

/* ADDRESS: GOLDDE 0x0058a470 */
void __cdecl d2_PopulateGeldleiheRows(Row* rows, int window, int form, int a4)
{
	char buf[0x80];
	int i;

	for (i = 0; i < 16; i++) {
		if (rows[i].id == 0) {
			return;
		}
		d2_SetForm(window, form);
		if (a4 != 0) {
			rows[i].icon = d2_AddWindowField((((Screen*)d2_CurrentWindow)->width - 0x30) >> 1, i * 0x4c, rows[i].id + 0xdf, 0x82, d2_CurrentWindowId);
		} else {
			rows[i].icon = d2_AddElementToWindow((((Screen*)d2_CurrentWindow)->width - 0x30) >> 1, i * 0x4c, rows[i].id + 0xdf, d2_CurrentWindowId);
			((D2_CONTROL_TL*) d2_Controls)[rows[i].icon].value_05c = 1;
		}
		((D2_CONTROL_TL*) d2_Controls)[rows[i].icon].value_054 = 1;
		rows[i].name = d2_ShowTxt((((Screen*)d2_CurrentWindow)->width - 0xbe) >> 1, i * 0x4c + 0x30, "", d2_CurrentWindowId);
		io_FormatTextBuffer(buf, "%S", d2_ObjektNameTable[rows[i].id * 2]);
		d2_SetLabelText(rows[i].name, buf);
		d2_SetElementFont(rows[i].icon, 0x54);
		d2_SetElementFont(rows[i].name, 0x54);
		((D2_CONTROL_TL*) d2_Controls)[rows[i].name].value_06c = 1;
		((D2_CONTROL_TL*) d2_Controls)[rows[i].name].width = 0xbe;
		rows[i].info = d2_ShowTxt((((Screen*)d2_CurrentWindow)->width - 0xbe) >> 1, i * 0x4c + 0x3f, "", d2_CurrentWindowId);
		io_FormatTextBuffer(buf, "%s", gm_TownTable + rows[i].owner * 0x2f4);
		d2_SetLabelText(rows[i].info, buf);
		d2_SetElementFont(rows[i].info, 0x54);
		((D2_CONTROL_TL*) d2_Controls)[rows[i].info].value_06c = 1;
		((D2_CONTROL_TL*) d2_Controls)[rows[i].info].width = 0xbe;
	}
}
