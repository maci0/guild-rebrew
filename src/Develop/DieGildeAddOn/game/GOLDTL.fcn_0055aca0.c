#include "Develop/DieGildeAddOn/game/game_timestamp.h"


#pragma pack(push, 2)






// SIZE 0xe
#pragma pack(pop)

typedef struct {
	char pad0[0x52];
	GAME_TIMESTAMP t;
	char pad60[0x10];
	int state;
	char pad74[4];
	unsigned char flags;
	char pad79[0xb];
	int wait;
	char pad88[0x24];
	int ac;
	int b0;
	int b4;
	int b8;
} Ent;
// SIZE 0xbc

#include "client_types.h"
extern pos14_7f4c00 gm_GameTime;

void __cdecl he_FreeAction(Ent *);
int __cdecl fcn_004c4450(int);
int __cdecl fcn_004c4480(int);
void __cdecl fcn_004e97f0(int, int);
void __cdecl gm_AddTime(GAME_TIMESTAMP *, int, int, int);
int __cdecl fcn_004c5620(int, Ent *);
int __cdecl fcn_004e9530(int);
int __cdecl fcn_004e9730(int);
short __cdecl gm_RandomMod(int);

void __cdecl fcn_0055aca0(Ent *e)
{
	int n;
	int r;

	if (e->state == -1 || e->state == -2) {
		he_FreeAction(e);
		return;
	}
	if (e->flags & 4) {
		return;
	}
	if (e->wait != -1 && fcn_004c4450(e->wait) == 0) {
		return;
	}
	e->wait = -1;
	switch (e->state) {
	case 0:
		if (e->b0 == 0) {
			gm_AddTime(&e->t, 0x18, 0, 0);
			e->t.hour = 0x11;
			e->t.minute = 0;
			e->ac = 0;
			e->b0 = 0x1b;
			e->b4 = -1;
			e->b8 = -1;
			e->wait = fcn_004c5620(0, e);
			return;
		}
		e->ac = fcn_004e9530(e->b0);
		if (e->ac == 0) {
			gm_AddTime(&e->t, 0x18, 0, 0);
			e->t.hour = 0x11;
			e->t.minute = 0;
			e->ac = 0;
			e->b0 = 0x1b;
			e->b4 = -1;
			e->b8 = -1;
			e->wait = fcn_004c5620(0, e);
			return;
		}
		e->b4 = fcn_004e9730(e->ac);
		e->b8 = gm_RandomMod(3) ? fcn_004e9730(e->ac) : -1;
		break;
	case 1:
		n = 0;
		if (e->b4 != -1) {
			r = fcn_004c4450(e->b4);
			if (r == 1) {
				n++;
				r = fcn_004c4480(e->b4);
				fcn_004e97f0(r, e->ac);
				e->b4 = -1;
			} else if (r == 2) {
				e->b4 = -1;
				n++;
			}
		} else {
			n++;
		}
		if (e->b8 != -1) {
			r = fcn_004c4450(e->b8);
			if (r == 1) {
				n++;
				r = fcn_004c4480(e->b8);
				fcn_004e97f0(r, e->ac);
				e->b8 = -1;
			} else if (r == 2) {
				e->b8 = -1;
				n++;
			}
		} else {
			n++;
		}
		if (n == 2) {
			e->t = (*(GAME_TIMESTAMP*)&gm_GameTime);
			gm_AddTime(&e->t, 0, 5, 0);
			e->wait = fcn_004c5620(0, e);
			return;
		}
		break;
	default:
		return;
	}
	e->t = (*(GAME_TIMESTAMP*)&gm_GameTime);
	e->wait = fcn_004c5620(1, e);
}
