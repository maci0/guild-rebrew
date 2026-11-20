
#include "Develop/DieGildeAddOn/game/building_prototype.h"

extern unsigned char* lpGebaeudePROT;
#include "Develop/DieGildeAddOn/game/game_player.h"
#include "Develop/DieGildeAddOn/game/game_data.h"
#include "client_dialog_state.h"
extern char g_6ac690[];

int __cdecl fcn_00470820(int, int, char*);
void __cdecl d2_CenterDialogWindows(int);
void __cdecl d2_SetOverlayAnimation(int, int);
int __cdecl fcn_0050cf50(unsigned char*, int);
void __cdecl fcn_00527f10(unsigned char* e);
char* __cdecl gm_SearchTable67(int id);
void __cdecl d2_SetForm(int, int);
int __cdecl fcn_00508da0(unsigned char* e);
int __cdecl io_AppendText();
int __cdecl fcn_00472250(int, int, int);
void __cdecl fcn_00472640(int i, int flag);
void __cdecl fcn_00471af0(int k, int flag);
void __cdecl d2_RunTechTreeDialog(unsigned char*, int);
void __cdecl d2_ShowRenovationDialog(unsigned char*);
void __cdecl fcn_005c2a40(unsigned char*);
void __cdecl fcn_005c30e0(unsigned char*);
int __cdecl fcn_005373e0(void*, int);
void __cdecl fcn_00471e30(int);

void __cdecl d2_ShowGebaeudeOptions(unsigned char* p)
{
	int h1;
	int h2;
	int last;
	int r;
	int h3;
	int id;
	unsigned char* tbl;
	int h4;
	int redraw;
	int d;
	int k;
	int fl;
	char* t;

	last = -1;
	redraw = 1;
	h1 = -1;
	h2 = -1;
	h3 = -1;
	h4 = -1;
	tbl = (unsigned char*)&((BUILDING_PROTOTYPE*)lpGebaeudePROT)[p[0]];
	id = *(int*) (p + 1);
	d = fcn_00470820(0, 0, g_6ac690);
	d2_CenterDialogWindows(d);
	d2_SetOverlayAnimation(0, 0);
	r = fcn_0050cf50(p, (char) p[0x5c]);
	fcn_00527f10(p);
	do {
		t = gm_SearchTable67(id);
		if ((*(unsigned short*) (p + 0x5a) & 0x400) != 0 || t == 0) {
			g_774654 = 1;
		}
		fl = *(unsigned short*) (p + 0x5a);
		if (fl != last) {
			redraw = 1;
		}
		last = fl;
		if (redraw != 0) {
			d2_SetForm(d, 1);
			k = (int) (9 - fcn_00508da0(p) / 10 + 0.5);
			if (*(unsigned short*) (p + 0x27) != g_774970 && *(unsigned short*) (p + 0x25) != g_774970) {
				io_AppendText(0x17a0, *(unsigned short*) (p + 0x25), p, k + 0x17b1, k + 0x17bb, r);
				if (*tbl == 1) {
					io_AppendText(0x17a2, p[0x65]);
				}
			}
			io_AppendText(0x179e, p, k + 0x17b1, k + 0x17bb, r);
			if (*tbl == 1) {
				io_AppendText(0x17a2, p[0x65]);
			}
			h2 = fcn_00472250(d, 1, io_AppendText(0x17a5));
			if (*tbl != 3) {
				h1 = fcn_00472250(d, 1, io_AppendText(0x17ac));
			}
			if (tbl[0x21] > 1) {
				h3 = fcn_00472250(d, 1, io_AppendText(0x17a8));
			}
			h4 = fcn_00472250(d, 1, io_AppendText(0x17ab));
			redraw = 0;
		}
		if ((p[0x5a] & 4) != 0) {
			if (h1 != -1) {
				fcn_00472640(h1, 0);
			}
			if (h2 != -1) {
				fcn_00472640(h2, 0);
			}
		}
		if (h4 != -1) {
			if ((p[0x5a] & 0x40) != 0) {
				fcn_00472640(h4, 0);
			}
			else {
				fcn_00472640(h4, 1);
			}
		}
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
		}
		if (g_100f1dc != -1) {
			if (d2_CurrentElementId == h1) {
				fcn_00471af0(d, 0);
				d2_RunTechTreeDialog(p, 0xfd);
				fcn_00471af0(d, 1);
			}
			else if (d2_CurrentElementId == h2) {
				fcn_00471af0(d, 0);
				d2_ShowRenovationDialog(p);
				fcn_00471af0(d, 1);
				redraw = 1;
			}
			else if (d2_CurrentElementId == h3) {
				fcn_00471af0(d, 0);
				fcn_005c2a40(p);
				fcn_00471af0(d, 1);
				redraw = 1;
			}
			else if (d2_CurrentElementId == h4) {
				fcn_00471af0(d, 0);
				fcn_005c30e0(p);
				fcn_00471af0(d, 1);
				redraw = 1;
			}
		}
	} while (fcn_005373e0(d2_ShowGebaeudeOptions, 0x677c7) != 0);
	fcn_00471e30(d);
	g_7746f8 = 0;
}
