// FUNCTION: GOLD 0x589390

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
void __cdecl fcn_004727a0(int, int);
int __cdecl fcn_00519190();
int __cdecl fcn_005ca560(struct sel*);
void __cdecl fcn_005caaa0(int, int, int, struct sel*);
float __cdecl fcn_00508e80(unsigned short);
int __cdecl gm_GetOppositeStatIndex(int);
#include "Develop/DieGildeAddOn/game/spiel.h"
char* __cdecl fcn_00508e40(int);
char* __cdecl fcn_005463a0(int, int, int);
char* __cdecl fcn_005462a0(void);
void __cdecl fcn_0051af00(char*, char*, ...);
void __cdecl fcn_0046fac0(int, short, char*, int);
void __cdecl fcn_00534210(int, int, char*, int, int);
int __cdecl fcn_005373e0(void*, int);
void __cdecl fcn_00525ef0(void);
void __cdecl fcn_00471e30(int);

void __cdecl fcn_00589390(char* w)
{
	int h;
	struct sel info;
	char buf[0x100];
	char* q;
	char* e;
	int any;
	int i;

	if (*(unsigned char*) (w + 2) >= 10) {
		return;
	}
	h = fcn_00470820(0, 0, "ToolTip\\ToolTip_Personen");
	fcn_00471b60(h);
	fcn_004727a0(0, 1);
	fcn_00519190("$Z$[%1N3$]", *(unsigned short*) w);
	fcn_004727a0(0, 4);
	memset(&info, 0, sizeof(info));
	info.who = w;
	if (fcn_005ca560(&info) != 0) {
		fcn_005caaa0(0xa6, 5, g_772514, &info);
	}
	fcn_004727a0(0, 2);
	if (w[2] != 0x14) {
		fcn_00519190(0x2b, (int) fcn_00508e80(*(unsigned short*) w));
	}
	fcn_00519190(0x2c, (w[9] != 0 ? 0x18f : 0x130) + *(unsigned char*) (w + 0x164),
	    gm_GetOppositeStatIndex(*(unsigned char*) (w + 0x164)));
	fcn_00519190(0x2d);
	if (w[0x166] == 0 && w[0x169] == 0) {
		fcn_00519190("$3>%s$A", 0x253);
	} else {
		if (w[0x166] != 0) {
			fcn_00519190("$3>%s$A", (w[9] != 0 ? 0x27b : 0x253) + *(unsigned char*) (w + 0x166));
		}
		if (w[0x169] != 0) {
			fcn_00519190("$3>%s$A", (w[9] != 0 ? 0x27b : 0x253) + *(unsigned char*) (w + 0x169));
		}
	}
	fcn_00519190(0x37, (w[9] != 0 ? 0x11e : 0x114) + *(unsigned char*) (w + 0xd));
	fcn_00519190(0x2e, gm_WalkEntityChain(*(unsigned short*) w));
	fcn_00519190(0x2f);
	q = fcn_00508e40(*(int*) (w + 0x5c));
	if (q != 0 && *(unsigned char*) (q + 8) > 0) {
		fcn_00519190(0x30, *(unsigned short*) q);
	} else {
		for (e = fcn_005463a0(1, 0, 0x41); e != 0; e = fcn_005462a0()) {
			if (*(int*) (e + 0xac) == *(int*) (w + 4)) {
				break;
			}
		}
		if (e != 0 && (q = fcn_00508e40(*(int*) (e + 0xb0))) != 0) {
			fcn_00519190(0x31, *(unsigned short*) q);
		} else {
			fcn_00519190(0x32);
		}
	}
	fcn_00519190(0x33, *(unsigned char*) (w + 0xc) + 0x486);
	any = 0;
	fcn_00519190(0x34);
	for (i = 0; i < 5; i++) {
		q = fcn_00508e40(((int*) (w + 0x68))[i]);
		if (q != 0) {
			fcn_00519190("$3>%1N1$A", *(unsigned short*) q);
			any = 1;
		}
	}
	if (any == 0) {
		fcn_00519190("$3>%s$A", 0x35);
	}
	fcn_004727a0(0, 3);
	for (i = 0; i < 5; i++) {
		fcn_0051af00(buf, "%s:", i + 0x16b7);
		fcn_0046fac0(0, i * 15, buf, g_772514);
		fcn_00534210(0x64, i * 15 + 2, w, i, 0x4df);
	}
	do {
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
		}
	} while (fcn_005373e0(fcn_00589390, 0x677c7) != 0);
	fcn_00525ef0();
	fcn_00471e30(h);
}
