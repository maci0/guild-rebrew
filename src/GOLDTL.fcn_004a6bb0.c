// FUNCTION: GOLDTL 0x004a6bb0
// SIZE: 748

#include <math.h>
#include <string.h>

#define MAXV(a, b) ((a) > (b) ? (a) : (b))

#include "client_types.h"

// SIZE 0x21c
typedef struct {
	char f0[2];
	char state;
	char f3[6];
	char kind;
	char fa[3];
	char level;
	char fe[0x22];
	char name[0x10];
	char first[0x1dc];
} Player;

// SIZE 0x34
typedef struct {
	Player* player;
	int portrait;
	char pad[0x2c];
} Seat;

// SIZE 0xc0
typedef struct {
	int f0;
	char* owner;
	char f8[0x30];
	Seat seats[2];
	int fa0;
	int limit;
	int pot;
	int stake;
	char fb0[8];
	short fb8;
	char fba[6];
} Game;

extern char* g_1007cd4;
extern Card_1007ce0 g_1007ce0[24];
extern Player g_1007e60[2];
extern unsigned char g_773d75;
extern char* g_14a62d8[];
extern char* g_14a5dbc[];
extern char* g_14a60d0[];

unsigned short __cdecl fcn_0042e410(int n);
int __cdecl fcn_004fdec0(char* name);
int __cdecl fcn_0050b810(int a, unsigned char b);
int __cdecl fcn_0050b710(int a, unsigned char b);
int __cdecl fcn_0050b750(int a, unsigned char b);
int __cdecl fcn_004a6ea0(Game* s);

int __cdecl fcn_004a6bb0(char* owner, Game* game)
{
	int i;
	int j;
	int money;
	double d;
	Player* p;

	g_1007cd4 = 0;
	if (owner == 0 || owner[2] != 6 || game == 0) {
		return 0;
	}
	memset(g_1007e60, 0, sizeof(g_1007e60));
	g_1007cd4 = (char*) game;
	memset(game, 0, sizeof(Game));
	((Game*) g_1007cd4)->owner = owner;
	money = fcn_0050b710(fcn_0050b810(*(int*) (owner + 0x178), g_773d75), g_773d75);
	d = MAXV(10000.0, money);
	((Game*) g_1007cd4)->pot = fcn_0050b750((int) (d / (log10(d) + 1.0) * 0.1f), g_773d75);
	((Game*) g_1007cd4)->limit = ((Game*) g_1007cd4)->pot / (fcn_0042e410(3) + 7);
	((Game*) g_1007cd4)->stake = ((Game*) g_1007cd4)->limit;
	((Game*) g_1007cd4)->fb8 = 4;
	for (i = 0; i < 6; i++) {
		for (j = 0; j < 4; j++) {
			g_1007ce0[i * 4 + j].rank = i;
			g_1007ce0[i * 4 + j].suit = j;
		}
	}
	for (i = 0; i < 2; i++) {
		p = &g_1007e60[i];
		if (i != 0) {
			p->kind = g_1007e60[0].kind == 0;
		} else {
			p->kind = (char) fcn_0042e410(2);
		}
		p->level = (char) fcn_0042e410(4) + 1;
		strncpy(p->first, g_14a62d8[fcn_0042e410(0x95)], 0xf);
		if (p->kind == 0) {
			strncpy(p->name, g_14a5dbc[fcn_0042e410(0xbf)], 0xf);
			switch (fcn_0042e410(4)) {
			case 0:
				((Game*) g_1007cd4)->seats[i].portrait = fcn_004fdec0("buerger_MANN") + 0x639;
				break;
			case 1:
				((Game*) g_1007cd4)->seats[i].portrait = fcn_004fdec0("Handwerker_MANN") + 0x639;
				break;
			case 2:
				((Game*) g_1007cd4)->seats[i].portrait = fcn_004fdec0("buerger3_DICKER") + 0x639;
				break;
			case 3:
				((Game*) g_1007cd4)->seats[i].portrait = fcn_004fdec0("schneider1_MANN") + 0x639;
				break;
			}
		} else {
			strncpy(p->name, g_14a60d0[fcn_0042e410(0x70)], 0xf);
			switch (fcn_0042e410(4)) {
			case 0:
				((Game*) g_1007cd4)->seats[i].portrait = fcn_004fdec0("buergerin_frau") + 0x639;
				break;
			case 1:
				((Game*) g_1007cd4)->seats[i].portrait = fcn_004fdec0("buergerin2_frau") + 0x639;
				break;
			case 2:
				((Game*) g_1007cd4)->seats[i].portrait = fcn_004fdec0("minerin_frau") + 0x639;
				break;
			case 3:
				((Game*) g_1007cd4)->seats[i].portrait = fcn_004fdec0("arbeiterin_frau") + 0x639;
				break;
			}
		}
		p->state = 10;
		((Game*) g_1007cd4)->seats[i].player = p;
	}
	return fcn_004a6ea0(game);
}
