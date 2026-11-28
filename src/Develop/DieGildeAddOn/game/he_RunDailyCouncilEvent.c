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

#include "Develop/client_types.h"
extern pos14_7f4c00 gm_GameTime;

void __cdecl he_FreeAction(Ent *);
int __cdecl cm_GetCommandStatus(int);
int __cdecl cm_GetCommandResult(int);
void __cdecl amt_PurchaseOfficeApplication(int, int);
void __cdecl gm_AddTime(GAME_TIMESTAMP *, int, int, int);
int __cdecl cm_SendSetHE(int, Ent *);
int __cdecl amt_FindHighestOccupiedOffice(int);
int __cdecl amt_SpawnOfficeCandidate(int);
short __cdecl gm_RandomMod(int);

void __cdecl he_RunDailyCouncilEvent(Ent *e)
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
	if (e->wait != -1 && cm_GetCommandStatus(e->wait) == 0) {
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
			e->wait = cm_SendSetHE(0, e);
			return;
		}
		e->ac = amt_FindHighestOccupiedOffice(e->b0);
		if (e->ac == 0) {
			gm_AddTime(&e->t, 0x18, 0, 0);
			e->t.hour = 0x11;
			e->t.minute = 0;
			e->ac = 0;
			e->b0 = 0x1b;
			e->b4 = -1;
			e->b8 = -1;
			e->wait = cm_SendSetHE(0, e);
			return;
		}
		e->b4 = amt_SpawnOfficeCandidate(e->ac);
		e->b8 = gm_RandomMod(3) ? amt_SpawnOfficeCandidate(e->ac) : -1;
		break;
	case 1:
		n = 0;
		if (e->b4 != -1) {
			r = cm_GetCommandStatus(e->b4);
			if (r == 1) {
				n++;
				r = cm_GetCommandResult(e->b4);
				amt_PurchaseOfficeApplication(r, e->ac);
				e->b4 = -1;
			} else if (r == 2) {
				e->b4 = -1;
				n++;
			}
		} else {
			n++;
		}
		if (e->b8 != -1) {
			r = cm_GetCommandStatus(e->b8);
			if (r == 1) {
				n++;
				r = cm_GetCommandResult(e->b8);
				amt_PurchaseOfficeApplication(r, e->ac);
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
			e->wait = cm_SendSetHE(0, e);
			return;
		}
		break;
	default:
		return;
	}
	e->t = (*(GAME_TIMESTAMP*)&gm_GameTime);
	e->wait = cm_SendSetHE(1, e);
}
