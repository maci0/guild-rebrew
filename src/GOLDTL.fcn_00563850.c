

#include "client_types.h"

// SIZE 0xc4
struct unit {
	char pad0[8];
	unsigned short house;
	char pada[6];
	int target;
	char pad14[0x30];
	pos14_7f4c00 p44;
	pos14_7f4c00 p52;
	pos14_7f4c00 p60;
	char pad6e[0xac - 0x6e];
	int search;
	int dist;
	char padb4[4];
	pos14_7f4c00 pb8;
	char padc6[2];
};

// SIZE 0x21c
struct house {
	char pad0[0xd];
	unsigned char level;
	char pade[0x21c - 0xe];
};

extern char g_7f4ca0[];
extern pos14_7f4c00 g_7f4c00;

char* __cdecl gm_StartFilteredEntitySearch(int, int, int);
void __cdecl fcn_00546190(struct unit*);
void __cdecl fcn_004c5420(int, int, int, int, int);
void __cdecl fcn_00500bb0(pos14_7f4c00*, int, int, int);

void __cdecl fcn_00563850(struct unit* u)
{
	char* e;
	struct house* h;

	e = gm_StartFilteredEntitySearch(1, 1, u->search);
	if (e == 0) {
		fcn_00546190(u);
		return;
	}
	u->target = *(int*) (e + 1);
	fcn_004c5420(*(int*) (e + 1), 0x5a, 2, 4, 0);
	u->p60 = g_7f4c00;
	u->p52 = g_7f4c00;
	u->p44 = g_7f4c00;
	fcn_00500bb0(&u->p52, 0, 10, 0);
	u->pb8 = u->p52;
	h = &((struct house*) g_7f4ca0)[u->house];
	fcn_00500bb0(&u->pb8, 0, (int) (10.0 * (h->level >= 9 ? 0.4f : h->level == 8 ? 0.6f : h->level == 7 ? 0.8f : 1.0f) * u->dist), 0);
}
