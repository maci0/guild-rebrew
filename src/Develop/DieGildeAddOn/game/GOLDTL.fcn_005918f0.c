

#include <string.h>

// SIZE 0x38
struct sel {
	char* who;
	char pad4[0x34];
};

extern int g_772514;
extern int g_14ce8e0;
extern int g_774654;

int __cdecl fcn_00470820(int, int, char*);
void __cdecl fcn_00471b60(int);
void __cdecl d2_SetForm(int, int);
int __cdecl io_AppendText();
int __cdecl fcn_005ca560(struct sel*);
void __cdecl fcn_005caaa0(int, int, int, struct sel*);
float __cdecl fcn_00505e30(unsigned short);
int __cdecl gm_GetOppositeStatIndex(int);
#include "Develop/DieGildeAddOn/game/spiel.h"
char* __cdecl gm_LookupEntityRecordById(int);
char* __cdecl fcn_005463a0(int, int, int);
char* __cdecl he_fn_Handlung(void);
void __cdecl io_FormatTextBuffer(char*, char*, ...);
#include "Develop/Units/d2.v1/d2_gui.h"
void __cdecl fcn_00534210(int, int, char*, int, int);
int __cdecl fcn_005373e0(void*, int);
void __cdecl fcn_00525ef0(void);
void __cdecl fcn_00471e30(int);

void __cdecl fcn_005918f0(char* w)
{
	int h;
	struct sel info;
	char buf[0x100];
	char* q;
	char* e;
	int any;
	int i;
	int y;

	if (*(unsigned char*) (w + 2) >= 10) {
		return;
	}
	h = fcn_00470820(0, 0, "ToolTip\\ToolTip_Personen");
	fcn_00471b60(h);
	d2_SetForm(0, 1);
	io_AppendText("$Z$[%1N3$]", *(unsigned short*) w);
	d2_SetForm(0, 4);
	memset(&info, 0, sizeof(info));
	info.who = w;
	if (fcn_005ca560(&info) != 0) {
		fcn_005caaa0(0xa6, 5, g_772514, &info);
	}
	d2_SetForm(0, 2);
	if (w[2] != 0x14) {
		io_AppendText(0x2b, (int) fcn_00505e30(*(unsigned short*) w));
	}
	io_AppendText(0x2c, (w[9] != 0 ? 0x18f : 0x130) + *(unsigned char*) (w + 0x164),
	    gm_GetOppositeStatIndex(*(unsigned char*) (w + 0x164)));
	io_AppendText(0x2d);
	if (w[0x166] == 0 && w[0x169] == 0) {
		io_AppendText("$3>%s$A", 0x253);
	} else {
		if (w[0x166] != 0) {
			io_AppendText("$3>%s$A", (w[9] != 0 ? 0x27b : 0x253) + *(unsigned char*) (w + 0x166));
		}
		if (w[0x169] != 0) {
			io_AppendText("$3>%s$A", (w[9] != 0 ? 0x27b : 0x253) + *(unsigned char*) (w + 0x169));
		}
	}
	io_AppendText(0x37, (w[9] != 0 ? 0x11e : 0x114) + *(unsigned char*) (w + 0xd));
	io_AppendText(0x2e, gm_WalkEntityChain(*(unsigned short*) w));
	io_AppendText(0x2f);
	q = gm_LookupEntityRecordById(*(int*) (w + 0x5c));
	if (q != 0 && *(unsigned char*) (q + 8) > 0) {
		io_AppendText(0x30, *(unsigned short*) q);
	} else {
		for (e = fcn_005463a0(1, 0, 0x41); e != 0; e = he_fn_Handlung()) {
			if (*(int*) (e + 0xac) == *(int*) (w + 4)) {
				break;
			}
		}
		if (e != 0 && (q = gm_LookupEntityRecordById(*(int*) (e + 0xb0))) != 0) {
			io_AppendText(0x31, *(unsigned short*) q);
		} else {
			io_AppendText(0x32);
		}
	}
	io_AppendText(0x33, *(unsigned char*) (w + 0xc) + 0x486);
	any = 0;
	io_AppendText(0x34);
	for (i = 0; i < 5; i++) {
		q = gm_LookupEntityRecordById(((int*) (w + 0x68))[i]);
		if (q != 0) {
			io_AppendText("$3>%1N1$A", *(unsigned short*) q);
			any = 1;
		}
	}
	if (any == 0) {
		io_AppendText("$3>%s$A", 0x35);
	}
	d2_SetForm(0, 3);
	for (i = 0, y = 0; y < 0x4b; i++, y += 0xf) {
		io_FormatTextBuffer(buf, "%s:", i + 0x16b7);
		d2_ShowTxt(0, y, buf, g_772514);
		fcn_00534210(0x64, y + 2, w, i, 0x4df);
	}
	do {
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
		}
	} while (fcn_005373e0(fcn_005918f0, 0x677c7) != 0);
	fcn_00525ef0();
	fcn_00471e30(h);
}
